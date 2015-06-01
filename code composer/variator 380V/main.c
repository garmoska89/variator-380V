#include <msp430.h> 
#include "library/adc.h"
#include "library/display.h"
#include "library/commontypes.h"
#include "library/timer.h"
#include "library/hallSensor.h"
#include "library/timer.h"
#include "library/triac.h"
#include "library/program.h"

/*
 * main.c
 */
//#pragma section ghs = ".main2"


int main(void)
{
	myState = withHallOff;
	init_adc();
    initDisplay();
    configureFrequency();
    watchDogConfigure();
    configHallSensor();
    timerForTriacs();
    configureTriac();
    //startTimer();
    __bis_SR_register(GIE);// Low Power Mode 0, ADC10_ISR

    while(1)
    {

    }
    //__bis_SR_register(CPUOFF + GIE);// Low Power Mode 0, ADC10_ISR
    return 0;
}
//#pragma endsection
void Task4ms();
void Task100ms();
void Task500ms();

void WatchDogTask()
{
	static uint8 updatePot=0;
	updatePot++;

	//if(updatePot%10 == 0 )

	Task4ms();
	if ( myState == withHall ){programWithHall();}
	if ( myState == withoutHall){programWithoutHall();};

	if (updatePot%25 == 0)
	{
		Task100ms();
	}
	if (updatePot == 120)	//only to start conversion for ADC
	{
		startADC();
	}
	if (updatePot == 125)
	{
		Task500ms();
		updatePot=0;
	}

}
void Task4ms()
{
	updateDisplay();
}
void Task100ms()//100ms tasc
{

}

void Task500ms()//500ms tasc
{
	if ( myState == withHall )
	{
		uint16 tmpValue;
		//display rotation
		tmpValue = rotation;
		digitValue[0]=tmpValue/1000;
		tmpValue %=1000;
		digitValue[1]=tmpValue/100;
		tmpValue %=100;
		digitValue[2]=tmpValue/10;
		newValue = true;
		if (timeForOverflow < howMuchTimeIgnoreOverflow) 	//how much time ignore overflow
		{													//time to start mo
			timeForOverflow++;
		}

	}
	if ( myState == withoutHall)
	{
		uint16 tmpValue;
		//display rotation
		tmpValue = procentValue;
		digitValue[0]=tmpValue/100;
		tmpValue %=100;
		digitValue[1]=tmpValue/10;
		tmpValue %=10;
		digitValue[2]=tmpValue;
		newValue = true;
	}
}

