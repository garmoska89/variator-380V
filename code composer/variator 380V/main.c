#include <msp430.h> 
#include "library/adc.h"
#include "library/display.h"
#include "library/commontypes.h"
#include "library/timer.h"
#include "library/hallSensor.h"
#include "library/timer.h"
#include "library/triac.h"
/*
 * main.c
 */
bool TaskFlag2ms = false;
//#pragma section ghs = ".main2"
int main(void)
{
	init_adc();
    initDisplay();
    configureFrequency();
    watchDogConfigure();
    configHallSensor();
    timerForTriacs();
    configureTriac();
    startTimer();
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
void Task250ms();

void WatchDogTask()
{
	static uint8 updatePot=0;
	updatePot++;

	//if(updatePot%10 == 0 )

	Task4ms();

	if (updatePot%25 == 0)
	{
		Task100ms();
	}

	if (updatePot == 50)
	{
		Task250ms();
		updatePot=0;
	}

}
void Task4ms()
{
	if (!errorOcured) displayInteger();
	else displayError();
}
void Task100ms()//100ms tasc
{

}
void Task250ms()//500ms tasc
{
	startADC();
}

