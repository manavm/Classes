int height = 70
int r;
void plotImage(void){
		count = count + 1;
		if (count == 2){
		if(ycoord == 0){
		ST7735_PlotClear(0,4095);  // range from 0 to 4095
		}
		if(ycoord == 128){s
		
    		ST7735_PlotClear(0,4095);  // range from 0 to 4095
			ycoord = 0;
		}
		ST7735_DrawFastHLine(0, height-10, 10, ST7735_BLUE);
		ST7735_DrawFastHLine(11, height+10, 10, ST7735_BLUE);
		ST7735_DrawFastHLine(22, height+14, 10, ST7735_BLUE);
		ST7735_DrawFastHLine(33, height+20, 10, ST7735_BLUE);
		ST7735_DrawFastHLine(44, height-12, 10, ST7735_BLUE);
		ST7735_DrawFastHLine(55, height+18, 10, ST7735_BLUE);
		ST7735_DrawFastHLine(66, height-20, 10, ST7735_BLUE);
		ST7735_DrawFastHLine(77, height+30, 10, ST7735_BLUE);
		ST7735_DrawFastHLine(88, height-2, 10, ST7735_BLUE);
		ST7735_DrawFastHLine(99, height, 10, ST7735_BLUE);
		ST7735_DrawFastHLine(110, height+15, 10, ST7735_BLUE);
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
