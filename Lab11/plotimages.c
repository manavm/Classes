#include "ST7735.h"
#include "math.h"
#include "stdlib.h"

int count = 0;
int ycoord = 0;
int height = 70;
int r;
int bar;
int flagg = 1;
int hbar1, hbar2, hbar3, hbar4, hbar5, hbar6, hbar7, hbar8, hbar9, hbar10, hbar11, hbar12, hbar13, hbar14, hbar15, hbar16;

void plotImage(void){
	if(flagg == 1){
		//this initially sets all the variables
	ST7735_OutString("   WELCOME HOME DJ\n");
//  ST7735_OutString("   EE445L VALVANO\n");
	ST7735_OutString("  Nick E. & Manav M.\n");
	ST7735_OutString("Press Button 2 Begin");			
				hbar1 = rand()%140;
				hbar2 = rand()%160;
				hbar3 = rand()%120;
				hbar4 = rand()%140;
				hbar5 = rand()%145;
				hbar6 = rand()%110;
				hbar7 = rand()%160;
				hbar8 = rand()%189; 				
				hbar9 = rand()%120;
				hbar10 = rand()%111;
				hbar11 = rand()%116;
				hbar12 = rand()%144;
				hbar13 = rand()%100;
				hbar14 = rand()%99;
				hbar15 = rand()%170;
				hbar16 = rand()%200;
				flagg = 0;
	}
				if(hbar1<70){
			hbar1 = 70;
			}
			if(hbar1 >140){
			hbar1 = 135;
			}
			
			if(hbar2<70){
			hbar2 = 70;
			}			
			if(hbar2 >140){
			hbar2 = 135;
			}
			
			if(hbar3<70){
			hbar3 = 70;
			}
			if(hbar3 >140){
			hbar3 = 135;
			}
			
			if(hbar4<70){
			hbar4 = 70;
			}
			if(hbar4 >140){
			hbar4 = 135;
			}
						
			if(hbar5<70){
			hbar5 = 70;
			}
			if(hbar5 >140){
			hbar5 = 135;
			}
			
			if(hbar6<70){
			hbar6 = 70;
			}
			if(hbar6 >140){
			hbar6 = 135;
			}
			
			if(hbar7<70){
			hbar7 = 70;
			}
			if(hbar7 >140){
			hbar7 = 135;
			}
			
			if(hbar8<70){
			hbar8 = 70;
			}
			if(hbar8 >140){
			hbar8 = 135;
			}
			
			if(hbar9<70){
			hbar9 = 70;
			}
			if(hbar9 >140){
			hbar9 = 135;
			}
			
			if(hbar10<70){
			hbar10 = 70;
			}			
			if(hbar10 >140){
			hbar10 = 135;
			}
			
			if(hbar11<70){
			hbar11 = 70;
			}
			if(hbar11 >140){
			hbar11 = 135;
			}
			
			if(hbar12<70){
			hbar12 = 70;
			}
			if(hbar12 >140){
			hbar12 = 135;
			}
						
			if(hbar13<70){
			hbar13 = 70;
			}
			if(hbar13 >140){
			hbar13 = 135;
			}
			
			if(hbar14<70){
			hbar14 = 70;
			}
			if(hbar14 >140){
			hbar14 = 135;
			}
			
			if(hbar15<70){
			hbar15 = 70;
			}
			if(hbar15 >140){
			hbar15 = 135;
			}
			
			if(hbar16<70){
			hbar16 = 70;
			}
			if(hbar16 >140){
			hbar16 = 135;
			}

        count = count + 1;
        if (count == 5000){
        if(ycoord == 0){
        ST7735_PlotClear(0,4095);  // range from 0 to 4095
        }
 
				//start of bar 1
				bar = 0;
				while(bar < 8){
				ST7735_DrawFastVLine(bar, hbar1, 200, ST7735_BLUE);
				bar +=1;
				}
				//end of bar 1
				
				//start of bar 2			
				while(bar < 16){
				ST7735_DrawFastVLine(bar, hbar2, 200, ST7735_RED);
				bar +=1;
				}
				//end of bar 2
				
				//start of bar 3			
				while(bar < 24){
				ST7735_DrawFastVLine(bar, hbar3, 200, ST7735_GREEN);
				bar +=1;
				}
				//end of bar 3
				
				//start of bar 4			
				while(bar < 32){
				ST7735_DrawFastVLine(bar, hbar4, 200, ST7735_BLUE);
				bar +=1;
				}
				//end of bar 4
				
				//start of bar 5			
				while(bar < 40){
				ST7735_DrawFastVLine(bar, hbar5, 200, ST7735_RED);
				bar +=1;
				}
				//end of bar 5
				
				//start of bar 6			
				while(bar < 48){
				ST7735_DrawFastVLine(bar, hbar6, 200, ST7735_GREEN);
				bar +=1;
				}
				//end of bar 6
				
				//start of bar 7			
				while(bar < 56){
				ST7735_DrawFastVLine(bar, hbar7, 200, ST7735_BLUE);
				bar +=1;
				}
				//end of bar 7
				
				//start of bar 8			
				while(bar < 64){
				ST7735_DrawFastVLine(bar, hbar8, 200, ST7735_RED);
				bar +=1;
				}
				//end of bar 8
				
				//start of bar 9			
				while(bar < 72){
				ST7735_DrawFastVLine(bar, hbar9, 200, ST7735_GREEN);
				bar +=1;
				}
				//end of bar 9
				
				//start of bar 10			
				while(bar < 80){
				ST7735_DrawFastVLine(bar, hbar10, 200, ST7735_BLUE);
				bar +=1;
				}
				//end of bar 10
				
				//start of bar 11			
				while(bar < 88){
				ST7735_DrawFastVLine(bar, hbar11, 200, ST7735_RED);
				bar +=1;
				}
				//end of bar 11
				
				//start of bar 12			
				while(bar < 96){
				ST7735_DrawFastVLine(bar, hbar12, 200, ST7735_GREEN);
				bar +=1;
				}
				//end of bar 12
				
				//start of bar 13			
				while(bar < 104){
				ST7735_DrawFastVLine(bar, hbar13, 200, ST7735_BLUE);
				bar +=1;
				}
				//end of bar 13
				
				//start of bar 14			
				while(bar < 112){
				ST7735_DrawFastVLine(bar, hbar14, 200, ST7735_RED);
				bar +=1;
				}
				//end of bar 14
				
				//start of bar 15			
				while(bar < 120){
				ST7735_DrawFastVLine(bar, hbar15, 200, ST7735_GREEN);
				bar +=1;
				}
				//end of bar 15
				
				//start of bar 16			
				while(bar < 128){
				ST7735_DrawFastVLine(bar, hbar16, 200, ST7735_BLUE);
				bar +=1;
				}
				//end of bar 16

		r = rand();//need a random number generator
		if( r< RAND_MAX/2){
		hbar1 += 5; hbar2 += 7; hbar4 += 5; hbar5 += 2; hbar8 += 1; hbar3 -= 5; hbar7 -= 10;
			hbar9 += 6; hbar10 += 7;hbar12 += 3;  hbar14 += 5; hbar16 += 4; hbar13 -= 5; hbar15 -= 9; hbar6 -= 5; hbar11 -= 5;
		}
		else{
		hbar1 -= 3; hbar2 -= 7;hbar4 -= 4; hbar5 -= 3; hbar8 -= 1;
		hbar9 -= 1; hbar10 -= 7; hbar12 -= 3;  hbar14 -= 4; hbar16 -= 4;
			hbar3 += 5; hbar13 += 5; hbar7 += 12; hbar15 += 9;  hbar6 += 5; hbar11 += 5; 
		}
		count = 0;
	}
}

