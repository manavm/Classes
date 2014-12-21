// PWMtest.c
// Runs on TM4C123
// Use PWM0/PB6 and PWM1/PB7 to generate pulse-width modulated outputs.
// Daniel Valvano
// March 28, 2014

/* This example accompanies the book
   "Embedded Systems: Real Time Interfacing to ARM Cortex M Microcontrollers",
   ISBN: 978-1463590154, Jonathan Valvano, copyright (c) 2014
  Program 6.7, section 6.3.2

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
#include "PLL.h"
#include "PWM.h"
#include "motor.h"
#include "Switch.h"
#include "tach.h"
#include "inc/tm4c123gh6pm.h"
#include "ST7735.h"
//#include "InputCapture.h"

#define PF0       (*((volatile uint32_t *)0x40025004))
#define PF4       (*((volatile uint32_t *)0x40025040))


extern uint32_t First;               // Timer0A first edge
extern int32_t Done;                // set each rising// max period is (2^24-1)*12.5ns = 209.7151ms
extern uint32_t Period;
void Delay1ms(uint32_t n);
void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts
long StartCritical (void);    // previous I bit, disable interrupts
void EndCritical(long sr);    // restore I bit to previous value
void WaitForInterrupt(void);  // low power mode
void HeartBeat_Init(void);	//PF2 for heartbeat

extern unsigned long actual, desired, interrupt;
//extern unsigned long H, L;
unsigned long ycoord = 0, count = 0;
extern uint32_t Period; // 24-bit, 12.5 ns units

uint32_t Speed; // motor speed in 0.1 Hz, 0.025rps
extern signed long H, L;
int32_t E; // speed error in 0.1 Hz, 0.025rps

int32_t U = 10000; 

void HeartBeat_Init(void){
	                                   // activate port F
  SYSCTL_RCGCGPIO_R |= 0x20;
  while((SYSCTL_PRGPIO_R&0x0020) == 0){};// ready?
  //Count = 0;                       // allow time to finish activating
  GPIO_PORTF_DIR_R |= 0x04;        // make PF2 out (built-in LED)
  GPIO_PORTF_AFSEL_R &= ~0x04;     // disable alt funct on PF2
  GPIO_PORTF_DEN_R |= 0x04;        // enable digital I/O on PF2
                                   // configure PF2 as GPIO
  GPIO_PORTF_PCTL_R = (GPIO_PORTF_PCTL_R&0xFFFFF0FF)+0x00000000;
  GPIO_PORTF_AMSEL_R = 0;          // disable analog functionality on PF
  //TimerCapture_Init(&UserTask);    // initialize timer0A in capture mode
	}


void plotPoints(void){
		count = count + 1;
		if (count == 2){
		if(ycoord == 0){
		ST7735_PlotClear(0,4095);  // range from 0 to 4095
		}
		if(ycoord == 128){
    ST7735_PlotClear(0,4095);  // range from 0 to 4095
			ycoord = 0;
		}
		ST7735_DrawFastHLine(ycoord, ((L/20)+40), 2, ST7735_RED);
		ST7735_DrawFastHLine(ycoord, (Speed/40)-40, 2, ST7735_BLUE);
		ycoord += 2;
		count = 0;
	}
}

int main(void){
	Output_Init();
  DisableInterrupts();  // disable interrupts while initializing
  PLL_Init();           // bus clock at 80 MHz
	PeriodMeasure_Init();
	Speed = 600;
	HeartBeat_Init();
  Motor_Init();         // output from PA5, SysTick interrupts
  Switch_Init();        // arm PF4, PF0 for falling edge interrupts
  EnableInterrupts();   // enable after all initialization are done
	PWM0B_Init(40000,U);
	ST7735_OutString("Actual \n");
	ST7735_OutString("Desired");
  while(1){ // main program is free to perform other tasks
		if(interrupt){
			interrupt = 0;
			Speed = 800000000/(Period*1024); // 0.1 Hz, 0.025rps
			E = L - Speed;
			U = U + (3*(E)/64);
			if(U < 100) U=100; 
			if(U>39900) U=39900; 
			PWM0B_Duty(U);
			plotPoints();
			ST7735_SetCursor(12, 0);
			ST7735_OutUDec(Speed/40);
			ST7735_SetCursor(12, 1);
			ST7735_OutUDec(L/40);
		}
		Delay1ms(300);
		GPIO_PORTF_DATA_R = GPIO_PORTF_DATA_R^0x04;

  }
}
