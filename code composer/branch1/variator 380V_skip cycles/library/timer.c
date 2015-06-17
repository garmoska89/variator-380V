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
	//BCSCTL2 = DIVS_1;	// DIV SMCLK /2
	//		Password | timerMode|cleareCounter|   div		 div
	//WDTCTL = WDTPW | WDTTMSEL |	WDTCNTCL  | WDTIS1  | 	WDTIS0	;	//8uS,
	//WDTCTL = WDTPW | WDTTMSEL |	WDTCNTCL  | WDTIS1  			;	//65us
	//WDTCTL = WDTPW | WDTTMSEL |	WDTCNTCL  			| 	WDTIS0  ;	//1.044mS
	//WDTCTL = WDTPW | WDTTMSEL |	WDTCNTCL  						;   //4.176ms

	BCSCTL2 = DIVS_3;	// DIV SMCLK /8
	//		Password | timerMode|cleareCounter|   div		 div
	//WDTCTL = WDTPW | WDTTMSEL |	WDTCNTCL  | WDTIS1  | 	WDTIS0	;	//32.48-32.58uS
	//WDTCTL = WDTPW | WDTTMSEL |	WDTCNTCL  | WDTIS1  			;	//260.2us
	  WDTCTL = WDTPW | WDTTMSEL |	WDTCNTCL  			| 	WDTIS0  ;	//4.165ms
	//WDTCTL = WDTPW | WDTTMSEL |	WDTCNTCL  						;   //16.656ms

	IE1 |= WDTIE;                        	// enable Watchdog timer interrupts
}
void configureFrequency()
{
	DCOCTL = CALDCO_16MHZ;     				// Set DCO step and modulation
	BCSCTL1 = CALBC1_16MHZ;     			// Set range
}

void WatchDogTask();
#pragma vector=WDT_VECTOR                 	// Watchdog Timer interrupt service routine

  __interrupt void watchdog_timer(void)
{
	  WatchDogTask();
}
