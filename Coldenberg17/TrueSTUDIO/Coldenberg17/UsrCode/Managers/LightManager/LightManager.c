/*
 * LightManager.c
 *
 *  Created on: Aug 14, 2016
 *      Author: Kuba
 */

#include "LightManager.h"
#include "Drivers/PortsDefs.h"

#include "Application/Buttons/Buttons.h"
#include "Application/Relays/Relays.h"
#include "Framework/Counter/Counter.h"

#define dTimeOfLight 2000 //20s

uint16_t u16LightTimer = 0;

/*! Public functions */
void LightManager_Perform( void )
{
	Counter_TickTimeout( &u16LightTimer );

	if(    (Button_GetEvent(dButton1) != dButtonEvent_None)
		|| (Button_GetEvent(dButton2) != dButtonEvent_None)
		|| (Button_GetEvent(dButton3) != dButtonEvent_None)
	  )
	{
		Counter_SetTimeout( &u16LightTimer, dTimeOfLight );
	}

	Relays_LightSetState( !Counter_IsTimeoutExpired( &u16LightTimer ) );

}
