/*
 * Relays.h
 *
 *  Created on: Aug 14, 2016
 *      Author: Kuba
 */

#ifndef RELAYS_H_
#define RELAYS_H_

#include "stdbool.h"
#include <stdint.h>


void Relays_Perform( void );
void Relays_Init( void );
void Relays_CompressorSetState( bool bState );
void Relays_LightSetState( bool bState );

#endif /* RELAYS_H_ */
