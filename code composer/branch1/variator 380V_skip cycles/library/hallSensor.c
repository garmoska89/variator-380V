/*
 * hallSensor.c
 *
 *  Created on: May 25, 2015
 *      Author: Serghei
 */
#include "hallSensor.h"
#define CNTL0	0x0000 	//16-bit, TBR
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
TA1CCTL0 = CM_0 | CAP	| CCIS_1 	;//|	CCIE ;
}
void stopHallSensor()
{
	TA1CTL &= ~TAIE;
	TA1CCTL0 &= ~(CCIE + CM_1);
	TA1CCTL0 &= ~CCIE;
}
void startHallSensor()
{
	TA1CTL 		|= TACLR;
	TA1CTL 		|= TAIE;
	TA1CCTL0 	|= CCIE;
	TA1CCTL0 = CM_1 ;
}
// Timer A0 interrupt service routine
#pragma vector=TIMER1_A0_VECTOR
__interrupt void Timer_A0 (void)
{
	//rotaion 	uS/min	TA1CCR0*4Us/250
	rotation = (14710800/TA1CCR0);//rotation (uint16)(((uint32)60000000/(uint32)(TA1CCR0))/245);
	if (normalModeCounts == houMuchCountsNormalMode ) {OverFlowCounts = (howMuchCountsIgnoreOverflow-1);}
	normalModeCounts++;
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
     OverFlowCounts++;		//time to start mo
     normalModeCounts = 0;
     if (OverFlowCounts == howMuchCountsIgnoreOverflow)
     {
     digitValue[0]='E';
     digitValue[1]='r';
	 digitValue[2]= 3;
	 newValue = true;
	 myState = WithHall_fault;
	 putOFFallTriacs();
	 stopHallSensor();
     }
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
