/*
 * LEDs.c
 *
 *  Created on: Aug 14, 2016
 *      Author: Kuba
 */

#include "LEDs.h"
#include "Drivers/PortsDefs.h"

#define LED1_SetOff()  HAL_GPIO_WritePin(LED1_GPIO, LED1_PIN, !LED1_PinActiveState)
#define LED1_SetOn()   HAL_GPIO_WritePin(LED1_GPIO, LED1_PIN, LED1_PinActiveState)
#define LED1_IsOn()    HAL_GPIO_ReadPin(LED1_GPIO, LED1_PIN)

#define LED2_SetOff()  HAL_GPIO_WritePin(LED2_GPIO, LED2_PIN, !LED2_PinActiveState)
#define LED2_SetOn()   HAL_GPIO_WritePin(LED2_GPIO, LED2_PIN, LED2_PinActiveState)
#define LED2_IsOn()    HAL_GPIO_ReadPin(LED2_GPIO, LED2_PIN)

#define LED3_SetOff()  HAL_GPIO_WritePin(LED3_GPIO, LED3_PIN, !LED3_PinActiveState)
#define LED3_SetOn()   HAL_GPIO_WritePin(LED3_GPIO, LED3_PIN, LED3_PinActiveState)
#define LED3_IsOn()    HAL_GPIO_ReadPin(LED3_GPIO, LED3_PIN)

typedef struct LEDs
{
	bool bLED1State;
	bool bLED2State;
	bool bLED3State;
}LEDs_T;

LEDs_T kLEDs;

/*! Public functions */
void LEDs_Perform( void )
{
	(kLEDs.bLED1State) ? LED1_SetOn() : LED1_SetOff();
	(kLEDs.bLED2State) ? LED2_SetOn() : LED2_SetOff();
	(kLEDs.bLED3State) ? LED3_SetOn() : LED3_SetOff();
}

void LEDs_SetState( LEDs_Selector_T eLED, bool bState )
{
	switch( eLED )
	{
	case dLed1:
		kLEDs.bLED1State = bState;
		break;

	case dLed2:
		kLEDs.bLED2State = bState;
		break;

	case dLed3:
		kLEDs.bLED3State = bState;
		break;

	default:
		break;
	}
}

bool LEDs_GetState( LEDs_Selector_T eLED )
{
	bool bReturn = false;
	switch( eLED )
	{
	case dLed1:
		bReturn = LED1_IsOn();
		break;

	case dLed2:
		bReturn = LED2_IsOn();
		break;

	case dLed3:
		bReturn = LED3_IsOn();
		break;

	default:
		break;
	}

	return bReturn;
}
