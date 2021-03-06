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
	case 0: P2IE  |= BIT6;break;//up-mode,
	case 1: TA0CCR0 = CCR0Value;TACTL |= TACLR;TA0CCTL0 |= CCIE;TACTL |= MC1;P2OUT &= ~(BIT4+BIT5+BIT7);break;//up-mode,
	case 2: P2OUT |= BIT7;TA0CCR0 = 0x000F;TACTL |= TACLR;break;
	case 3: P2OUT &= ~BIT7;TA0CCR0 = 0x41A0;TACTL |= TACLR;break;
	case 4: P2OUT |= BIT7;TA0CCR0 = 0x000F;TACTL |= TACLR;break;
	case 5: P2OUT &= ~BIT7;TACTL &=~MC_0;state=1;TA0CCTL0 &= ~CCIE;break;
	case 6: TA0CCR0 = CCR0Value;TACTL |= TACLR;TA0CCTL0 |= CCIE;TACTL |= MC1;P2IE  |= BIT6;break;
	//case 2: TA0CCR0 = time;TACTL |= MC1;break;
	//case 3: TA0CCR0 = time;TACTL |= MC1;break;
	//case 4: TA0CCR0 = time;TACTL |= MC1;break;
	//case 5: TA0CCR0 = time;TACTL |= MC1;break;
	case 7: break;
	default:TACTL &=~MC_0;state=0;break;//stop timer and whate zero-cross
	}
}
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
	   state++;
	   powerOnTriac();

	//P2OUT |= BIT7;
	//stopTimerForTriacs();
}
   void startTimer()
   {
   	TA0CCR0 = 0x1FFF;//FFFF - 33.33ms
   	TACTL |= TACLR;
   	TACTL |= MC_1;						//Up mode: the timer counts up to TACCR0.
   	TA0CCTL0 |= CCIE;                 // Enable Timer A0 interrupts, bit 4=1
   }
   void putONallTriacs()
   {
	P2OUT |= (BIT4+BIT5+BIT7);			//turn on all pins for Triacs
   }
   void stopTimerForTriacs()
   	{
	//P2IE  &=  ~BIT6; //  disable  interrupt   for P2.6
	P2OUT &= ~(BIT4+BIT5+BIT7);			//turn off all pins for Triacs
	TA0CCTL0 &= ~CCIE;                 	//Disable Timer A0 interrupts, bit 4=1
   	TACTL &= ~MC_1;						//Stop mode: the timer is halted.
   	TACTL |= TACLR;
   	}
   //  Port    1   interrupt   service routine
   #pragma vector=PORT2_VECTOR
   __interrupt void    Port_2(void)
   {
   	P2IFG  &=  (~BIT6);    //  P2.1    IFG clear
   	TACTL |= TACLR;

   	state=1;
   	if (myState == withHall || myState == withoutHall) powerOnTriac();
   }
