/*
 * program.h
 *
 *  Created on: May 28, 2015
 *      Author: uidg6243
 */
#include "display.h"
#include "commontypes.h"
#include "adc.h"
#include "hallSensor.h"
#define MAX_CCRO 0x1D00
#define minRotation 300
#define maxRotation 4000
#ifndef PROGRAM_H_
#define PROGRAM_H_
void programWithHall();
void programWithoutHall();
int32 map(int32 x, int32 in_min,int32 in_max, int32 out_min, int32 out_max);
uint16 constrain(uint16 x, uint16 min, uint16 max);
uint16 CCR0Value;
uint16 procentValue;
#endif /* PROGRAM_H_ */
