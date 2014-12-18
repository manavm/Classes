// ST7735TestMain.c
// Runs on LM4F120/TM4C123
// Test the functions in ST7735.c by printing basic
// patterns to the LCD.
// Daniel Valvano
// September 12, 2013

/* This example accompanies the book
   "Embedded Systems: Real Time Interfacing to Arm Cortex M Microcontrollers",
   ISBN: 978-1463590154, Jonathan Valvano, copyright (c) 2014

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

// Backlight (pin 10) connected to +3.3 V
// MISO (pin 9) unconnected 
// SCK (pin 8) connected to PA2 (SSI0Clk)
// MOSI (pin 7) connected to PA5 (SSI0Tx)
// TFT_CS (pin 6) connected to PA3 (SSI0Fss)
// CARD_CS (pin 5) unconnected
// Data/Command (pin 4) connected to PA6 (GPIO)
// RESET (pin 3) connected to PA7 (GPIO)
// VCC (pin 2) connected to +3.3 V
// Gnd (pin 1) connected to ground
#include <stdio.h>
#include <stdint.h>
#include "ST7735.h"
#include "PLL.h"
#include "inc/tm4c123gh6pm.h"
#include "MainMenu.h"
#include "switch.h"
#include "timer.h"
#include "LCD.h"
#include "Clock.h"
#include "PWM.h"

void PolledButtons_Init(void);
void DelayWait10ms(uint32_t n);
void Delay1ms(uint32_t n);
void WaitForInterrupt(void);  // low power mode
extern int hour;
extern int minute;
extern int hour_alarm;
extern int minute_alarm;
extern int alarm;
extern unsigned int sTime, sAlarm, onAlarm, onMode, sClock;
extern int displaymode;


#define GPIO_LOCK_KEY           0x4C4F434B  // Unlocks the GPIO_CR register
#define PF0   (*((volatile uint32_t *)0x40025004))
#define PF2   (*((volatile uint32_t *)0x40025010))
#define PF4   (*((volatile uint32_t *)0x40025040))
#define SW1       0x10                      // on the left side of the Launchpad board
#define SW2       0x01                      // on the right side of the Launchpad board
#define SYSCTL_RCGC2_GPIOF      0x00000020  // port F Clock Gating Control

// Make PF2 an output, enable digital I/O, ensure alt. functions off
void SSR_Init(void){ 
  SYSCTL_RCGCGPIO_R |= 0x20;        // 1) activate clock for Port F
  while((SYSCTL_PRGPIO_R&0x20)==0){}; // allow time for clock to start
                                    // 2) no need to unlock PF2
  GPIO_PORTF_PCTL_R &= ~0x00000F00; // 3) regular GPIO
  GPIO_PORTF_AMSEL_R &= ~0x04;      // 4) disable analog function on PF2
  GPIO_PORTF_DIR_R |= 0x04;         // 5) set direction to output
  GPIO_PORTF_AFSEL_R &= ~0x04;      // 6) regular port function
  GPIO_PORTF_DEN_R |= 0x04;         // 7) enable digital port
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


void displayMainMenu(void) {
	if(sTime == 1){
		SetTime();
		switchReset();
	}
	
	else if(sAlarm == 1){
		SetAlarm();
		switchReset();
	}
	
	else if (onAlarm == 1){
		SetOn_Off();
		switchReset();
	}
	
	else if (onMode == 1){
		ChangeDisplayMode();
		switchReset();
	}
	
	else if (sClock == 1){
		if(displaymode == 1){
			switchReset();
		DisplayClockAnalog();
		}
		if(displaymode == 0){
			 switchReset();
		DisplayClockDigital();
		}
	}
}


int main(void){
	Output_Init();
	Board_Init();
  PLL_Init();                           // set system clock to 80 MHz		
	SSR_Init();														//initialize heartbeat
	SysTick_Init(80000000);
  ST7735_InitR(INITR_REDTAB);
	PolledButtons_Init();       // initialize interrupts and ports
	printf("CLOCK\nMAIN MENU\n\n\n\n\nPress 1 :SET TIME\nPress 2 :SET ALARM\nPress 3:ALRM ON/OFF\nPress 4 :DISPLAY CLK");
	while(1){
	//interrupts for button 1-5
	//functions include a way to set time, set alarm, set alarm on/off, and change display mode	
		displayMainMenu();
    Delay1ms(300);
    PF2 ^= 0x04;
		if(alarm == 1){										//will enter this if alarm is on
			if(hour == hour_alarm){					//checks to make sure hours are equal
				if(minute == minute_alarm){		//checks to make sure minutes are equal
					while(PF4 != 0){
						displayAlarm(hour, minute, 0);
					  PWM0A_Init(40000, 30000);         // initialize PWM0, 1000 Hz, 75% duty
						PWM0B_Init(40000, 10000);         // initialize PWM0, 1000 Hz, 25% duty
					}
					PWM0A_Init(0, 0);         // initialize PWM0, 1000 Hz, 75% duty
					PWM0B_Init(0, 0);
						alarm = 0;
					main();
				}
			}
		
		}
		
		
}
}

