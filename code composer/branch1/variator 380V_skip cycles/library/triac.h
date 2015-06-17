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

#define MAX_COUNTS_TO_SKIP 50

void configureTriac();
void putONallTriacs();
void putOFFallTriacs();

uint16 periodCounts;
uint16 periodToSkip;
bool onAllTriacs;

#endif /* LIBRARY_TRIAC_H_ */
