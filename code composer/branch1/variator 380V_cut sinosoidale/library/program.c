/*
 * program.c
 *
 *  Created on: May 28, 2015
 *      Author: uidg6243
 */

#include "program.h"

void programWithHall()
{
	int16 difRotation=0;
	uint16 tmpValue;
	tmpValue = potentiometerRotation;
	difRotation = tmpValue - rotation;
	tmpValue = constrain(tmpValue,ADC_lowLevel,ADC_highLevel);
	if (difRotation < 0 )	//Motor Rotation is to HIGH
	{
		if ( ( (CCR0Value + 50)<MAX_CCRO) && (rotation>minRotation) ) CCR0Value += 50;
	}
	else					//Motor Rotation is to Low
	{
		if ( CCR0Value >= 65 ) CCR0Value -= 50;
	}
}
void programWithoutHall()
{
	uint16 tmpValue;
	tmpValue = potentiometerADC;
	tmpValue = constrain(tmpValue,ADC_lowLevel,ADC_highLevel);
	CCR0Value = map(tmpValue,ADC_lowLevel,ADC_highLevel,MAX_CCRO,0x000F);
	procentValue = map(tmpValue,ADC_lowLevel,ADC_highLevel,1,100);
	procentValue=constrain(procentValue,0,100);
}
int32 map(int32 x, int32 in_min,int32 in_max, int32 out_min, int32 out_max)
{
	return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
uint16 constrain(uint16 x, uint16 min, uint16 max)
{
	uint16 tmpValue;
	if (x > max) tmpValue = max;
	else if (x < min) tmpValue = min;
	else tmpValue = x;
	return tmpValue;
}
