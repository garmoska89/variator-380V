#include <msp430.h> 
#include "library/adc.h"
#include "library/display.h"
#include "library/commontypes.h"
#include "library/timer.h"
/*
 * main.c
 */
bool TaskFlag2ms = false;
int main(void)
{

    init_adc();
    initDisplay();
    configureFrequency();
    watchDogConfigure();
    //configHallSensor();
    //ErrorNumber = hall;
    timerForTriacs();
    __bis_SR_register(GIE);// Low Power Mode 0, ADC10_ISR
    while(1)
    {

    }
    //__bis_SR_register(CPUOFF + GIE);// Low Power Mode 0, ADC10_ISR
	return 0;
}
void Task1ms()
{
	static uint8 updatePot=0;
	updatePot++;
	if (updatePot%5 == 0)
	{
		Task5ms();
	}
	if (updatePot%100 == 0)
	{
		Task100ms();
	}
	if (updatePot == 250)
	{
		Task250ms();
		updatePot=0;
	}
}
void Task5ms()
{
	displayInteger();
}
void Task100ms()//100ms tasc
{

}
void Task250ms()//500ms tasc
{
	ADC10CTL0 |= ENC + ADC10SC;		// Enable Conversion and conversion start
}

