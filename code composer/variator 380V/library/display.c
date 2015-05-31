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
P1DIR |= 0xFE;
P1OUT |= 0xFE;
P2DIR |= 0x07;
P2OUT |= 0x07;
}
void updateDisplay()
{
static uint8 NrOfDigit = 0;
static uint8 tmpValueOfDigit[3];
//static uint16 oldNumber=0;									//soft filter
	if (newValue)
	{
//		if (fiternumber>number && (fiternumber-number>10) ||	//soft filter: display only if increas
//			fiternumber<number && (number-fiternumber>10))		//or decrease by with 15 unit
//		{

		tmpValueOfDigit[0] = digitValue[0];
		tmpValueOfDigit[1] = digitValue[1];
		tmpValueOfDigit[2] = digitValue[2];
//		digit[0]=oldNumber/1000;
//		oldNumber %=1000;
//		digit[1]=oldNumber/100;
//		oldNumber %=100;
//		digit[2]=oldNumber/10;
		newValue = false;
	}
	P2OUT |=0x07;						//turn off all 3 digit
	P1OUT |=0xFE;						//turn off all segments
	switch (tmpValueOfDigit[NrOfDigit])
	{
		case 0	: P1OUT &=0x03;break;
		case 1	: P1OUT &=0xDB;break;
		case 2	: P1OUT &=0x45;break;
		case 3	: P1OUT &=0x51;break;
		case 4	: P1OUT &=0x99;break;
		case 5	: P1OUT &=0x31;break;
		case 6	: P1OUT &=0x21;break;
		case 7	: P1OUT &=0x5B;break;
		case 8	: P1OUT &=0x01;break;
		case 9	: P1OUT &=0x11;break;
		case 'E': P1OUT &=0x25;break;	//65 ASCII
		case 'r': P1OUT &=0xEC;break;	//72 ASCII
		case 'O': P1OUT &=0x03;break;	//79 ASCII
		case 'F': P1OUT &=0x2D;break;	//70 ASCII
		//default: while(1){}break;		// to leave off display
	}
	switch (NrOfDigit)
	{
	case 0: P2OUT&=~0x01;NrOfDigit++;break;
	case 1: P2OUT&=~0x02;NrOfDigit++;break;
	case 2: P2OUT&=~0x04;NrOfDigit=0;break;
	}
}
