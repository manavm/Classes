#include <stdint.h>
#include "inc/tm4c123gh6pm.h"
#define NVIC_ST_CTRL_COUNT      0x00010000  // Count flag
#define NVIC_ST_CTRL_CLK_SRC    0x00000004  // Clock Source
#define NVIC_ST_CTRL_INTEN      0x00000002  // Interrupt enable
#define NVIC_ST_CTRL_ENABLE     0x00000001  // Counter mode
#define FIFTHSECOND							0x00242400  // Counter load value

uint8_t Screen_Update = 0;

// Initialize SysTick Interrupt.
void SysTick_Init(void){
  NVIC_ST_CTRL_R = 0;                   // disable SysTick during setup
  NVIC_ST_RELOAD_R = FIFTHSECOND - 1;  			// 0.2s reload value
  NVIC_ST_CURRENT_R = 0;                // any write to current clears it
                                        // enable SysTick with core clock
	NVIC_SYS_PRI3_R = (NVIC_SYS_PRI3_R & 0x00FFFFFF) | 0x40000000; //priority 2
  NVIC_ST_CTRL_R = 0x00000007;
}


void SysTick_Handler(void) {
	Screen_Update = 1;
	GPIO_PORTF_DATA_R ^= 0x02;   // toggle
}