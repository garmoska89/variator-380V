/*
 * hallSensor.c
 *
 *  Created on: May 25, 2015
 *      Author: Serghei
 */
#define CNTL0	0x0000 	//16-bit, TBR
#include <msp430g2553.h>
#include "commontypes.h"
#include "hallSensor.h"

void configHallSensor()
{
//Config timer capture from falling to rising
//
P2DIR &=~BIT3;								//set input
P2SEL |= BIT3;								//Timer1_A3.CCI0B

TA1CTL = CNTL0 | TASSEL_2 | ID_3 | MC_2 | TACLR ;//| TAIE;
/*
SCS	- 0	Asynchronous capture
	  1	Synchronous capture
*/
//		Rising	| Captur| CCI0B		|
TA1CCTL0 = CM_1 | CAP	| CCIS_1 	;//|	CCIE ;
}

// Timer A0 interrupt service routine
#pragma vector=TIMER1_A0_VECTOR
__interrupt void Timer_A0 (void)
{
	TA1CTL |= TACLR;
	__enable_interrupt();
}
// Interrupt handler for TA1CCR0 CCIFG.
#pragma vector=TIMER1_A1_VECTOR
__interrupt void Timer_A1 (void)
{
	switch( TA0IV )
	{
	 case 2:
	 number = 111;
	 newValue = true;
	 __enable_interrupt(); // overflow
	break; // CCR1 not used
	 case 4:
	 __enable_interrupt(); // overflow
	 break; // CCR2 not used
	 case 10:
     {
	 TA1CCTL0 &=~COV;
	 TA1CTL |= TACLR;
     __enable_interrupt(); // overflow
	 break;
     }
	 case 14:
	 {
	 __enable_interrupt(); // overflow
	 break;
	 }
	}

}
