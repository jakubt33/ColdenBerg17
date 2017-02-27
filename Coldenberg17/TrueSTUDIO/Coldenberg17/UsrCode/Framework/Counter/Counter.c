/*
 * Counter.c
 *
 *  Created on: Aug 14, 2016
 *      Author: Kuba
 */

#include "Counter.h"
#include "Drivers/PortsDefs.h"

void Counter_SetTimeout( uint16_t *u16Counter, uint16_t u16NewTimeout )
{
	*u16Counter = u16NewTimeout;
}

void Counter_TickTimeout( uint16_t *u16Counter )
{
	if( !Counter_IsTimeoutExpired( u16Counter ) )
	{
		*u16Counter = *u16Counter - 1U;
	}
}

bool Counter_IsTimeoutExpired( uint16_t *u16Counter )
{
	return ( *u16Counter == 0u );
}

/*! Public functions */
