/*
 * Relays.c
 *
 *  Created on: Aug 14, 2016
 *      Author: Kuba
 */

#include "Relays.h"
#include "Drivers/PortsDefs.h"

#define RelayCompressor_SetOff()  HAL_GPIO_WritePin(RelayCompressor_GPIO, RelayCompressor_PIN, !RelayCompressor_PinActiveState)
#define RelayCompressor_SetOn()   HAL_GPIO_WritePin(RelayCompressor_GPIO, RelayCompressor_PIN, RelayCompressor_PinActiveState)
#define RelayCompressor_IsOn()    HAL_GPIO_ReadPin(RelayCompressor_GPIO, RelayCompressor_PIN)

#define RelayTapfield_SetOff()  HAL_GPIO_WritePin(RelayTapfied_GPIO, RelayTapfied_PIN, !RelayTapfied_PinActiveState)
#define RelayTapfield_SetOn()   HAL_GPIO_WritePin(RelayTapfied_GPIO, RelayTapfied_PIN, RelayTapfied_PinActiveState)
#define RelayTapfield_IsOn()    HAL_GPIO_ReadPin(RelayTapfied_GPIO, RelayTapfied_PIN)

#define RelayLight_SetOff()  HAL_GPIO_WritePin(RelayLight_GPIO, RelayLight_PIN, !RelayLight_PinActiveState)
#define RelayLight_SetOn()   HAL_GPIO_WritePin(RelayLight_GPIO, RelayLight_PIN, RelayLight_PinActiveState)
#define RelayLight_IsOn()    HAL_GPIO_ReadPin(RelayLight_GPIO, RelayLight_PIN)

#define dCompressorTimerDelay 50U /*! x10ms */

typedef struct Relays
{
	bool bRelayCompressor;
	bool bRelayLight;

	uint16_t u16CompressorTimer;
}Relays_T;

Relays_T kRelays;

/*! Public functions */
/*! Perform is called every 10ms */
void Relays_Perform( void )
{
	if(kRelays.u16CompressorTimer) kRelays.u16CompressorTimer--;

	kRelays.bRelayLight ? RelayLight_SetOn() : RelayLight_SetOff();

	if(kRelays.bRelayCompressor)
	{
		if(!kRelays.u16CompressorTimer)
		{
			RelayTapfield_SetOff();
		}
	}
	else
	{
		RelayTapfield_SetOff();
		RelayCompressor_SetOff();
		kRelays.u16CompressorTimer = 0U;
	}

}

void Relays_Init( void )
{
	kRelays.bRelayCompressor = false;
	kRelays.bRelayLight = false;
	kRelays.u16CompressorTimer = 0U;

	RelayLight_SetOff();
	RelayTapfield_SetOff();
	RelayCompressor_SetOff();
}

void Relays_CompressorSetState( bool bState )
{
	if( !kRelays.bRelayCompressor )
	{
		RelayCompressor_SetOn();
		RelayTapfield_SetOn();
		kRelays.u16CompressorTimer = dCompressorTimerDelay;
	}
	kRelays.bRelayCompressor = bState;
}

void Relays_LightSetState( bool bState )
{
	kRelays.bRelayLight = bState;
}
