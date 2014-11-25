// SysTickInts.c
// Runs on LM4F120/TM4C123
// Use the SysTick timer to request interrupts at a particular period.
// Daniel Valvano
// October 11, 2012

/* This example accompanies the book
   "Embedded Systems: Real Time Interfacing to Arm Cortex M Microcontrollers",
   ISBN: 978-1463590154, Jonathan Valvano, copyright (c) 2014

   Program 5.12, section 5.7

 Copyright 2014 by Jonathan W. Valvano, valvano@mail.utexas.edu
    You may use, edit, run or distribute this file
    as long as the above copyright notice remains
 THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 VALVANO SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL,
 OR CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 For more information about my classes, my research, and my books, see
 http://users.ece.utexas.edu/~valvano/
 */

#include <stdint.h>
#include "inc/tm4c123gh6pm.h"
#include "SysTickInts.h"
#include "ADCSWTrigger.h"
#include "ADC.h"

#define NVIC_ST_CTRL_CLK_SRC    0x00000004  // Clock Source
#define NVIC_ST_CTRL_INTEN      0x00000002  // Interrupt enable
#define NVIC_ST_CTRL_ENABLE     0x00000001  // Counter mode
#define PF1       (*((volatile uint32_t *)0x40025008))


void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts
long StartCritical (void);    // previous I bit, disable interrupts
void EndCritical(long sr);    // restore I bit to previous value
void WaitForInterrupt(void);  // low power mode

uint32_t data;
volatile uint8_t flag = 0;  
// **************SysTick_Init*********************
// Initialize SysTick periodic interrupts
// Input: interrupt period
//        Units of period are 12.5ns (assuming 50 MHz clock)
//        Maximum is 2^24-1
//        Minimum is determined by length of ISR

void SysTick_Init(void)
{
    // Initialize SysTick to interrupt at every sample
    NVIC_ST_CTRL_R &= ~(0x1);       // disable SysTick during initialization
    NVIC_ST_CTRL_R |= 0x2;          // set IE bit
    // SysTick should interrupt at a frequency of 40 Hz
    NVIC_ST_RELOAD_R = 80000000/20;          // FIXME: 40 Hz frequency
    NVIC_ST_CURRENT_R = 0;          // clear current register
    NVIC_ST_CTRL_R |= 0x1;          // reenable SysTick
    NVIC_ST_CTRL_R |= 0x4;          // use external clock
}

void SysTick_Handler(void)
{
    // 1.Toggle the heartbeat LED
    PF1 ^= 0x2;      

    // 2.Sample the ADC

    // 3.Save the 12-bit ADC sample into mailbox ADCMail
    data = ADC0_InSeq3();
    // 4.Set the mailbox flag ADCStatus to signify when new data is available
    flag = 1;
    // 5.Return from Interrupt
}
