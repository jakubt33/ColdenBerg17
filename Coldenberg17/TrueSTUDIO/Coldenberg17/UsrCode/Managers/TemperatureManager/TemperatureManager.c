/*
 * TemperatureManager.c
 *
 *  Created on: Aug 14, 2016
 *      Author: Kuba
 */

#include "TemperatureManager.h"
#include "Drivers/PortsDefs.h"

#include "Application/Ntc/Ntc.h"
#include "Application/Relays/Relays.h"
#include "Framework/Counter/Counter.h"

#define dTempHisteresis 1u

#define dMaxCoolingTime 		20*60*10 //20min cooling time
#define dTimeStopDuringCooling   2*60*10 //2min  pause
#define dInitTime				dTimeStopDuringCooling //pause needed to cool down compressor


typedef enum
{
	dState_Init,
	dState_Cooling,
	dState_Pause,
	dState_Warming,
	dState_Error,

	dState_Last,
} TempManager_State_T;

typedef struct
{
	TempManager_State_T eState;
	uint8_t u8TempTarget;
	kCounterDown uTimer;
} TempManager_C;

#define mCheckError()                 \
do{                                   \
	if ( dNtc_ErrorTemp == uNtcTemp ) \
	{                                 \
		SetState(dState_Error);       \
	}                                 \
}while(0)

static void SetState( TempManager_State_T eNewState );

TempManager_C oTempManager;

/*! Public functions. Call each 100ms passed */
void TemperatureManager_Perform( void )
{
	uint8_t uTempTarget = oTempManager.u8TempTarget;
	uint16_t uNtcTemp = Ntc_GetValue();
	mCheckError();

	Counter_TickTimeout( &oTempManager.uTimer );
	switch ( oTempManager.eState )
	{
	case dState_Init:
	case dState_Pause:
		if ( Counter_IsTimeoutExpired( &oTempManager.uTimer ) )
		{
			if ( uTempTarget - dTempHisteresis > uNtcTemp )
			{
				SetState(dState_Warming);
			}
			else if ( uTempTarget + dTempHisteresis < uNtcTemp )
			{
				SetState(dState_Cooling);
			}
		}
		break;

	case dState_Cooling:
		if ( uTempTarget - dTempHisteresis > uNtcTemp )
		{
			SetState(dState_Warming);
		}
		if ( Counter_IsTimeoutExpired( &oTempManager.uTimer ) )
		{
			SetState(dState_Pause);
		}
		break;

	case dState_Warming:
		if ( uTempTarget + dTempHisteresis < uNtcTemp )
		{
			SetState(dState_Cooling);
		}
		break;

	case dState_Error:
		Relays_CompressorSetState( false ); //redundant protection

		if ( dNtc_ErrorTemp != uNtcTemp )
		{
			SetState(dState_Init);
		}
		break;

	default:
		break;
	}
}

static void SetState( TempManager_State_T eNewState )
{
	switch ( eNewState )
	{
	case dState_Init:
		Relays_CompressorSetState( false );
		Counter_SetTimeout( &oTempManager.uTimer, dInitTime);
		break;

	case dState_Cooling:
		Relays_CompressorSetState( true );
		Counter_SetTimeout( &oTempManager.uTimer, dMaxCoolingTime );
		break;

	case dState_Pause:
		Relays_CompressorSetState( false );
		Counter_SetTimeout( &oTempManager.uTimer, dTimeStopDuringCooling );
		break;

	case dState_Warming:
		Relays_CompressorSetState( false );
		break;

	case dState_Error:
		Relays_CompressorSetState( false );
		break;

	default:
		break;
	}
	oTempManager.eState = eNewState;
}

void TemperatureManager_SetTemp( uint16_t uNewTemp )
{
	oTempManager.u8TempTarget = uNewTemp;
}

uint16_t TemperatureManager_GetTempTarget( void )
{
	return oTempManager.u8TempTarget;
}
