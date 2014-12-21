// LaunchPadSwitches.h
// Runs on TM4C123
// Provide functions that initialize a GPIO as an input pin and
// allow reading of two negative logic switches on PF0 and PF4

// Use bit-banded I/O.
// Daniel and Jonathan Valvano
// September 12, 2013

/* This example accompanies the book
   "Embedded Systems: Introduction to ARM Cortex M Microcontrollers",
   ISBN: 978-1469998749, Jonathan Valvano, copyright (c) 2013
   Section 4.2    Program 4.2

  "Embedded Systems: Real Time Interfacing to ARM Cortex M Microcontrollers",
   ISBN: 978-1463590154, Jonathan Valvano, copyright (c) 2013
   Example 2.3, Program 2.9, Figure 2.36

 Copyright 2013 by Jonathan W. Valvano, valvano@mail.utexas.edu
    You may use, edit, run or distribute this file
    as long as the above copyright notice remains
 THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 VALVANO SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL,
 OR CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 For more information about my classes, my research, and my books, see
 http://users.ece.utexas.edu/~valvano/
 */





//------------Board_Init------------
// Initialize GPIO Port F for negative logic switches on PF0 and
// PF4 as the Launchpad is wired.  Weak internal pull-up
// resistors are enabled, and the NMI functionality on PF0 is
// disabled.
// Input: none
// Output: none
void Board_Init(void);

//------------Board_Input------------
// Read and return the status of the switches.
// Input: none
// Output: 2 if only Switch 1 is pressed
//         1 if only Switch 2 is pressed
//         3 if both switches are pressed
//         0 if no switches are pressed
uint32_t Board_Input(void);

//------------LED_On------------
// Turn on LED
// Input: none
// Output: none
void LED_On(void);

//------------LED_Off------------
// Turn on LED
// Input: none
// Output: none
void LED_Off(void);
  
//------------LED_Toggle------------
// Turn on LED
// Input: none
// Output: none
void LED_Toggle(void);

/****************Int2Str***************
 converts signed integer number to ASCII string
 format signed 32-bit 
 range -99999 to +99999
 Input: signed 32-bit integer 
 Output: null-terminated string exactly 7 characters plus null
 Examples
  12345 to " 12345"  
 -82100 to "-82100"
   -102 to "  -102" 
     31 to "    31" 
   
 */ 
void Int2Str(int32_t const num, char *string);
