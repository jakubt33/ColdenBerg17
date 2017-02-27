/*
 * TemperatureManager.h
 *
 *  Created on: Aug 14, 2016
 *      Author: Kuba
 */

#ifndef TEMPERATUREMANAGER_H_
#define TEMPERATUREMANAGER_H_

#include "stdbool.h"
#include <stdint.h>

void TemperatureManager_Perform( void );
void TemperatureManager_SetTemp( uint8_t u8NewTemp );
uint8_t TemperatureManager_GetTemp( void );

#endif /* TEMPERATUREMANAGER_H_ */
