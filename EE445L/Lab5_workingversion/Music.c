#include <stdint.h>
#include "Switch.h"
#include "DAC.h"
#include "Timer0A.h"
#include "Music.h"
#include "SysTick.h"
int i, j;
extern uint32_t play, rewind, mode, pause;
extern int Time, lenPush, notePush;

void Music_Play(const unsigned short *instrument, int instrumentSize, const struct Songs* song, int songSize){
		int noteIndex=0;
		int i=0;
		int pause=0;	
	
	while(1){
		if(play){
			pause=1-pause;
			resetSwitches();
		}
		if(rewind||mode){
			break;
		}
		if(lenPush&&!pause){
			Timer0A_Init(song->duration[noteIndex]);
			SysTick_Init(402000/(song->notes[noteIndex]));
			noteIndex=(noteIndex+1)%songSize;
		}
		if(notePush&&!pause){
			notePush=0;
			DAC_Out(instrument[i]);
			i=(i+1)%instrumentSize;
		}
	}

	/*
	//in class he mentioned something about having to layer two interrupts ontop of each other and how that can help, we may 
	//have to do something with that. I plan on asking the TA's about it tomorrow.
		DAC_Out(song->notes[Time&0x1F] + instrument[Time&0x1F]);
	//	DAC_Out(song->notes[Time&0x1F]);
	//	DAC_Out(instrument[Time&0x1F]);
    Time = Time + 1;
		SysTick_Wait(song->duration[Time&0x1F]);
	*/
}

