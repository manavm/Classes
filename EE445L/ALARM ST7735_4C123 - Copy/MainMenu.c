//these functions are included in the main menu

#include <stdio.h>
#include <stdint.h>
#include "ST7735.h"
#include "PLL.h"
#include "inc/tm4c123gh6pm.h"
#include "Clock.h"

#define PF0   (*((volatile uint32_t *)0x40025004))
#define PF4   (*((volatile uint32_t *)0x40025040))
int hour = 12;
int hour_alarm = 12;
int minute = 0;
int minute_alarm = 0;
int alarm = 0;
int displaymode = 1;
//This function is used to Refresh the screen and display just the hours on SetTime
//Inputs: NONE
void RefreshSetTime(){
			ST7735_SetCursor(0,0);
			ST7735_FillScreen(0x0000);            // set screen to black
			ST7735_OutString("Input Time for Clock\n");
			ST7735_OutString("First Set the Hour\n");	
}
//This function is used to Refresh the screen and display hour+minutes on SetTime
//Inputs: the hour you recieved from the first half of SetTime
void	RefreshSetTime2(int hour_b4){
			ST7735_SetCursor(0,0);
			ST7735_FillScreen(0x0000);            // set screen to black
			ST7735_OutString("Input Time for Clock\n");
			ST7735_OutString("First Set the Hour\n");
			printf("%u",hour_b4);
			ST7735_OutString("\n");	
			ST7735_OutString("Set the Minute\n");	
}
// Subroutine to wait 10 msec
// Inputs: None
// Outputs: None
// Notes: ...
void DelayWait10ms(uint32_t n){uint32_t volatile time;
  while(n){
    time = 727240*2/91;  // 10msec
    while(time){
	  	time--;
    }
    n--;
  }
}
//This subroutine is used to Set the Time
void SetTime(){
	RefreshSetTime();
			//begin polling for hour
		printf("0");
DelayWait10ms(100);
	while(PF4 != 0){
		if (PF0 == 0){
		DelayWait10ms(30);
				if (PF0 == 1){
				hour = hour - 1;
						if( hour < 1){
							hour = 12;
						}
				RefreshSetTime();
				printf("%u",hour);
				}
		}
/*		if(PD1 == 1){
		DelayWait10ms(30);
				if(PD1 == 1){		
				hour = hour + 1;
					if(hour > 12){
					hour = 1;
					}
				RefreshSetTime();
				printf("%u",hour);
				}
		}
		*/
				
	}
			//actively update variable hour
			//selection button is pressed
	ST7735_OutString("\n");	
	ST7735_OutString("Set the Minute\n");
	printf(":0");
	DelayWait10ms(100);
	while(PF4 != 0){
		if (PF0 == 0){
		DelayWait10ms(30);
			if (PF0 == 0){
			minute = minute + 1;
				if( minute > 59){
				minute = 0;
				}	
			RefreshSetTime2(hour);
				if(minute < 10){
				printf(":0%u",minute);
				}
				if(minute >= 10){
				printf(":%u\n",minute);
				}
			}
		}	
/*		
		if(PD1 == 1){
		DelayWait10ms(30);
			if (PD1 == 1){
			minute = minute + 1;
				if(minute > 59){
				minute = 0;
				}
				RefreshSetTime();
					if(minute < 10){
					printf(":0%u",minute);
					}
					else{
					printf(":%u/n",minute);
					}
			}
		}
*/
	}
					ST7735_SetCursor(0,0);
			ST7735_FillScreen(0x0000);            // set screen to black
			printf("CLOCK\nMAIN MENU\n\n\n\n\nPress 1 :SET TIME\nPress 2 :SET ALARM\nPress 3:ALRM ON/OFF\nPress 4 :DISPLAY CLK");
}
//This Function is used to Refresh the Screen while setting the Alarm. Hour Displayed Only
//Inputs: NONE
void RefreshSetAlarm(){
			ST7735_SetCursor(0,0);
			ST7735_FillScreen(0x0000);            // set screen to black
			ST7735_OutString("Input Alarm Time\n");
			ST7735_OutString("First Set the Hour\n");	
}
//This Function is used to Refresh the Screen while Setting the Alarm. Hour:Minutes displayed
//Inputs: Hour variable.
void	RefreshSetAlarm2(int hour_b4){
			ST7735_SetCursor(0,0);
			ST7735_FillScreen(0x0000);            // set screen to black
			ST7735_OutString("Input Alarm Time\n");
			ST7735_OutString("First Set the Hour\n");
			printf("%u\n",hour_b4);
			ST7735_OutString("Set the Minute\n");	
}
//This Funciton is used to Set the Alarm
void SetAlarm(){
		RefreshSetAlarm();
			//begin polling for hour
		printf("12");
DelayWait10ms(100);
	while(PF4 != 0){
		if (PF0 == 0){
		DelayWait10ms(30);
				if (PF0 == 0){
				hour_alarm = hour_alarm - 1;
						if( hour_alarm < 1){
							hour_alarm = 12;
						}
				RefreshSetAlarm();
				printf("%u",hour_alarm);
				}
		}
		/*
		if(PD1 == 1){
		DelayWait10ms(30);
				if(PD1 == 1){		
				hour_alarm = hour_alarm + 1;
					if(hour_alarm > 12){
					hour_alarm = 1;
					}
				RefreshSetAlarm();
				printf("%u",hour_alarm);
				}
		}
		*/
				
		}
			//actively update variable hour
			//selection button is pressed
			ST7735_OutString("\n");	
			ST7735_OutString("Set the Minute\n");
			printf(":0");
			DelayWait10ms(100);
			while(PF4 != 0){
				if (PF0 == 0){
					DelayWait10ms(30);
					if (PF0 == 0){
					minute_alarm = minute_alarm + 1;
					if( minute_alarm > 59){
						minute_alarm = 0;
				}
					
				RefreshSetAlarm2(hour_alarm);
				if(minute_alarm < 10){
					printf(":0%u",minute_alarm);
				}
				if(minute_alarm >10){
					printf(":%u\n",minute_alarm);
			}
		}
		}
	}		
/*			
				if(PD1 == 1){
					DelayWait10ms(30);
					if (PD1 == 1){
					minute_alarm = minute_alarm + 1;
					if(minute_alarm > 59){
						minute_alarm = 0;
				RefreshSetAlarm2(hour_alarm);
					if(minute_alarm < 10){
					printf(":0%u",minute_alarm);
				}
						printf(":%u/n",minute_alarm);
					}
				}
			}
	*/
				ST7735_SetCursor(0,0);
			ST7735_FillScreen(0x0000);            // set screen to black
		printf("CLOCK\nMAIN MENU\n\n\n\n\nPress 1 :SET TIME\nPress 2 :SET ALARM\nPress 3:ALRM ON/OFF\nPress 4 :DISPLAY CLK");
};
//This Function is used to Set the Alarm Either On or Off
void SetOn_Off(){
			ST7735_SetCursor(0,0);
			ST7735_FillScreen(0x0000);            // set screen to black
	if(alarm == 1){
		printf("\nALARM IS ON");
	}
	if(alarm == 0){
		printf("\nALARM IS OFF");
	}
	printf("\nTO CHANGE ALARM\n PRESS BUTTON\n");
//	printf("if not, press back\n");
	while(PF4 != 0){
}
		if (alarm == 0){
			alarm = 1;
		}
		else if (alarm == 1){
			alarm = 0;
		}
	if(alarm == 1){
		printf("ALARM IS ON");
	}
	if(alarm == 0){
		printf("ALARM IS OFF");
		}
DelayWait10ms(500);	
DelayWait10ms(500);
						ST7735_SetCursor(0,0);
			ST7735_FillScreen(0x0000);            // set screen to black
		printf("CLOCK\nMAIN MENU\n\n\n\n\nPress 1 :SET TIME\nPress 2 :SET ALARM\nPress 3:ALRM ON/OFF\nPress 4 :DISPLAY CLK");

	}
//This Function is used to Start the Display Mode
void ChangeDisplayMode(){
				ST7735_SetCursor(0,0);
			ST7735_FillScreen(0x0000);            // set screen to black
	if(displaymode == 1){
		printf("ANALOG IS ON\n");
	}
	if(displaymode == 0){
		printf("DIGITAL IS ON\n");
	}
	printf("\nTO CHANGE DISPLAY \nMODE PRESS BUTTON\n");
	printf("if not, press back\n");
	while(PF4 != 0){
		if(PF0 == 0){
			DelayWait10ms(50);
				if(PF0 == 0){
			if(displaymode == 0){
				displaymode = 1;
			}
			else if(displaymode == 1){
				displaymode = 0;
			}
		}
	}
	}
		if(displaymode == 1){
		printf("ANALOG IS ON\n");
	}
	if(displaymode == 0){
		printf("DIGITAL IS ON\n");
	}
DelayWait10ms(500);	
DelayWait10ms(500);
				ST7735_SetCursor(0,0);
			ST7735_FillScreen(0x0000);            // set screen to black
	printf("CLOCK\nMAIN MENU\n\n\n\n\nPress 1 :SET TIME\nPress 2 :SET ALARM\nPress 3:ALRM ON/OFF\nPress 4 :DISPLAY CLK");
}
