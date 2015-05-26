/*
 * adc.c
 *
 *  Created on: May 24, 2015
 *      Author: Serghei
 */
#include <msp430g2553.h>
#include "adc.h"
void init_adc()
{
	P1SEL |= BIT0;										// ADC input pin P1.0
	ADC10CTL1 = INCH_0+ ADC10DIV_7 + CONSEQ_2 ;         // Channel 0, ADC10CLK/8, Repeat-single-channel
	ADC10CTL0 = ADC10SHT_3 + MSC + ADC10ON + ADC10IE + ENC + ADC10SC;	//sample-and-hold time 64 x ADC10CLKs, Multiple sample and conversion,
														// ADC10 on, ADC10 interrupt enable
	ADC10AE0 |= BIT0;                         			// ADC input enable P1.0

}
#pragma vector=ADC10_VECTOR
__interrupt void ADC10_ISR(void)
{
	ADC10CTL0 &= ~ENC;				// Disable Conversion
	while (ADC10CTL1 & BUSY);		// Wait if ADC10 busy
	potitiometer = ADC10MEM;
	number = potitiometer;
	//testTimer();
	newValue = true;

	ADC10CTL0 &= ~ADC10IFG;  // clear interrupt flag
}
void testTimer()
{
if (potitiometer>10)
{
	TA0CCR0 = number * 10;
	TACTL |= TACLR;
	TACTL |= MC_1;						//Up mode: the timer counts up to TACCR0.
	TA0CCTL0 |= CCIE;                 // Enable Timer A0 interrupts, bit 4=1
}
else
	{
	TA0CCTL0 &= ~CCIE;                 	//Disable Timer A0 interrupts, bit 4=1
	TACTL &= ~MC_3;						//Stop mode: the timer is halted.
	TACTL |= TACLR;
	}
}
