#include <stdint.h>
#include "inc/tm4c123gh6pm.h"



//unsigned long H,L = 1400, button_push;
signed long H,L = 1000, interrupt;
void Motor_Init(void){
  SYSCTL_RCGC2_R |= 0x00000001; // activate clock for port A
  L = H = 2368512;                // 50%
  GPIO_PORTA_AMSEL_R &= ~0x10;      // disable analog functionality on PA4
  GPIO_PORTA_PCTL_R &= ~0x000F0000; // configure PA4 as GPIO
  GPIO_PORTA_DIR_R |= 0x10;     // make PA4 out
  GPIO_PORTA_DR8R_R |= 0x10;    // enable 8 mA drive on PA4
  GPIO_PORTA_AFSEL_R &= ~0x10;  // disable alt funct on PA4
  GPIO_PORTA_DEN_R |= 0x10;     // enable digital I/O on PA4
  GPIO_PORTA_DATA_R &= ~0x10;   // make PA5 low
  NVIC_ST_CTRL_R = 0;           // disable SysTick during setup
  NVIC_ST_RELOAD_R = H-1;       // reload value for 500us
  NVIC_ST_CURRENT_R = 0;        // any write to current clears it
  NVIC_SYS_PRI3_R = (NVIC_SYS_PRI3_R&0x00FFFFFF)|0x40000000; // priority 2
  NVIC_ST_CTRL_R = 0x00000007;  // enable with core clock and interrupts
}

void SysTick_Handler(void){
  interrupt = 1;
}
