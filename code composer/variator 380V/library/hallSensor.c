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
#include "display.h"
void configHallSensor()
{
//Config timer capture from falling to rising
//
P2DIR &=~BIT3;								//set input
P2SEL |= BIT3;								//Timer1_A3.CCI0B

TA1CTL = CNTL0 | TASSEL_2 | ID_3 | MC_2 | TACLR | TAIE;
/*
SCS	- 0	Asynchronous capture
	  1	Synchronous capture
*/
//		Rising	| Captur| CCI0B		|
TA1CCTL0 = CM_1 | CAP	| CCIS_1 	|	CCIE ;
}

// Timer A0 interrupt service routine
#pragma vector=TIMER1_A0_VECTOR
__interrupt void Timer_A0 (void)
{
	uint16 tmpValue;
	ErrorType = OK;
	errorOcured = false;
	//rotaion 	uS/min	TA1CCR0*4Us/250
	rotation = (14710800/TA1CCR0);//rotation (uint16)(((uint32)60000000/(uint32)(TA1CCR0))/245);
	
	
	tmpValue = rotation;
	digitValue[0]=tmpValue/1000;
	tmpValue %=1000;
	digitValue[1]=tmpValue/100;
	tmpValue %=100;
	digitValue[2]=tmpValue/10;
	newValue = true;
	
	
	//number = rotation;
	//ms * 10 to show beter on Display
	//number = ((uint16)(((uint32)((TA1CCR0)))/245)*10);

 	TA1CTL |= TACLR;
	__enable_interrupt();
}
// Interrupt handler for TA1CCR0 CCIFG.
#pragma vector=TIMER1_A1_VECTOR
__interrupt void Timer_A1 (void)
{
	switch( TA1IV )
	{
	case 2:
//		TA1CCTL1 &=~COV;
//		TA1CTL |= TACLR;
	 	__enable_interrupt(); 	// overflow
	break; 					// CCR1 not used
	 case 4:
//		 TA1CCTL1 &=~COV;
//		 TA1CTL |= TACLR;
		__enable_interrupt(); // overflow
	 break; // CCR2 not used
	 case 10:
     {
     ErrorType = overflow;
     errorOcured = true;
	 newValue = true;
//	 TA1CTL &=~TAIFG;
//	 //TA1CCTL0 &=~COV;
//	 TA1CTL |= TACLR;
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
