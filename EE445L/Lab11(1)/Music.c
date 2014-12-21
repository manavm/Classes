#include <stdint.h>
#include "Switch.h"
#include "DAC.h"
#include "Timer0A.h"
#include "Timer1A.h"
#include "Music.h"
#include "SysTick.h"
int i, j;
extern uint32_t play, rewind, pause;
extern uint32_t bNote, fNote, aNote, eNote;
extern int Time, lenPush, notePush;
extern struct Songs *furElisePtr;
extern struct Songs *demoPtr;
extern struct Songs *demo1Ptr;


void Music_Play(const unsigned short *instrument, int instrumentSize, const struct Songs* song, int songSize){
		int noteIndex=0;
		int i=0;
		int pause=0;	
		const unsigned short *testInstr;
		testInstr = &Flute[0];
		
	while(1){
		if(play){
			pause=1-pause;
			resetSwitches();
		}
		if(aNote){
			demoPtr->notes[noteIndex] = 1776;
			demoPtr->duration[noteIndex] = 10000;
			lenPush = 1;
			aNote = 0;
		}
		if(fNote){
			demoPtr->notes[noteIndex] = 2237;
			demoPtr->duration[noteIndex] = 10000;
			lenPush = 1;
			fNote = 0;
		}
		if(bNote){
			demoPtr->notes[noteIndex] = 1582;
			demoPtr->duration[noteIndex] = 10000;
			lenPush = 1;
			bNote = 0;
		}
		if(eNote){
			demoPtr->notes[noteIndex] = 2370;
			lenPush = 1;
			eNote = 0;
		}
		
		if(lenPush&&!pause){
			Timer0A_Init(demoPtr->duration[noteIndex]);
			Timer1A_Init(demoPtr->duration[noteIndex]);
			//SysTick_Init(402000/(song->notes[noteIndex]));
			//SysTick_Init(402000/(furElisePtr->notes[noteIndex]));
			SysTick_Init(402000/(demoPtr->notes[noteIndex]));
			//SysTick_Init(402000/(demo1Ptr->notes[noteIndex])); 			
			noteIndex=(noteIndex+1)%(songSize);
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

