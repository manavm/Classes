long StartCritical (void);    // previous I bit, disable interrupts

void EndCritical(long sr);    // restore I bit to previous value

// **************SysTick_Init*********************
// Initialize Systick periodic interrupts
// Input: interrupt period
//        Units of period are 20ns
//        Maximum is 2^24-1
//        Minimum is determined by length of ISR
// Output: none

void SysTick_Init(unsigned long period);

void SysTick_Handler(void);
