/*
 * LedsManager.h
 *
 *  Created on: Aug 14, 2016
 *      Author: Kuba
 */

#ifndef LedsMANAGER_H_
#define LedsMANAGER_H_

#include "stdbool.h"
#include <stdint.h>

void LedsManager_Perform( void );
void LedsManager_SetBlink( void );
void LedsManager_SetAllOff( void );
void LedsManager_SetAllOn( void );

#endif /* LedsMANAGER_H_ */
