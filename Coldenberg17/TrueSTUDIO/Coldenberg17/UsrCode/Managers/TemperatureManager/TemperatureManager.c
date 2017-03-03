/*
 * TemperatureManager.c
 *
 *  Created on: Aug 14, 2016
 *      Author: Kuba
 */

#include "TemperatureManager.h"
#include "Drivers/PortsDefs.h"

uint16_t temp = 0;
/*! Public functions */
void TemperatureManager_Perform( void )
{

}

void TemperatureManager_SetTemp( uint16_t uNewTemp )
{
	temp = uNewTemp;
}

uint16_t TemperatureManager_GetTemp( void )
{
	return temp;
}
