/*
 * program.c
 *
 *  Created on: May 28, 2015
 *      Author: uidg6243
 */

#include "program.h"

void programWithHall()
{
	int16 difRotation = potentiometerRotation - rotation;
	if (difRotation < 0 )	//Motor Rotation is to HIGH
	{
		if ( rotation > minRotation ) onAllTriacs=false;
		else onAllTriacs=true;
	}
	else					//Motor Rotation is to Low
	{
		//onAllTriacs=true;					|
		periodToSkip = map(difRotation,0,50,10,0);				//o stingere lina cind ajunge la rotatiile dorite cu 50 rot. mai inainte incepem a stinge incetisor
		if (periodCounts > 10) periodCounts=0;

		if (periodCounts < periodToSkip) putOFFallTriacs();
		else putONallTriacs();

		if (periodToSkip != 0) periodCounts++;
		else periodCounts=0;
	}
}
void programWithoutHall()
{
	uint16 tmpValue;
	tmpValue = potentiometerADC;
	tmpValue = constrain(tmpValue,ADC_lowLevel,ADC_highLevel);

	periodToSkip = map(tmpValue,ADC_lowLevel,ADC_highLevel,MAX_COUNTS_TO_SKIP,0);

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
