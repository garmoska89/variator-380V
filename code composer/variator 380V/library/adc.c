/*
 * adc.c
 *
 *  Created on: May 24, 2015
 *      Author: Serghei
 */

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
	static bool onlyOnce0=true;
	static bool onlyOnce1=true;
	static bool onlyOnce2=true;
	ADC10CTL0 &= ~ENC;				// Disable Conversion
	while (ADC10CTL1 & BUSY);		// Wait if ADC10 busy
	potentiometerADC = (1023 - ADC10MEM);
	potentiometerRotation = map(potentiometerADC,ADC_lowLevel,ADC_highLevel,minRotation,maxRotation);
	if ( (potentiometerADC < ADC_lowLevel))
	{
		if(onlyOnce0 && (myState == withHallOff || myState == withHallHigh || myState == withHall || myState == withoutHall || myState == withoutHall_fault) )
		{
			myState = withHallOff;
			stopTimerForTriacs();
			stopHallSensor();
			onlyOnce0=false;onlyOnce1=true;onlyOnce2=true;
			digitValue[0]='O';
			digitValue[1]='F';
			digitValue[2]='F';
			newValue = true;
		}

		if(onlyOnce0 && (myState == WithHall_fault) )
		{
			myState = withoutHallOff;
			stopTimerForTriacs();
			stopHallSensor();
			onlyOnce0=false;onlyOnce1=true;onlyOnce2=true;
			digitValue[0]='O';
			digitValue[1]='F';
			digitValue[2]='F';
			newValue = true;
		}
	}
	if ( (potentiometerADC >= ADC_lowLevel+5) && (potentiometerADC <= ADC_highLevel-5) )
	{
		if ( onlyOnce1 && ( myState == withHallOff || myState == withHallHigh) )
		{
			programWithHall();				//to update CCR0Value
			P2IE  |= BIT6; 				 	//activate zero cross detection
			zeroCrossOcured = false;		//after first zero Cross the system considering in start Mode
			//startTimer();
			startHallSensor();

			myState = withHall;

			timeForOverflow=0;
			state=0;
			firsTime=true;
			onlyOnce0=true;onlyOnce1=false;onlyOnce2=true;
		}

		if ( onlyOnce1 && ( myState == withoutHallOff || myState == withoutHallHigh))
		{
			programWithoutHall();			//to update CCR0Value
			P2IE  |= BIT6; 					//activate zero cross detection
			zeroCrossOcured = false;
			//startTimer();

			myState = withoutHall;

			state=0;
			firsTime=true;
			onlyOnce0=true;onlyOnce1=false;onlyOnce2=true;
		}

	}
	if (potentiometerADC > ADC_highLevel)
	{
		if(onlyOnce2 && (myState == withHallOff || myState == withHall))
		{
			stopTimerForTriacs();
			stopHallSensor();
			putONallTriacs();

			P2IE &= ~BIT6;

			myState = withHallHigh;

			onlyOnce0=true;onlyOnce1=true;onlyOnce2=false;

			digitValue[0]=9;
			digitValue[1]=9;
			digitValue[2]=9;
			newValue = true;
		}
		if(onlyOnce2 && (myState == withoutHallOff || myState == withoutHall))
		{
			stopTimerForTriacs();
			putONallTriacs();

			P2IE &= ~BIT6;

			myState = withoutHallHigh;
			onlyOnce0=true;onlyOnce1=true;onlyOnce2=false;

			procentValue = 100;
			digitValue[0]=1;
			digitValue[1]=0;
			digitValue[2]=0;
			newValue = true;
		}
	}
	//display ADC
	/*
		tmpValue = potentiometerADC;
		digitValue[0]=tmpValue/1000;
		tmpValue %=1000;
		digitValue[1]=tmpValue/100;
		tmpValue %=100;
		digitValue[2]=tmpValue/10;
		newValue = true;
	*/
	ADC10CTL0 &= ~ADC10IFG;  // clear interrupt flag
}
void startADC()
{
	ADC10CTL0 |= ENC + ADC10SC;		// Enable Conversion and conversion start
}
