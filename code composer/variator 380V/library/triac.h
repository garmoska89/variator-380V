/*
 * triac.h
 *
 *  Created on: May 25, 2015
 *      Author: Serghei
 */

#ifndef LIBRARY_TRIAC_H_
#define LIBRARY_TRIAC_H_
#define delay_3ms3 6566			//20ms-39400 and 3.3ms=~6566
#define CCR0_10ms delay_3ms3*3
#define detectZeroCross 39400
#include "commontypes.h"
#include <msp430g2553.h>
#include "program.h"
void timerForTriacs();
void startTimer();
void stopTimerForTriacs();
void configureTriac();
void putONallTriacs();
void powerOnTriac();
void errorbelongZeroCross();
uint8 state;
uint16 time;
bool needToStartTimer;
int16 CCR0Value_Error;
uint16 local_CCR0Value;
int16 precedence_CCR0Value;
bool overflow;
bool zeroCrossOcured;
bool firsTime;
int32 TA0R_last;
uint16 CCR0_20ms1;
uint16 CCR0_20ms2;
uint16 Cros_0;
#endif /* LIBRARY_TRIAC_H_ */
