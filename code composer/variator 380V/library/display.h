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
void displayInteger();
enum errors
	{
	hall=0,
	general
	};
void displayError();
uint8 ErrorNumber;
bool newValue;
#endif /* LIBRARY_DISPLAY_H_ */
