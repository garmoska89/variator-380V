/*
 * triac.c
 *
 *  Created on: May 25, 2015
 *      Author: Serghei
 */
#include "triac.h"
void configureTriac()
{
	P2SEL &= ~(BIT4+BIT5+BIT7);
	P2DIR |=   BIT4+BIT5+BIT7;
	P2OUT &= ~(BIT4+BIT5+BIT7);

	//zero cross
	P2SEL &= ~BIT6; //  Set P2.1    SEL as  GPIO
	P2DIR &= ~BIT6;	//set p2.6 as input
	P2IES |=  BIT6; //falling edge
	P2IFG &= ~BIT6;    //  Clear   interrupt   flag    for P2.6
	//P2IE  |=  BIT6; //  Enable  interrupt   for P2.6
	onAllTriacs = false;
}
   void putONallTriacs()
   {
	   P2OUT |= (BIT4+BIT5+BIT7);			//turn on all pins for Triacs
   }
   void putOFFallTriacs()
   {

	   P2OUT &= ~(BIT4+BIT5+BIT7);			//turn off all pins for Triacs
   }

   //  Port    1   interrupt   service routine
   #pragma vector=PORT2_VECTOR
   __interrupt void    Port_2(void)
   {
   	P2IFG  &=  (~BIT6);    //  P2.1    IFG clear

   	if ( myState == withoutHall )
	{
   		if (periodCounts > MAX_COUNTS_TO_SKIP ) periodCounts=0;

   		if (periodCounts < periodToSkip) putOFFallTriacs();
   		else putONallTriacs();

   		if ( periodToSkip != 0 )periodCounts++;
   		else periodCounts=0;
	}
   }
