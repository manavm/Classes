// TwoButtonPoll.c
// Runs on LM4F120/TM4C123
// Use polled interrupts to respond to two button presses.  Note
// that button bouncing is not addressed.
// Daniel Valvano
// September 12, 2013

/* This example accompanies the book
   "Embedded Systems: Introduction to ARM Cortex M Microcontrollers"
   ISBN: 978-1469998749, Jonathan Valvano, copyright (c) 2014
   Volume 1, Program 9.6
   
   "Embedded Systems: Real Time Interfacing to ARM Cortex M Microcontrollers",
   ISBN: 978-1463590154, Jonathan Valvano, copyright (c) 2014
   Volume 2, Example 5.1, Program 5.8

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

// momentary, positive logic button connected to PE4 (trigger on rising edge)
// momentary, positive logic button connected to PE5 (trigger on rising edge)

#include <stdint.h>
#include "inc/tm4c123gh6pm.h"
#define NVIC_EN0_INT4           0x00000010  // Interrupt 4 enable

#define GPIO_LOCK_KEY           0x4C4F434B  // Unlocks the GPIO_CR register
#define PF0                     (*((volatile uint32_t *)0x40025004))
#define PF4                     (*((volatile uint32_t *)0x40025040))
#define PF2   (*((volatile uint32_t *)0x40025010))
#define PA5                     (*((volatile uint32_t *)0x40004080))
#define SWITCHES                (*((volatile uint32_t *)0x40025044))
#define SW1       0x10                      // on the left side of the Launchpad board
#define SW2       0x01                      // on the right side of the Launchpad board
#define SYSCTL_RCGC2_GPIOF      0x00000020  // port F Clock Gating Control

void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts
long StartCritical (void);    // previous I bit, disable interrupts
void EndCritical(long sr);    // restore I bit to previous value
void WaitForInterrupt(void);  // low power mode

// global variables visible in Watch window of debugger
// set when corresponding button pressed
volatile uint32_t play, rewind, mode, pause; // semaphores
volatile uint32_t bNote, fNote, aNote;
//--PolledButtons_Init--
//inititalizes Port E interrupts

void PolledButtons_Init(void){
  DisableInterrupts();
  SYSCTL_RCGCGPIO_R |= 0x00000010; // activate port E
  GPIO_PORTE_AMSEL_R &= ~0x30;// disable analog function on PE5-4
  GPIO_PORTE_PCTL_R &= ~0x00FF0000; // configure PE5-4 as GPIO 
  GPIO_PORTE_DIR_R &= ~0x30;  // make PE5-4 in 
  GPIO_PORTE_AFSEL_R &= ~0x30;// disable alt funct on PE5-4 
  GPIO_PORTE_DEN_R |= 0x30;   // enable digital I/O on PE5-4
  GPIO_PORTE_IS_R &= ~0x30;   // PE5-4 is edge-sensitive 
  GPIO_PORTE_IBE_R &= ~0x30;  // PE5-4 is not both edges 
  GPIO_PORTE_IEV_R |= 0x30;   // PE5-4 rising edge event
  GPIO_PORTE_ICR_R = 0x30;    // clear flag5-4
  GPIO_PORTE_IM_R |= 0x30;    // enable interrupt on PE5-4
                              // GPIO PortE=priority 2
  NVIC_PRI1_R = (NVIC_PRI1_R&0xFFFFFF00)|0x00000040; // bits 5-7
  NVIC_EN0_R = NVIC_EN0_INT4; // enable interrupt 4 in NVIC
  EnableInterrupts();
}
void GPIOPortE_Handler(void){
  if(GPIO_PORTE_RIS_R&0x10){  // poll PE4
    GPIO_PORTE_ICR_R = 0x10;  // acknowledge flag4
    rewind = 1;                  // signal SW1 occurred
  }
	  if(GPIO_PORTE_RIS_R&0x20){  // poll PE5
    GPIO_PORTE_ICR_R = 0x20;  // acknowledge flag5
    rewind = 1;                  // signal SW2 occurred
  }
	}

void Board_Init(void){            
  SYSCTL_RCGCGPIO_R |= 0x20;     // 1) activate Port F
  while((SYSCTL_PRGPIO_R&0x20) == 0){};// ready?
                                 // 2a) unlock GPIO Port F Commit Register
  GPIO_PORTF_LOCK_R = GPIO_LOCK_KEY;
  GPIO_PORTF_CR_R |= (SW1|SW2);  // 2b) enable commit for PF4 and PF0
                                 // 3) disable analog functionality on PF4 and PF0
  GPIO_PORTF_AMSEL_R &= ~(SW1|SW2);
                                 // 4) configure PF0 and PF4 as GPIO
  GPIO_PORTF_PCTL_R = (GPIO_PORTF_PCTL_R&0xFFF0FFF0)+0x00000000;
  GPIO_PORTF_DIR_R &= ~(SW1|SW2);// 5) make PF0 and PF4 in (built-in buttons)
                                 // 6) disable alt funct on PF0 and PF4
  GPIO_PORTF_AFSEL_R &= ~(SW1|SW2);
//  delay = SYSCTL_RCGC2_R;        // put a delay here if you are seeing erroneous NMI
  GPIO_PORTF_PUR_R |= (SW1|SW2); // enable weak pull-up on PF0 and PF4
  GPIO_PORTF_DEN_R |= (SW1|SW2); // 7) enable digital I/O on PF0 and PF4
}

//------------Switch_Init2------------
// Initialize GPIO Port F
// Input: none
// Output: none
void Switch_Init2(void){  unsigned long volatile delay;
  SYSCTL_RCGC2_R |= 0x00000020; // (a) activate clock for port F
  delay = SYSCTL_RCGC2_R;
  GPIO_PORTF_LOCK_R = 0x4C4F434B; // unlock GPIO Port F
  GPIO_PORTF_CR_R = 0x1F;         // allow changes to PF4,0
  GPIO_PORTF_DIR_R &= ~0x1F;    // (c) make PF4,0 in (built-in button)
  GPIO_PORTF_AFSEL_R &= ~0x1F;  //     disable alt funct on PF4,0
  GPIO_PORTF_DEN_R |= 0x1F;     //     enable digital I/O on PF4,0
  GPIO_PORTF_PCTL_R &= ~0x000F000F; //  configure PF4,0 as GPIO
  GPIO_PORTF_AMSEL_R &= ~0x1F;  //     disable analog functionality on PF4,0
  GPIO_PORTF_PUR_R |= 0x1F;     //     enable weak pull-up on PF4,0
  GPIO_PORTF_IS_R &= ~0x1F;     // (d) PF4,PF0 is edge-sensitive
  GPIO_PORTF_IBE_R &= ~0x1F;    //     PF4,PF0 is not both edges
  GPIO_PORTF_IEV_R &= ~0x1F;    //     PF4,PF0 falling edge event
  GPIO_PORTF_ICR_R = 0x1F;      // (e) clear flags 4,0
  GPIO_PORTF_IM_R |= 0x1F;      // (f) arm interrupt on PF4,PF0
  NVIC_PRI7_R = (NVIC_PRI7_R&0xFF00FFFF)|0x00400000; // (g) priority 2
  NVIC_EN0_R = 0x40000000;      // (h) enable interrupt 30 in NVIC
}

void GPIOPortF_Handler(void){ // called on touch of either SW1 or SW2
	if(GPIO_PORTF_RIS_R&0x01){  // SW2 touch
    GPIO_PORTF_ICR_R = 0x01;  // acknowledge flag0
     play = 1;                  // signal SW1 occurred
  }
  if(GPIO_PORTF_RIS_R&0x10){  // SW1 touch
    GPIO_PORTF_ICR_R = 0x10;  // acknowledge flag4
     mode = 1;                  // signal SW1 occurred
  }
	if(GPIO_PORTF_RIS_R&0x02){  // SW2 touch
    GPIO_PORTF_ICR_R = 0x02;  // acknowledge flag0
     bNote = 1;                  // signal SW1 occurred
  }
	if(GPIO_PORTF_RIS_R&0x04){  // SW2 touch
    GPIO_PORTF_ICR_R = 0x04;  // acknowledge flag0
     fNote = 1;                  // signal SW1 occurred
  }
	if(GPIO_PORTF_RIS_R&0x08){  // SW2 touch
    GPIO_PORTF_ICR_R = 0x08;  // acknowledge flag0
     aNote = 1;                  // signal SW1 occurred
  }
}


void resetSwitches(void){
	play = 0;
	rewind = 0;
	mode = 0;
	pause = 0;
}

