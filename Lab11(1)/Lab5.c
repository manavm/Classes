#include <stdint.h>
#include "inc/tm4c123gh6pm.h"
#include "Switch.h"
#include "DAC.h"
#include "PLL.h"
#include "Timer0A.h"
#include "SysTick.h"
#include "ST7735.h"
#include "plotImage.h"


#define NVIC_EN0_INT4           0x00000010  // Interrupt 4 enable
#define F16HZ (50000000/16)

extern struct Songs *strobePtr;
void Music_Play(const unsigned short, int, const struct Songs* song, int);
extern uint32_t play, rewind, mode, pause;
extern int i,j, lenPush;
extern const unsigned short Trumpet[32], Horn[32],Wave[32],Flute[32],dt[32];
int hor, flut = 0;
int trump = 1;
//--HeartBeat_Init--
//Initialize PF2 Onboard Heartbeat
void HeartBeat_Init(void){
	                                   // activate port F
  SYSCTL_RCGCGPIO_R |= 0x20;
  while((SYSCTL_PRGPIO_R&0x0020) == 0){};// ready?
  GPIO_PORTF_DIR_R |= 0x04;        // make PF2 out (built-in LED)
  GPIO_PORTF_AFSEL_R &= ~0x04;     // disable alt funct on PF2
  GPIO_PORTF_DEN_R |= 0x04;        // enable digital I/O on PF2
                                   // configure PF2 as GPIO
  GPIO_PORTF_PCTL_R = (GPIO_PORTF_PCTL_R&0xFFFFF0FF)+0x00000000;
  GPIO_PORTF_AMSEL_R = 0;          // disable analog functionality on PF
	}


extern unsigned short Time;
//debug code
	
int main1(void){
	PLL_Init();
  ST7735_InitR(INITR_REDTAB);
	while(1){
		plotImage();
	}
}

int main(void){
	//PLL_Init(); //16MHZ bus clock //when PLL is on, nothing works
	HeartBeat_Init();
	//SysTick_Init();
  PolledButtons_Init();       // initialize interrupts and ports
	DAC_Init(1024);							// initialize with command: Vout = Vref
//	DAC_Init(0x1000);                  // initialize with command: Vout = Vref
	//Timer0A_Init(dt[0]);
	Board_Init();		//Initalize the On Board Switches
	Switch_Init2(); //i used the board switches because our switches were doing the thing
							//where they worked for a bit then they stopped working again
	lenPush = 1;
	int instrument = 0;

			
			
	while(1){
		if(mode){
			resetSwitches();	
			
			if (instrument == 0){
				Music_Play(Wave[0], 32, strobePtr, 35);	
				instrument += 1;
			}
			else if (instrument == 1){
				Music_Play(Trumpet[0], 32, strobePtr, 35);
				instrument += 1;
			}
			else if (instrument == 2){
				Music_Play(Flute[0], 32, strobePtr, 35);
				instrument = 0;
			}
		}
		else if(play){
			resetSwitches();
			if (instrument == 0){
				Music_Play(Wave[0], 64, strobePtr, 35);		
			}
			if (instrument == 1){
				Music_Play(Trumpet[0], 32, strobePtr, 35);
			}
			if (instrument == 2){
				Music_Play(Flute[0], 32, strobePtr, 35);
			}
		}
	}
}

		/*
		GPIO_PORTF_DATA_R = GPIO_PORTF_DATA_R^0x04;	//heartbeat, feel free to move around for debugging purposes
		
    if(play){
			//		resetSwitches();		//can't just reset all the switches because then it doesn't continue to play, need a seperate pause button
			if(trump == 1){
			Music_Play(Trumpet[0], 32, strobePtr, 21);
			}
			else if( hor == 1){	
			Music_Play(Horn[0], 32, strobePtr, 21);		
			}
			else if(flut == 1){
			Music_Play(Flute[0], 32, strobePtr, 21);	
			}	
			
		}
		if(rewind){ //button to rewind (currently does not work)
			resetSwitches();}
		
		if(pause){ //button to pause (currently does not work)
		play = 0;
		pause = 0;
		}
		
		if(mode){	//code to toggle between modes
			if(trump == 1){
				trump = 0;
				hor = 1;}
					else if( hor == 1){
					hor = 0;
					flut = 1;}
						else if(flut == 1){
						flut = 0;
						trump = 1;}	
			mode = 0;
		}
		*/


		/*
	 DAC_Out(Horn[Time&0x1F]);
    Time = Time + 1;
		SysTick_Wait(dt[Time&0x1F]);    
		*/
	
    // calculated frequencies are not exact, due to the impreciseness of delay loops
    // assumes using 16 MHz PIOSC (default setting for clock source)
    // maximum frequency with 16 MHz PIOSC: (8,000,000 bits/1 sec)*(1 sample/16 bits)*(1 wave/32 sample) = 15,625 Hz
    // maximum frequency with 20 MHz PLL: (10,000,000 bits/1 sec)*(1 sample/16 bits)*(1 wave/32 sample) = 19,531.25 Hz
//    SysTick_Wait(0);                 // ?? kHz sine wave (actually 12,000 Hz)
//    SysTick_Wait(9);                 // 55.6 kHz sine wave (actually 10,000 Hz)
//    SysTick_Wait(15);                // 33.3 kHz sine wave (actually 8,500 Hz)
//    SysTick_Wait(19);                // 26.3 kHz sine wave (actually 8,500 Hz)
//    SysTick_Wait(64);                // 7.81 kHz sine wave (actually 4,800 Hz)
//    SysTick_Wait(99);                // 5.05 kHz sine wave (actually 3,500 Hz)
//    SysTick_Wait(1136);              // 440 Hz sine wave (actually 420 Hz)

