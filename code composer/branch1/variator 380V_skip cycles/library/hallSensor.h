/*
 * hallSensor.h
 *
 *  Created on: May 25, 2015
 *      Author: Serghei
 */
#include <msp430g2553.h>
#include "commontypes.h"
#include "display.h"
#include "adc.h"


#ifndef LIBRARY_HALLSENSOR_H_
#define LIBRARY_HALLSENSOR_H_

#define howMuchCountsIgnoreOverflow 10
#define houMuchCountsNormalMode 0xFFFF

uint8 OverFlowCounts;
uint8 normalModeCounts;
uint16 rotation;

void configHallSensor();
void hallSensor();
void startHallSensor();
void stopHallSensor();

#endif /* LIBRARY_HALLSENSOR_H_ */
