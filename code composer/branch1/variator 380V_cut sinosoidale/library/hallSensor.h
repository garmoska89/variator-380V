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
#define howMuchTimeIgnoreOverflow 10 //10*500ms=5000ms = 5s
uint8 timeForOverflow;
extern uint8 errors;
void configHallSensor();
extern bool fault;
extern bool ignored;
void hallSensor();
void startHallSensor();
void stopHallSensor();
extern uint16 number;
extern bool newValue;
extern uint8 ErrorType;
uint16 rotation;
#endif /* LIBRARY_HALLSENSOR_H_ */
