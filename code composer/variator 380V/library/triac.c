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
        case 0: TA0CCR0 = CCR0Value;
        	if (needToStartTimer)
        		{
        		startTimer();
        		needToStartTimer = false;
        		}
        								P2OUT &= ~(BIT4+BIT5+BIT7);	P2OUT |= BIT4;		TACTL |= TACLR;	break;        	// F1 !F2 !F3
        case 1: TA0CCR0 = delay_3ms3;   P2OUT &= ~(BIT4+BIT5+BIT7);	P2OUT |= BIT7;    	TACTL |= TACLR;	break;        	//!F1 !F2  F3 3.3ms
        case 2: TA0CCR0 = delay_3ms3;   P2OUT &= ~(BIT4+BIT5+BIT7);	P2OUT |= BIT5;     	TACTL |= TACLR;	break;        	//!F1  F2 !F3 3.3ms
        case 3: TA0CCR0 = delay_3ms3;   P2OUT &= ~(BIT4+BIT5+BIT7);	P2OUT |= BIT1;     	TACTL |= TACLR;	break;        	// F1 !F2 !F3 3.3ms
        case 4: TA0CCR0 = delay_3ms3;   P2OUT &= ~(BIT4+BIT5+BIT7);	P2OUT |= BIT7;     	TACTL |= TACLR;	break;        	//!F1 !F2  F3 3.3ms
        case 5: TA0CCR0 = delay_3ms3;   P2OUT &= ~(BIT4+BIT5+BIT7);	P2OUT |= BIT5;     	TACTL |= TACLR;	break;        	//!F1  F2 !F3 3.3ms
        default:errorbelongZeroCross();        											TACTL |= TACLR;	break;        	//stop timer and whate zero-cross
        }
}
void errorbelongZeroCross()
{
	//display ER4 in case if overflow
	     digitValue[0]='E';
	     digitValue[1]='r';
		 digitValue[2]= 4;
		 newValue = true;
		 if (myState == withHall) myState = WithHall_fault;
		 else  myState = withoutHall;
		 stopTimerForTriacs();
	     stopHallSensor();
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
void timerForTriacs()
{
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
}
   void startTimer()
   {
   	//TA0CCR0 = 0x1FFF;//FFFF - 33.33ms
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
	P2IE  &=  ~BIT6; //  disable  interrupt   for P2.6
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
   	state=0;
   	powerOnTriac();
   }
