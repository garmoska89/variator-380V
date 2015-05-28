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
void configureTriac()
{
	P2SEL &= ~(BIT4+BIT5+BIT7);
	P2DIR |=   BIT4+BIT5+BIT7;
	P2OUT &= ~(BIT4+BIT5+BIT7);

}
void timerForTriacs(uint)
{
	TA0CCR0 = 0xFFFF;
	//		SMCLK	 |  /1	|Stop Mode
	TACTL = TASSEL_2 | ID_0 | MC_0;
	TA0CCTL0 &= ~CCIE;                 // Dissable interrupt
	TACTL |= TACLR;						//reset TA0R register
}
#pragma vector=TIMER0_A0_VECTOR
   __interrupt void Timer0_A0 (void)
{	// Timer0 A0 interrupt service routine
	//powerOnTriac();
	//state++;
	P2OUT ^= BIT4;
}
   void startTimer()
   {
   	TA0CCR0 = 0x1FFF;//FFFF - 33.33ms
   	TACTL |= TACLR;
   	TACTL |= MC_1;						//Up mode: the timer counts up to TACCR0.
   	TA0CCTL0 |= CCIE;                 // Enable Timer A0 interrupts, bit 4=1
   }
   void stopTimerForTriacs()
   	{
	P2OUT &= ~(BIT4+BIT5+BIT7);			//turn off all pins for Triacs
	TA0CCTL0 &= ~CCIE;                 	//Disable Timer A0 interrupts, bit 4=1
   	TACTL &= ~MC_3;						//Stop mode: the timer is halted.
   	TACTL |= TACLR;
   	}
