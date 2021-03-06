/*
 * adc.h
 *
 *  Created on: May 24, 2015
 *      Author: Serghei
 */

#ifndef LIBRARY_ADC_H_
#define LIBRARY_ADC_H_

#include <msp430g2553.h>
#include "display.h"
#include "triac.h"
#include "program.h"
#include "commontypes.h"

#define ADC_lowLevel 5
#define ADC_highLevel 1020

void init_adc();
void startADC();

uint16 potentiometerADC;
uint16 potentiometerRotation;
typedef enum stateMachine
{
	withHallOff=0,
	withHall,
	withHallHigh,

	WithHall_fault,

	withoutHallOff,
	withoutHall,
	withoutHallHigh
}stateMachine;
stateMachine myState;

#endif /* LIBRARY_ADC_H_ */
