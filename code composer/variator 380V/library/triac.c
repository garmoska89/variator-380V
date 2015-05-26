/*
 * triac.c
 *
 *  Created on: May 25, 2015
 *      Author: Serghei
 */
#include "triac.h"
void powerOnTriac()
{
	//calculare time
	switch (state)
	{
	case 0: TA0CCR0 = time;TACTL |= MC1;break;//up-mode,
	case 1: TA0CCR0 = time;TACTL |= MC1;break;
	case 2: TA0CCR0 = time;TACTL |= MC1;break;
	case 3: TA0CCR0 = time;TACTL |= MC1;break;
	case 4: TA0CCR0 = time;TACTL |= MC1;break;
	case 5: TA0CCR0 = time;TACTL |= MC1;break;
	case 6: break;
	default:TACTL &=~MC_0;state=0;break;//stop timer and whate zero-cross
	}
}
void timerForTriacs(uint)
{
	TA0CCR0 = 0xFFFF;
	//		SMCLK	 |  /8	|Stop Mode
	TACTL = TASSEL_2 | ID_3 | MC_0;
	TA0CCTL0 &= ~CCIE;                 // Dissable interrupt
	TACTL |= TACLR;						//reset TA0R register

	P2DIR |= BIT3; 					// Set P1.0 to output direction
	P2OUT &= ~BIT3; 			     	// Set the red LED on
}
#pragma vector=TIMER0_A0_VECTOR
   __interrupt void Timer0_A0 (void) {		// Timer0 A0 interrupt service routine
	//powerOnTriac();
	//state++;
	P2OUT ^= BIT3;						// Toggle red LED
	//__bis_SR_register(GIE);// Low Power Mode 0, ADC10_ISR
}
