/*
 * display.c
 *
 *  Created on: May 24, 2015
 *      Author: Serghei
 */

#include <msp430g2553.h>
#include "display.h"
void initDisplay()
{
number = 666;
P1DIR |= 0xFE;
P1OUT |= 0xFE;
P2DIR |= 0x07;
P2OUT |= 0x07;
}
void displayInteger()
{
static uint8 NrOfDigit = 0;
static uint8 digit[3];
static uint16 oldNumber=0;									//soft filter
	if (newValue && (NrOfDigit == 0))
	{
//		if (fiternumber>number && (fiternumber-number>10) ||	//soft filter: display only if increas
//			fiternumber<number && (number-fiternumber>10))		//or decrease by with 15 unit
//		{
		oldNumber=number;
		digit[0]=oldNumber/1000;
		oldNumber %=1000;
		digit[1]=oldNumber/100;
		oldNumber %=100;
		digit[2]=oldNumber/10;
		newValue = false;
	}
	P2OUT |=0x07;						//turn off all 3 digit
	P1OUT |=0xFE;						//turn off all segments
	switch (digit[NrOfDigit])
	{
		case 0: P1OUT &=0x03;break;
		case 1: P1OUT &=0xDB;break;
		case 2: P1OUT &=0x45;break;
		case 3: P1OUT &=0x51;break;
		case 4: P1OUT &=0x99;break;
		case 5: P1OUT &=0x31;break;
		case 6: P1OUT &=0x21;break;
		case 7: P1OUT &=0x5B;break;
		case 8: P1OUT &=0x01;break;
		case 9: P1OUT &=0x11;break;
		default: while(1){}break;
	}
	switch (NrOfDigit)
	{
	case 0: P2OUT&=~0x01;NrOfDigit++;break;
	case 1: P2OUT&=~0x02;NrOfDigit++;break;
	case 2: P2OUT&=~0x04;NrOfDigit=0;break;
	}
}

void displayError()
{
	static uint8 NrOfDigit = 0;
	static bool newValueGetted = false;
	static uint8 digit[3];

	P2OUT |=0x07;						//turn off all 3 digit
	P1OUT |=0xFE;						//turn off all segments

	if (!newValueGetted)
	{
		newValueGetted = true;
		digit[2] = ErrorNumber;
	}

	switch (NrOfDigit)
	{
		case 0: P1OUT &=0x25;break;
		case 1: P1OUT &=0xEC;break;
		case 2:
				{
					switch (digit[2])				//last digit display
					{
						case hall:  P1OUT &=0xDB;break;
						default: break;
					}
				}
	}

	switch (NrOfDigit)
	{
		case 0: P2OUT&=~0x01;NrOfDigit++;break;
		case 1: P2OUT&=~0x02;NrOfDigit++;break;
		case 2: P2OUT&=~0x04;NrOfDigit=0;newValueGetted = false;break;
	}
}
