/*
 * Relays.c
 *
 *  Created on: Aug 14, 2016
 *      Author: Kuba
 */

#include "Relays.h"
#include "Drivers/PortsDefs.h"
#include "Framework/Counter/Counter.h"

#define RelayCompressor_SetOff()  HAL_GPIO_WritePin(RelayCompressor_GPIO, RelayCompressor_PIN, !RelayCompressor_PinActiveState)
#define RelayCompressor_SetOn()   HAL_GPIO_WritePin(RelayCompressor_GPIO, RelayCompressor_PIN, RelayCompressor_PinActiveState)
#define RelayCompressor_IsOn()    HAL_GPIO_ReadPin(RelayCompressor_GPIO, RelayCompressor_PIN)

#define RelayTapfield_SetOff()  HAL_GPIO_WritePin(RelayTapfied_GPIO, RelayTapfied_PIN, !RelayTapfied_PinActiveState)
#define RelayTapfield_SetOn()   HAL_GPIO_WritePin(RelayTapfied_GPIO, RelayTapfied_PIN, RelayTapfied_PinActiveState)
#define RelayTapfield_IsOn()    HAL_GPIO_ReadPin(RelayTapfied_GPIO, RelayTapfied_PIN)

#define RelayLight_SetOff()  HAL_GPIO_WritePin(RelayLight_GPIO, RelayLight_PIN, !RelayLight_PinActiveState)
#define RelayLight_SetOn()   HAL_GPIO_WritePin(RelayLight_GPIO, RelayLight_PIN, RelayLight_PinActiveState)
#define RelayLight_IsOn()    HAL_GPIO_ReadPin(RelayLight_GPIO, RelayLight_PIN)

#define dCompressorTapFieldDelay   	100U  /*! x10ms */
#define dCompressorPowerOnDelay 	9000U /*! 90s */

typedef enum
{
	dCompressor_Off,
	dCompressor_WaitForTapfield,
	dCompressor_On,
} Compressor_State_T;

typedef struct
{
	Compressor_State_T eState;
	bool bCompressorRequestOn;
	uint16_t u16Timer;
}Compressor_T;

static void Compressor_SetState( Compressor_State_T eNewState );

Compressor_T kCompressor;

/*! Public functions */
void Relays_Init( void )
{
	kCompressor.bCompressorRequestOn = false;
	kCompressor.eState = dCompressor_Off;
	kCompressor.u16Timer = 0u;

	RelayLight_SetOff();
	RelayTapfield_SetOff();
	RelayCompressor_SetOff();
}

/*! Perform is called every 10ms */
void Relays_Perform( void )
{
	Counter_TickTimeout( &kCompressor.u16Timer );

	switch( kCompressor.eState )
	{
	case dCompressor_Off:
		RelayTapfield_SetOff();
		RelayCompressor_SetOff();
		if ( Counter_IsTimeoutExpired( &kCompressor.u16Timer ) )
		{
			if ( kCompressor.bCompressorRequestOn )
			{
				Compressor_SetState( dCompressor_WaitForTapfield );
			}
		}

		break;

	case dCompressor_WaitForTapfield:
		if ( Counter_IsTimeoutExpired( &kCompressor.u16Timer ) )
		{
			Compressor_SetState( dCompressor_On );
		}
		if ( !kCompressor.bCompressorRequestOn )
		{
			Compressor_SetState( dCompressor_Off );
		}
		break;

	case dCompressor_On:
		if ( !kCompressor.bCompressorRequestOn )
		{
			Compressor_SetState( dCompressor_Off );
		}
		break;

	default:
		Compressor_SetState( dCompressor_Off );
		break;

	}
}

void Relays_CompressorSetState( bool bNewState )
{
	kCompressor.bCompressorRequestOn = bNewState;
}

void Relays_LightSetState( bool bState )
{
	bState ? RelayLight_SetOn() : RelayLight_SetOff();
}

static void Compressor_SetState( Compressor_State_T eNewState )
{
	if( kCompressor.eState != eNewState )
	{
		switch( eNewState )
		{
		case dCompressor_Off:
			RelayTapfield_SetOff();
			RelayCompressor_SetOff();
			Counter_SetTimeout( &kCompressor.u16Timer, dCompressorPowerOnDelay );
			break;

		case dCompressor_WaitForTapfield:
			RelayTapfield_SetOn();
			RelayCompressor_SetOn();
			Counter_SetTimeout( &kCompressor.u16Timer, dCompressorTapFieldDelay );
			break;

		case dCompressor_On:
			RelayTapfield_SetOff();
			break;

		}
		kCompressor.eState = eNewState;
	}
}
