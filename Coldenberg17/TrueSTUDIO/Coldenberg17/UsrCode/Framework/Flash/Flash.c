/*
 * Flash.c
 *
 *  Created on: Aug 14, 2016
 *      Author: Kuba
 */

#include "Flash.h"
#include "Drivers/PortsDefs.h"

static uint8_t value = 99; //TODO: handle it

/*! Public functions */
void Flash_SaveValue( uint8_t u8NewValue )
{
	value = u8NewValue;
}

uint8_t Flash_GetLastValue( void )
{
	return value;
}
