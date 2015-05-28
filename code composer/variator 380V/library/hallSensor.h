/*
 * hallSensor.h
 *
 *  Created on: May 25, 2015
 *      Author: Serghei
 */

#ifndef LIBRARY_HALLSENSOR_H_
#define LIBRARY_HALLSENSOR_H_
extern uint8 errors;
void configHallSensor();

void hallSensor();
extern uint16 number;
extern bool newValue;
extern bool errorOcured;
extern uint8 ErrorType;
uint16 rotation;
#endif /* LIBRARY_HALLSENSOR_H_ */
