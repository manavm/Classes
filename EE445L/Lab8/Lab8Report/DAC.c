#include <stdint.h>
#include "inc/tm4c123gh6pm.h"
#include "Systick.h"
#include "Timer0A.h"

#define PD0                     (*((volatile uint32_t *)0x40007004))
#define PD1                     (*((volatile uint32_t *)0x40007008))
#define PD3   									(*((volatile uint32_t *)0x40007020))
	
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

void Delay(void){
	int n = 100000;
	while (n != 0){
		n = n-1;
	}
}

//********DAC_Out*****************
// Send data to Max5353 12-bit DAC
// inputs:  voltage output (0 to 4095)
// outputs: none
void DAC_Out2(uint16_t code){   
  while((SSI0_SR_R&0x00000002)==0){};// SSI Transmit FIFO Not Full
  SSI0_DR_R = code; }                // data out, no reply
  

void DAC_Init(uint16_t data){
/*
  SYSCTL_RCGCGPIO_R |= 0x08;        // 1) activate port D
  while((SYSCTL_PRGPIO_R&0x08)==0){};   // allow time for clock to stabilize
                                    // 2) no need to unlock PD3-0
  GPIO_PORTD_AMSEL_R &= ~0x0F;      // 3) disable analog functionality on PD3-0
  GPIO_PORTD_PCTL_R &= ~0x0000FFFF; // 4) GPIO
  GPIO_PORTD_DIR_R |= 0x0F;         // 5) make PD3-0 out
  GPIO_PORTD_AFSEL_R &= ~0x0F;      // 6) regular port function 
  GPIO_PORTD_DEN_R |= 0x0F;         // 7) enable digital I/O on PD3-0
*/
	

	SYSCTL_RCGCGPIO_R |= 0x08;        // 1) activate port D
  while((SYSCTL_PRGPIO_R&0x08)==0){};   // allow time for clock to stabilize
                                    // 2) no need to unlock PD3-0
	GPIO_PORTD_AMSEL_R = 0;      // 3) disable analog functionality on PD3,PD1,PD0
  GPIO_PORTD_PCTL_R &= ~0x0000FFFF; // 4) GPIO
  GPIO_PORTD_DIR_R |= 0x0B;         // 5) make PD3,PD1,PD0 out
  GPIO_PORTD_AFSEL_R |= 0x0B;   		// 6) regular port function 
  GPIO_PORTD_PUR_R |= 0x0B; 
	GPIO_PORTD_DEN_R |= 0x0B;     		// 7) enable digital I/O on PD3,PD1,PD0
	GPIO_PORTD_IS_R &= ~0x0B;     		// (d) PD3,PD1,PD0 is edge-sensitive
  GPIO_PORTD_IBE_R &= ~0x0B;    		//     PD3,PD1,PD0 is not both edges
  GPIO_PORTD_IEV_R |= 0x0B;    			//     PD3,,PD0,PD1 rising edge event
  GPIO_PORTD_ICR_R = 0x0B;      		// (e) clear flags 4,0
  GPIO_PORTD_IM_R |= 0x0B;      		// (f) arm interrupt on PD3,PD1,PD0
	PD0 = 0x01;											//make the Frame Select High
	
}

void DAC_Out(uint16_t code){//when the Clock rises (PD1), first I toggle the FS(PD0).
//then on the second time the clock rises(on the rising edge) I output code to PD3
//		PD0 = 0x01;	// Frame Select Goes back up
	int count = 16;
	long code2;			
	//make sure the Ports are rising edge triggered.
	PD0 = 0x00;//change the Frame Select
	PD1 = 0x00;//change the clock
	Delay();
	PD1 = 0x02;//clock goes back up
	//this is a loop, where I send out one Bit at a time to PD3
	//I have to loop it 16 times, and each time I send data I have to toggle the Clock
	//after I send data I have to shift PD3 and get ready to send it again.
while(count != 0){	
	code2 = (code&0x0001);
	code = code/2; //this right shifts
	code2 = code2*8; //(left shift * 3)
	PD3 = code2;
	PD1 = 0x00;		//clock falls
	Delay();
	PD1 = 0x02;	//clock rises again
	count = count - 1; //# of remaining loops
}
	PD1 = 0x00;		//clock falls again
	PD0 = 0x01;	// Frame Select Goes back up

}
