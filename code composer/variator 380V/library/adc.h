/*
 * adc.h
 *
 *  Created on: May 24, 2015
 *      Author: Serghei
 */

#ifndef LIBRARY_ADC_H_
#define LIBRARY_ADC_H_
#include "commontypes.h"
#define MAX_ROTATION 3;//3069/1023
void init_adc();
void testTimer();
uint16 adcToRotation();
uint16 potitiometer;
extern uint16 number;
extern bool newValue;
#endif /* LIBRARY_ADC_H_ */
