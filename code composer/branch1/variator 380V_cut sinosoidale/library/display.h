/*
 * display.h
 *
 *  Created on: May 24, 2015
 *      Author: Serghei
 */

#ifndef LIBRARY_DISPLAY_H_
#define LIBRARY_DISPLAY_H_
#include "commontypes.h"
void initDisplay();
/*
 ====P7=====
|			|
|			|
P6			P5
|			|
|			|
 ====P1=====
|			|
|			|
P4			P2
|			|
|			|
 ====P3=====
*/
uint16 number;
void updateDisplay();
uint8 digitValue[3];
bool newValue;
#endif /* LIBRARY_DISPLAY_H_ */
