#include <stdint.h>
#include "inc/tm4c123gh6pm.h"
#include "switch.h"

void EnableInterrupts(void);  // Enable interrupts
long StartCritical (void);    // previous I bit, disable interrupts
void EndCritical(long sr);    // restore I bit to previous value
void WaitForInterrupt(void);  // low power mode

volatile unsigned long Counts;
extern int minute, hour;
//int counts;
int second;
#define PD0             (*((volatile unsigned long *)0x40007004))
#define NVIC_ST_CTRL_CLK_SRC    0x00000004  // Clock Source
#define NVIC_ST_CTRL_INTEN      0x00000002  // Interrupt enable
#define NVIC_ST_CTRL_ENABLE     0x00000001  // Counter mode


/*
void SysTick_Init(void){
	SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOD; // activate port D
  GPIO_PORTD_DIR_R |= 0x02;   // make PD0 out
  GPIO_PORTD_DEN_R |= 0x01;   // enable digital I/O on PD0
	GPIO_PORTD_AFSEL_R &= ~0x04;// disable alt funct on PF2
	
	int Counts = 0;
  NVIC_ST_CTRL_R = 0;         // disable SysTick during setup
  NVIC_ST_RELOAD_R = period-1;// reload value
  NVIC_ST_CURRENT_R = 0;      // any write to current clears it
  NVIC_SYS_PRI3_R = (NVIC_SYS_PRI3_R&0x00FFFFFF)|0x40000000; // priority 2
                              // enable SysTick with core clock and interrupts
  NVIC_ST_CTRL_R = NVIC_ST_CTRL_ENABLE+NVIC_ST_CTRL_CLK_SRC+NVIC_ST_CTRL_INTEN;
}
*/

void SysTick_Init(unsigned long period){long sr;
  sr = StartCritical();
  NVIC_ST_CTRL_R = 0;         // disable SysTick during setup
  NVIC_ST_RELOAD_R = period-1;// reload value
  NVIC_ST_CURRENT_R = 0;      // any write to current clears it
  NVIC_SYS_PRI3_R = (NVIC_SYS_PRI3_R&0x00FFFFFF)|0x40000000; // priority 2
                              // enable SysTick with core clock and interrupts
  NVIC_ST_CTRL_R = NVIC_ST_CTRL_ENABLE+NVIC_ST_CTRL_CLK_SRC+NVIC_ST_CTRL_INTEN;
  EndCritical(sr);
}

void SysTick_Handler(void){
	//counts = counts + 1;
	//if(counts == 10){
	second = second + 1;
	if(second == 60){
	second = second%60;
  minute = minute + 1;
	}
	if(minute == 60){
		minute = minute % 60;
		hour = hour + 1;
		if(hour == 13){
			hour = hour%12;
		}
	//}
}
}

void SysTick_Wait(uint32_t delay){
  volatile uint32_t elapsedTime;
  uint32_t startTime = NVIC_ST_CURRENT_R;
  do{
    elapsedTime = (startTime-NVIC_ST_CURRENT_R)&0x00FFFFFF;
  }
  while(elapsedTime <= delay);
}

void SysTick_Wait10ms(uint32_t delay){
  uint32_t i;
  for(i=0; i<delay; i++){
    SysTick_Wait(5000000);  // wait 10ms (assumes 50 MHz clock)
  }
	
}

