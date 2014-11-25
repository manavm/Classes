// Lab8.c
// Runs on LM4F120 or TM4C123
// Student names: change this to your names or look very silly
// Last modification date: change this to the last modification date or look very silly

// Analog Input connected to PE2=ADC1
// displays on Nokia 5110
// PF3, PF2, PF1 are heartbeats

#include <stdint.h>

#include "ST7735.h"
#include "TExaS.h"
#include "ADC.h"
#include "inc/tm4c123gh6pm.h"
#include "SysTickInts.h"
#include "ADCSWTrigger.h"
#include "lab9.h"


//*****the first three main programs are for debugging *****
// main1 tests just the ADC and slide pot, use debugger to see data
// main2 adds the LCD to the ADC and slide pot, ADC data is on Nokia
// main3 adds your convert function, position data is no Nokia

void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts

#define PF1       (*((volatile uint32_t *)0x40025008))
#define PF2       (*((volatile uint32_t *)0x40025010))
#define PF3       (*((volatile uint32_t *)0x40025020))
	
volatile int delay = 0;

extern uint32_t data;
extern uint8_t flag;  
	uint32_t temp = 0;
void PortF_Init(void){
  SYSCTL_RCGCGPIO_R |= 0x00000020;  // 1) activate clock for Port F
  delay = SYSCTL_RCGCGPIO_R;        // allow time for clock to start
  GPIO_PORTF_LOCK_R = 0x4C4F434B;   // 2) unlock GPIO Port F
  GPIO_PORTF_CR_R = 0x1F;           // allow changes to PF4-0
  // only PF0 needs to be unlocked, other bits can't be locked
  GPIO_PORTF_AMSEL_R = 0x00;        // 3) disable analog on PF
  GPIO_PORTF_PCTL_R = 0x00000000;   // 4) PCTL GPIO on PF4-0
  GPIO_PORTF_DIR_R = 0x0E;          // 5) PF4,PF0 in, PF3-1 out
  GPIO_PORTF_AFSEL_R = 0x00;        // 6) disable alt funct on PF7-0
  GPIO_PORTF_PUR_R = 0x11;          // enable pull-up on PF0 and PF4
  GPIO_PORTF_DEN_R = 0x1F;          // 7) enable digital I/O on PF4-0
}
uint32_t temp;    // 32-bit fixed-point 0.001 cm

uint16_t count, ycoord, L, Speed;
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
		ST7735_DrawFastHLine(ycoord, temp/25, 2, ST7735_RED);
		ycoord += 2;
		count = 0;
	}
}

int main(void){
  TExaS_Init();
	ST7735_InitR(INITR_REDTAB);	
  PortF_Init();
  ADC0_InitSWTriggerSeq3_Ch9(); 
	SysTick_Init();
	EnableInterrupts();
  while(1){
		while(flag != 1){};    //Wait until ADCStatus flag is true
		
		flag = 0;
		temp = convert(data); 
		
		ST7735_SetCursor(0,0);
		ST7735_OutString("ADC output is: ");
		ST7735_OutUDec(data);
		ST7735_SetCursor(0,3);
		ST7735_OutString("Temp is: ");
		ST7735_OutUDec((temp/100)-10);
		ST7735_OutString(".");
		ST7735_OutUDec(temp%100);	
		ST7735_OutString("  C");
		ST7735_SetCursor(0,4);
		plotPoints();
  }
}
