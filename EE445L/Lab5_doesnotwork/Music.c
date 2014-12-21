#include <stdint.h>
#include "Switch.h"
#include "DAC.h"
#include "Timer0A.h"
#include "Music.h"
#include "SysTick.h"
int i, j;
extern uint32_t play, rewind, mode, pause;
extern uint16_t Time, lenPush, notePush;

void Music_Play(const uint16_t *instrument, uint16_t instrLen, const struct Songs* song, uint16_t songLen){
	
	uint16_t i=0;
	uint16_t j=0;
	uint16_t pause=0;			// Start off at pause, until play button is pressed
	
	while(1){
		if(play){							// Toggle play/pause
			pause = 1-pause;
			resetSwitches();
		}
		
		if(rewind||mode){			// Back to main if rewind or mode is pressed
			break;
		}
		
		if(lenPush&&!pause){									
			SysTick_Init(400000/((*song).notes[j]));
			Timer0A_Init((*song).duration[j]);
			j = (j+1) % songLen;
		}

		
		if(notePush&&!pause){
			notePush=0;								// Acknowledge
			DAC_Out(instrument[i]);
			i = (i+1) % instrLen;
		}
		
	}


}

