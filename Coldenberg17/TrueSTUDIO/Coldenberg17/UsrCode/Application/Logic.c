/*
 * Logic.c
 *
 *  Created on: Aug 14, 2016
 *      Author: Kuba
 */

#include "Logic.h"
#include "Drivers/PortsDefs.h"

#include "Ntc/Ntc.h"
#include "Display/Display.h"

#include "Application/Buttons/Buttons.h"
#include "Framework/Flash/Flash.h"
#include "Framework/Counter/Counter.h"
#include "Managers/TemperatureManager/TemperatureManager.h"
#include "Managers/LedsManager/LedsManager.h"

typedef enum
{
	dLogicInit = 0,
	dLogicDisplaySetTemp,
	dLogicDisplayCurrentTemp,
	dLogicSetTempWaitForReady,
	dLogicSetTemp,
} LogicState_T;

typedef struct
{
	LogicState_T eState;
	uint16_t u16Timeout;
} Logic_T;

Logic_T kLogic;

static void Logic_SetState( LogicState_T eNewState );

/*! Public functions */
void Logic_Perform( void )
{
	Counter_TickTimeout( &kLogic.u16Timeout );

	static uint8_t u8RestoredTemp = 99u;
	switch( kLogic.eState )
	{
	case dLogicInit:
		u8RestoredTemp = Flash_GetLastValue();
		if( u8RestoredTemp != 0)
		{
			TemperatureManager_SetTemp( u8RestoredTemp );
		}
		Logic_SetState( dLogicDisplayCurrentTemp );
		break;

	case dLogicDisplayCurrentTemp:
		Display_DisplayNumber( Ntc_GetValue() );

		if(    (Button_GetEvent(dButton1) == dButtonEvent_Click)
			|| (Button_GetEvent(dButton2) == dButtonEvent_Click)
			|| (Button_GetEvent(dButton3) == dButtonEvent_Click)
		  )
		{
			Logic_SetState( dLogicDisplaySetTemp );
		}

		if (Button_GetEvent(dButton3) == dButtonEvent_Pressed3s)
		{
			Logic_SetState( dLogicSetTempWaitForReady );
		}

		break;

	case dLogicDisplaySetTemp:
		Display_DisplayNumber( TemperatureManager_GetTemp() );

		if( Counter_IsTimeoutExpired( &kLogic.u16Timeout ) )
		{
			Logic_SetState( dLogicDisplayCurrentTemp );
		}
		break;

	case dLogicSetTempWaitForReady:
		if (Button_GetEvent(dButton3) == dButtonEvent_Click)
		{
			Logic_SetState( dLogicSetTemp );
		}
		break;

	case dLogicSetTemp:
		if (Button_GetEvent(dButton3) == dButtonEvent_Pressed3s)
		{
			Logic_SetState( dLogicDisplaySetTemp );
		}
		if (Button_GetEvent(dButton3) == dButtonEvent_Click)
		{
			Flash_SaveValue( 3 ); //TODO: add
			TemperatureManager_SetTemp( 3 );
			Logic_SetState( dLogicDisplayCurrentTemp );
		}
		break;

	default:
		break;
	}
}

static void Logic_SetState( LogicState_T eNewState )
{
	switch ( eNewState )
	{
	case dLogicInit:
		break;

	case dLogicDisplayCurrentTemp:
		LedsManager_SetAllOff();
		break;

	case dLogicDisplaySetTemp:
		LedsManager_SetAllOn();
		Counter_SetTimeout( &kLogic.u16Timeout, 300U );

		break;

	case dLogicSetTempWaitForReady:
		LedsManager_SetBlink();
		break;

	case dLogicSetTemp:
		break;

	default:
		break;
	}
	kLogic.eState = eNewState;
}

