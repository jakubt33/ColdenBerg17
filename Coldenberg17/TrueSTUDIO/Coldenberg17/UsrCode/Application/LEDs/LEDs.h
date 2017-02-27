/*
 * LEDs.h
 *
 *  Created on: Aug 14, 2016
 *      Author: Kuba
 */

#ifndef LEDS_H_
#define LEDS_H_

#include "stdbool.h"
#include <stdint.h>

typedef enum
{
	dLed1,
	dLed2,
	dLed3,
}LEDs_Selector_T;

void LEDs_Perform( void );
void LEDs_SetState( LEDs_Selector_T eLED, bool bState );
bool LEDs_GetState( LEDs_Selector_T eLED );

#endif /* LEDS_H_ */
