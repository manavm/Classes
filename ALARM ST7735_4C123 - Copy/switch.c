#include <stdint.h>
#include "inc/tm4c123gh6pm.h"
#include "MainMenu.h"
#include "Clock.h"

extern int displaymode;
extern int alarm;
void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts
long StartCritical (void);    // previous I bit, disable interrupts
void EndCritical(long sr);    // restore I bit to previous value
void WaitForInterrupt(void);  // low power mode

// global variable visible in Watch window of debugger
// increments at least once per button press
volatile uint32_t FallingEdges = 0;
volatile unsigned char SW1, SW2;
volatile unsigned int sTime, sAlarm, onAlarm, onMode, sClock;
void Delay1ms(uint32_t n);

void PolledButtons_Init(void){         
	//SW1 = 0;
	//SW2 = 0;
  SYSCTL_RCGCGPIO_R |= 0x00000010; // (a) activate clock for port E
  FallingEdges = 0;             // (b) initialize counter
  GPIO_PORTE_DIR_R &= ~0x1F;    // (c) make PF4 in (built-in button)
  //GPIO_PORTE_AFSEL_R &= ~0x1F;  //     disable alt funct on PF4
  GPIO_PORTE_DEN_R |= 0x1F;     //     enable digital I/O on PF4   
  //GPIO_PORTE_PCTL_R &= ~0x000FFFFF; // configure PF4 as GPIO
  //GPIO_PORTE_AMSEL_R &= ~0x1F;       //     disable analog functionality on PF
  GPIO_PORTE_IS_R &= ~0x1F;     // (d) PF4 is edge-sensitive
  GPIO_PORTE_IBE_R &= ~0x1F;    //     PF4 is not both edges
  GPIO_PORTE_IEV_R |= 0x1F;    //     PF4 rising edge event
  GPIO_PORTE_ICR_R = 0x1F;      // (e) clear flag4
  GPIO_PORTE_IM_R |= 0x1F;      // (f) arm interrupt on PF4 *** No IME bit as mentioned in Book ***
  NVIC_PRI1_R = (NVIC_PRI0_R&0xFFFFFF00)|0x00000040; // (g) priority 5
  NVIC_EN0_R = NVIC_EN0_INT4;      // (h) enable interrupt 30 in NVIC
  EnableInterrupts();           // (i) Clears the I bit
}

void GPIOPortE_Handler(void){
	if(GPIO_PORTE_RIS_R & 0x01){
	//Delay1ms(60);
//if(GPIO_PORTE_RIS_R & 0x01){
		GPIO_PORTE_ICR_R = 0x01;      // acknowledge flag4
		sTime = 1;
//}
	}
  if(GPIO_PORTE_RIS_R & 0x02){
		//Delay1ms(60);
		 //if(GPIO_PORTE_RIS_R & 0x02){
		GPIO_PORTE_ICR_R = 0x02;      // acknowledge flag4
		sAlarm = 1;
		// }
	}
	if(GPIO_PORTE_RIS_R & 0x04){
		//DisableInterrupts();
		//Delay1ms(60);
		//if(GPIO_PORTE_RIS_R & 0x04){
		GPIO_PORTE_ICR_R = 0x04;      // acknowledge flag4
		onAlarm = 1;
	//	SetOn_Off();			temporaryily changing this to displayclock because we do not have a fifth button
			//EnableInterrupts();
	//}
}
	
	if(GPIO_PORTE_RIS_R & 0x08){
		//Delay1ms(60);
		//if(GPIO_PORTE_RIS_R & 0x08){
		GPIO_PORTE_ICR_R = 0x08;      // acknowledge flag4
		onMode = 1;
	//}
}
	
	if(GPIO_PORTE_RIS_R & 0x10){
		//Delay1ms(60);
		//if(GPIO_PORTE_RIS_R & 0x10){
		GPIO_PORTE_ICR_R = 0x10;      // acknowledge flag4
		sClock = 1;
	//}
}
	
}

void switchReset(void) {
	long sr;
	sr = StartCritical();
	sTime = 0;
	sAlarm = 0;
	onAlarm = 0;
	onMode = 0;
	sClock = 0;
	EndCritical(sr);
}

/*
void GPIOPortE_Handler(void){
	if(GPIO_PORTE_RIS_R & 0x01){
		DisableInterrupts();
		GPIO_PORTE_ICR_R = 0x01;      // acknowledge flag4
		SetTime();
		EnableInterrupts();
	}
  if(GPIO_PORTE_RIS_R & 0x02){
		DisableInterrupts();
		GPIO_PORTE_ICR_R = 0x02;      // acknowledge flag4
		SetAlarm();
		EnableInterrupts();
	}
	if(GPIO_PORTE_RIS_R & 0x04){
		//DisableInterrupts();
		GPIO_PORTE_ICR_R = 0x04;      // acknowledge flag4
	//	SetOn_Off();			temporaryily changing this to displayclock because we do not have a fifth button
		if(displaymode == 1){
		DisplayClockAnalog();
		}
		if(displaymode == 0){
		DisplayClockDigital();
		}
			//EnableInterrupts();
	}
	
	if(GPIO_PORTE_RIS_R & 0x08){
		DisableInterrupts();
		GPIO_PORTE_ICR_R = 0x08;      // acknowledge flag4
		ChangeDisplayMode();		//this is temporarily edited out to try out DisplayClock
		EnableInterrupts();
	}
	
	if(GPIO_PORTE_RIS_R & 0x40){
		GPIO_PORTE_ICR_R = 0x40;      // acknowledge flag4
		if(displaymode == 1){
		DisplayClockAnalog();
		}
		if(displaymode == 0){
		DisplayClockDigital();
		}
	}
	
}
*/
