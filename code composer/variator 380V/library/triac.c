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
		case 0: P2OUT &= ~(BIT4+BIT5+BIT7);	P2OUT |= BIT7;	state++;Cros_0=TA0R;break;		// F1 !F2 !F3 //waite x time and after start to put on triacs
		case 1: P2OUT &= ~(BIT4+BIT5+BIT7);					state++;			break;
		case 2:	P2OUT &= ~(BIT4+BIT5+BIT7);	P2OUT |= BIT4;	state++;			break;		//!F1  F2 !F3
		case 3: P2OUT &= ~(BIT4+BIT5+BIT7);					state++;			break;
		case 4: P2OUT &= ~(BIT4+BIT5+BIT7); P2OUT |= BIT5;	state++;			break;      //F1 !F2  F3
		case 5: P2OUT &= ~(BIT4+BIT5+BIT7);					state=0;			break;
//		case 6: P2OUT &= ~(BIT4+BIT5+BIT7);	P2OUT |= BIT7;	state++;			break;		// F1 !F2 !F3
//		case 7: P2OUT &= ~(BIT4+BIT5+BIT7);					state++;			break;
//		case 8:	P2OUT &= ~(BIT4+BIT5+BIT7);	P2OUT |= BIT4;	state++;			break;		//!F1  F2 !F3
//		case 9: P2OUT &= ~(BIT4+BIT5+BIT7);					state++;			break;
//		case 10:P2OUT &= ~(BIT4+BIT5+BIT7); P2OUT |= BIT5;	state++;			break;      //!F1 !F2  F3
//		case 11:P2OUT &= ~(BIT4+BIT5+BIT7);					state=0;			break;
		default:errorbelongZeroCross();        				   					break;        	//stop timer and whate zero-cross
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
		 else  myState = withoutHall_fault;
		 stopTimerForTriacs();
	     stopHallSensor();
}
void configureTriac()
{
	P2SEL &= ~(BIT4+BIT5+BIT7);
	P2DIR |=   BIT4+BIT5+BIT7;
	P2OUT &= ~(BIT4+BIT5+BIT7);

	CCR0Value_Error = 0;

	//zero cross
	P2SEL &= ~BIT6; //  Set P2.1    SEL as  GPIO
	P2DIR &= ~BIT6;	//set p2.6 as input
	P2IES |=  BIT6; //rising edge
	P2IFG &= ~BIT6;    //  Clear   interrupt   flag    for P2.6
	//P2IE  |=  BIT6; //  Enable  interrupt   for P2.6
}
void timerForTriacs()
{
	//		SMCLK	 |  /1	|Stop Mode
	TACTL = TASSEL_2 | ID_0 | MC_0;
	//TA0CCTL0 &= ~CCIE;                 // Dissable interrupt
	//TACTL |= TACLR;						//reset TA0R register
}
//#pragma vector=TIMER0_A0_VECTOR
//   __interrupt void Timer0_A0 (void)
//{	// Timer0 A0 interrupt service routine
//	   powerOnTriac();
//	   state++;
//}
#pragma vector=TIMER0_A1_VECTOR
   __interrupt void Timer0_A1 (void)
{
   switch( TA0IV )
	{
	case 2:
   //		TA1CCTL1 &=~COV;
   //		TA1CTL |= TACLR;
		__enable_interrupt(); 	// overflow
	break; 					// CCR1 not used
	 case 4:
   //		 TA1CCTL1 &=~COV;
   //		 TA1CTL |= TACLR;
	 __enable_interrupt(); // overflow
	 break; // CCR2 not used
	 case 10:
		{
		TA0R_last = ( TA0R_last - 0xFFFF );
		__enable_interrupt(); // overflow
	 break;
		}
	 case 14:
	 {
	 __enable_interrupt(); // overflow
	 break;
	 }
	}
}
   void startTimer()
   {
	TACTL |= MC_2 | TAIE;				//Continuous mode: the timer counts up to 0FFFFh.
	TA0R_last = 0;
	//TACTL |= MC_1;					//Up mode: the timer counts up to TACCR0.
   }
   void putONallTriacs()
   {
	P2OUT |= (BIT4+BIT5+BIT7);			//turn on all pins for Triacs
   }
   void stopTimerForTriacs()
   	{
	P2IE  &=  ~BIT6; 					//disable  interrupt   for P2.6
	P2OUT &= ~(BIT4+BIT5+BIT7);			//turn off all pins for Triacs
	TA0CCTL0 &= ~CCIE;                 	//Disable Timer A0 interrupts, bit 4=1
   	TACTL &= ~MC_1;						//Stop mode: the timer is halted.
   	TACTL |= TACLR;
	//zeroCrossOcured = false;
   	}
   //  Port    1   interrupt   service routine
   #pragma vector=PORT2_VECTOR
   __interrupt void    Port_2(void)
   {
//					   if (state%2 %= 0)
//					   {
//						   CCR0_20ms2 = TA0R;
//						   if (CCR0_20ms2 > CCR0_20ms1) CCR0_20ms2 = CCR0_20ms2 - CCR0_20ms1;
//						   else CCR0_20ms2 = 0xFFFF - CCR0_20ms1 + CCR0_20ms2;
//						   if (!zeroCrossOcured)
//						   {
//							   zeroCrossOcured = true;
//						   }
//					   }
//					   else
//					   {
//					   if (!zeroCrossOcured) startTimer();
//					   CCR0_20ms1 = TA0R;
//					   }
//					   P2IFG  &=  (~BIT6);    //  P2.1    IFG clear
	   if (!zeroCrossOcured)
	   {
		   startTimer();
		   zeroCrossOcured = true;
	   }
	   else
//		   	   	   	   if (zeroCrossOcured)
	   {
		  //TA0R_last = CCR0Value + (TA0R - TA0R_last);
		  //TA0R_last =TA0R_last - (TA0R - TA0R_last) 100;
		  if (TA0R > Cros_0)
		  {
			  if ( (detectZeroCross - (TA0R - Cros_0)) > delay_3ms3 )
			  {
				  TA0R_last -= delay_3ms3;
			  }
			  else if ( (detectZeroCross - (TA0R - Cros_0)) < delay_3ms3 )
			  {
				  TA0R_last += delay_3ms3;
			  }
			  else if ( (detectZeroCross - (TA0R - Cros_0)) > 0 )
			  {
				  TA0R_last -= (detectZeroCross - (TA0R - Cros_0) );
			  }
			  else
			  {
				  TA0R_last += ( detectZeroCross - (TA0R - Cros_0) );
			  }
		  }
		  else
		  {
			  if ( (detectZeroCross - (0xFFFF - Cros_0 + TA0R) ) > delay_3ms3 )
			  {
				  TA0R_last -= delay_3ms3;
			  }
			  else if ( (detectZeroCross - (TA0R - Cros_0)) < delay_3ms3 )
			  {
				  TA0R_last += delay_3ms3;
			  }
			  else if ( (detectZeroCross - (TA0R - Cros_0)) > 0 )
			  {
				  TA0R_last -= (detectZeroCross - (TA0R - Cros_0));
			  }
			  else
			  {
				  TA0R_last += (detectZeroCross - (TA0R - Cros_0));
			  }
		  }
	   }
   }
