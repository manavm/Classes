#include <stdint.h>
#include "ST7735.h"
#include <stdlib.h>
#include "Music.h"

int height = 70;
int r;
int val;
uint32_t ycoord = 0, count = 0;

extern int songSize;



void plotImage(void){
		count = count + 1;
		if (count == 2){
		if(ycoord == 0){
		ST7735_PlotClear(0,4095);  // range from 0 to 4095
		}
		if(ycoord == 128){
		
    	ST7735_PlotClear(0,4095);  // range from 0 to 4095
			ycoord = 0;
		}
		
		uint16_t noteCount = 0;
		while (noteCount < songSize){
		val = demoPtr->notes[noteCount];
			
		if(val == 1776)
			ST7735_OutString("A");

		if(val == 1582)
			ST7735_OutString("B");
		
		if(val == 2237)
			ST7735_OutString("E");
		
		if(val == 2370)
			ST7735_OutString("F");
		noteCount += 1;
	}
		
ST7735_DrawFastVLine(0, height-10, 50, ST7735_BLUE);
ST7735_DrawFastVLine(11, height+10, 50, ST7735_BLUE);
ST7735_DrawFastVLine(22, height+14, 50, ST7735_BLUE);
ST7735_DrawFastVLine(33, height+20, 50, ST7735_BLUE);
ST7735_DrawFastVLine(44, height-12, 50, ST7735_BLUE);
ST7735_DrawFastVLine(55, height+18, 50, ST7735_BLUE);
ST7735_DrawFastVLine(66, height-20, 50, ST7735_BLUE);
ST7735_DrawFastVLine(77, height+30, 50, ST7735_BLUE);
ST7735_DrawFastVLine(88, height-2, 50, ST7735_BLUE);
ST7735_DrawFastVLine(99, height, 50, ST7735_BLUE);
ST7735_DrawFastVLine(110, height+15, 50, ST7735_BLUE);
		r = rand();//need a random number generator
		if( r< RAND_MAX/2){
		height += 2;
		}
		else{
		height -= 2;
		}
		if(height<70){
		height = 70;
		}
		if(height >140){
		height = 70;
		}
		count = 0;
	}
}
