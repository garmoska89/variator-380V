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
	P1SEL |= BIT0;														// ADC input pin P1.0
	ADC10CTL1 = INCH_0+ ADC10DIV_7 + CONSEQ_2 ;         				// Channel 0, ADC10CLK/8, Repeat-single-channel
	ADC10CTL0 = ADC10SHT_3 + MSC + ADC10ON + ADC10IE + ENC + ADC10SC;	//sample-and-hold time 64 x ADC10CLKs, Multiple sample and conversion,
																		// ADC10 on, ADC10 interrupt enable
	ADC10AE0 |= BIT0;                         							// ADC input enable P1.0
}
#pragma vector=ADC10_VECTOR
__interrupt void ADC10_ISR(void)
{
	ADC10CTL0 &= ~ENC;				// Disable Conversion
	while (ADC10CTL1 & BUSY);		// Wait if ADC10 busy
	potentiometerADC = ADC10MEM;
	//number = potitiometer;
	//testTimer();
	//newValue = true;
	ADC10CTL0 &= ~ADC10IFG;  // clear interrupt flag
}
void startADC()
{
	ADC10CTL0 |= ENC + ADC10SC;		// Enable Conversion and conversion start
}
