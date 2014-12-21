#include "ST7735.h"
#include <math.h>
#include <stdio.h>
#include <stdint.h>
#define PI 3.14159265358979323846



int old_minute;
int old_hour;

int	old_xHr;
int	old_yHr;
int	old_xMin;
int	old_yMin;

void displayAnalog(int hour, int minutes){		//called by periodic interrupt to update time display
		int centerX = 59, centerY = 74;
	int xMin, yMin, xHr, yHr, newminutes,newhour;
	ST7735_Line(centerX, centerY, old_xHr, old_yHr, ST7735_BLACK);
	ST7735_Line(centerX, centerY, old_xMin, old_yMin, ST7735_BLACK);

	if( minutes >= 0){
		if (minutes <= 30){
		newminutes = abs(minutes - 30);
		}
		else if( minutes > 30){
			newminutes = abs((-1*minutes) + 90);
		}
}
	if(hour >= 6){
		newhour = abs((-1*hour)+18);
	}
	else if(hour < 6){
		newhour = abs((-1*hour)+6);
	}


	xHr = 59 + 25*sin(((newhour%12 - minutes%60 / 60.0)*PI)/6);

	yHr = 74 + 25*cos(((newhour%12 - minutes%60 / 60.0)*PI)/6);

	xMin =59 + 40*sin((newminutes%60 * PI)/30);

	yMin = 74 + 40*cos((newminutes%60 * PI)/30);

	ST7735_Line(centerX, centerY, xHr, yHr, ST7735_GREEN);
	ST7735_Line(centerX, centerY, xMin, yMin, ST7735_RED);
	old_xHr = xHr;
	old_yHr = yHr;
	old_xMin = xMin;
	old_yMin = yMin;
}
	
void displayDigital(int hours, int minutes, int seconds){
		ST7735_InitR(INITR_REDTAB);	
}

void displayAlarm(int hours, int minutes, int seconds){
	ST7735_InitR(INITR_REDTAB);
}
