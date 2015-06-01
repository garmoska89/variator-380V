/*
 * triac.h
 *
 *  Created on: May 25, 2015
 *      Author: Serghei
 */

#ifndef LIBRARY_TRIAC_H_
#define LIBRARY_TRIAC_H_
#include "commontypes.h"
#include <msp430g2553.h>
#include "program.h"
void timerForTriacs();
void startTimer();
void stopTimerForTriacs();
void configureTriac();
void putONallTriacs();
void powerOnTriac();
uint8 state;
uint16 time;
#endif /* LIBRARY_TRIAC_H_ */
