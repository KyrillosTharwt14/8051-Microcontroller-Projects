//----------------------------------------------------------------------------
// DAC1_fgen1.c 
//----------------------------------------------------------------------------// 
// AUTH: BW,FB 
// DATE: 2 OCT 01 // 
// Target: C8051F02x 
// Tool chain: KEIL C51 // 
// Description: 
//    Example source code which outputs waveforms on DAC1.  DAC1's output is 
//    scheduled to update at a rate determined by the constant 
//    <SAMPLE_RATE_DAC>, managed and timed by Timer4. // 
//    Implements a 256-entry full-cycle sine table of 16-bit precision. Other 
//    waveforms supported are square, triangle, and saw tooth. // 
//    The output frequency is determined by a 16-bit phase adder. 
//    At each DAC update cycle, the phase adder value is added to a running 
//    phase accumulator, <phase_accumulator>, the upper bits of which are used 
//    to access the sine lookup table. // 
//    The program is controlled through UART using HyperTerminal running on a 
//    PC. All commands are two characters in length and have optional 
//    frequency and amplitude arguments. Note that the amplitude parameter 
//    cannot be specified unless the frequency is also specified. //    
//    Command Format:  //        
//       XX [frequency] [amplitude] //         
//       where XX denotes the command // 
//    Command List: //
//      SQ - Square Wave //      SI - Sine Wave //      TR - Triangle Wave //      SA - Saw Tooth Wave //      OF - Output OFF 
//      ?? - Help    

//----------------------------------------------------------------------------// Includes //----------------------------------------------------------------------------
#include <c8051f020.h>     // SFR declarations 
#include <stdio.h> 
#include <string.h> 
#include <ctype.h>
#include <stdlib.h>
//----------------------------------------------------------------------------// 16-bit SFR Definitions for 'F02x //----------------------------------------------------------------------------
sfr16 DP       = 0x82;              // data pointer 
sfr16 TMR3RL   = 0x92;              // Timer3 reload value 
sfr16 TMR3     = 0x94;              // Timer3 counter 
sfr16 ADC0     = 0xbe;              // ADC0 data 
sfr16 ADC0GT   = 0xc4;              // ADC0 greater than window 
sfr16 ADC0LT   = 0xc6;              // ADC0 less than window 
sfr16 RCAP2    = 0xca;              // Timer2 capture/reload 
sfr16 T2       = 0xcc;              // Timer2 
sfr16 RCAP4    = 0xe4;              // Timer4 capture/reload 
sfr16 T4       = 0xf4;              // Timer4 
sfr16 DAC0     = 0xd2;              // DAC0 data 
sfr16 DAC1     = 0xd5;              // DAC1 data
//----------------------------------------------------------------------------// Function PROTOTYPES //----------------------------------------------------------------------------
void main (void); 
void SYSCLK_Init (void); 
void PORT_Init (void); 
void UART0_Init (void);
void Timer4_Init (int counts); 
void Timer4_ISR (void); 
long pow(int x, int y); 
void Print_Command_List(void);
void Sine(void); 
void Square(void); 
void Triangle(void); 
void Saw(void); 
void Off(void); 
void Help(void); 
void Error(void);