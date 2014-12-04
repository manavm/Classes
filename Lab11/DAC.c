#include <stdint.h>
#include "inc/tm4c123gh6pm.h"
#define PD0 (*((volatile unsigned long *)0x40007004))
#define PD1 (*((volatile unsigned long *)0x40007008)) 
#define PD2 (*((volatile unsigned long *)0x40007010))
#define PD3 (*((volatile unsigned long *)0x40007020))
//********DAC_Init*****************
// Initialize Max5353 12-bit DAC
// inputs:  initial voltage output (0 to 4095)
// outputs: none
// assumes: system clock rate less than 20 MHz
void DAC_Init2(uint16_t data){
  SYSCTL_RCGCSSI_R |= 0x01;       // activate SSI0
  SYSCTL_RCGCGPIO_R |= 0x01;      // activate port A
  while((SYSCTL_PRGPIO_R&0x01) == 0){};// ready?
  GPIO_PORTA_AFSEL_R |= 0x2C;     // enable alt funct on PA2,3,5
  GPIO_PORTA_DEN_R |= 0x2C;       // configure PA2,3,5 as SSI
  GPIO_PORTA_PCTL_R = (GPIO_PORTA_PCTL_R&0xFF0F00FF)+0x00202200;
  GPIO_PORTA_AMSEL_R = 0;         // disable analog functionality on PA
  SSI0_CR1_R = 0x00000000;        // disable SSI, master mode
  SSI0_CPSR_R = 0x02;             // 8 MHz SSIClk 
  SSI0_CR0_R &= ~(0x0000FFF0);    // SCR = 0, SPH = 0, SPO = 0 Freescale
  SSI0_CR0_R |= 0x0F;             // DSS = 16-bit data
  SSI0_DR_R = data;               // load 'data' into transmit FIFO
  SSI0_CR1_R |= 0x00000002;       // enable SSI

}

//********DAC_Out*****************
// Send data to Max5353 12-bit DAC
// inputs:  voltage output (0 to 4095)
// outputs: none
void DAC_Out2(uint16_t code){   
  while((SSI0_SR_R&0x00000002)==0){};// SSI Transmit FIFO Not Full
  SSI0_DR_R = code; 
}                // data out, no reply
  
//GPIO DAC//
void DAC_Init(void){ volatile unsigned long delay;
 SYSCTL_RCGC2_R |= 0x00000008; // activate port D
 delay = SYSCTL_RCGC2_R;
 GPIO_PORTD_DIR_R |= 0x0B; // PD3, PD1, PD0 outputs
 GPIO_PORTD_DEN_R |= 0x0B; // enable digital I/O on PD3, PD1, PD0
 GPIO_PORTD_AFSEL_R &= ~0x0B; // regular port function 

 PD3 = 0;
 PD0 = 1;
} 
int h = 0;
void delay(void){
	while(h < 1000){
		h +=h;
	}
	h = 0;
}
void DAC_Out(unsigned char data){
 // faster
 PD0 = 0; // frame select low
	//delay();
// bit 7
 PD3 = data>>6; // bit 1 is high or low depending on bit 7
 PD1 = 2; // clock high
	//delay();
 PD1 = 0; // clock low
// bit 6
 PD3 = data>>5; // bit 1 is high or low depending on bit 6
 PD1 = 2; // clock high
	//delay();
 PD1 = 0; // clock low
// bit 5
 PD3 = data>>4; // bit 1 is high or low depending on bit 5
 PD1 = 2; // clock high
//	delay();
 PD1 = 0; // clock low
// bit 4
 PD3 = data>>3; // bit 1 is high or low depending on bit 4
 PD1 = 2; // clock high
//	delay();
 PD1 = 0; // clock low
// bit 3
 PD3 = data>>2; // bit 1 is high or low depending on bit 3
 PD1 = 2; // clock high
// delay();
 PD1 = 0; // clock low
// bit 2
 PD3 = data>>1; // bit 1 is high or low depending on bit 2
 PD1 = 2; // clock high
// delay();
 PD1 = 0; // clock low
// bit 1
 PD3 = data; // bit 1 is high or low depending on bit 1
 PD1 = 2; // clock high
// delay();
 PD1 = 0; // clock low
// bit 0
 PD3 = data<<1; // bit 1 is high or low depending on bit 0
 PD1 = 2; // clock high
 //delay();
 PD1 = 0; // clock low
 PD0 = 1; // frame select high
} 