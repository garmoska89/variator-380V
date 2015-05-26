/*
 * timer.c
 *
 *  Created on: May 25, 2015
 *      Author: uidg6243
 */
#include <msp430g2553.h>
#include "timer.h"

void watchDogConfigure()
{
	BCSCTL2 = DIVS_1;	// DIV SMCLK /2
	//		Password | timerMode|cleareCounter|   div		 div
	//WDTCTL = WDTPW | WDTTMSEL |	WDTCNTCL  | WDTIS1  | 	WDTIS0	;	//8uS, 		122.66kHz
	//WDTCTL = WDTPW | WDTTMSEL |	WDTCNTCL  | WDTIS1  			;	//65us, 	15.30kHz
	  WDTCTL = WDTPW | WDTTMSEL |	WDTCNTCL  			| 	WDTIS0  ;	//1.044mS,	479Hz		;
	//WDTCTL = WDTPW | WDTTMSEL |	WDTCNTCL  						;   //4.176ms	239.6Hz
			//WDT_MDLY_8
	IE1 |= WDTIE;                         // enable Watchdog timer interrupts
	//P2DIR |= BIT3; 					// Set P1.0 to output direction
	//P2OUT &= ~BIT3; 			     	// Set the red LED on
}
void configureFrequency()
{
	DCOCTL = CALDCO_16MHZ;     				// Set DCO step and modulation
	BCSCTL1 = CALBC1_16MHZ;     			// Set range
}


#pragma vector=WDT_VECTOR                 	// Watchdog Timer interrupt service routine

  __interrupt void watchdog_timer(void)
{
	Task1ms();
}
