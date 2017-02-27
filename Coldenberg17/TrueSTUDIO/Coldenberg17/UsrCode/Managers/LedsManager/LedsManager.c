/*
 * LedsManager.c
 *
 *  Created on: Aug 14, 2016
 *      Author: Kuba
 */

#include "LedsManager.h"
#include "Drivers/PortsDefs.h"
#include "Application/LEDs/LEDs.h"
#include "Framework/Counter/Counter.h"

#define AllLedsOff() 				\
do{									\
	LEDs_SetState( dLed1, false );	\
	LEDs_SetState( dLed2, false );	\
	LEDs_SetState( dLed3, false );	\
}while(0)

#define AllLedsOn() 				\
do{									\
	LEDs_SetState( dLed1, true );	\
	LEDs_SetState( dLed2, true );	\
	LEDs_SetState( dLed3, true );	\
}while(0)


typedef enum
{
	LedsMode_Off,
	LedsMode_On,
	LedsMode_BlinkingOn,
	LedsMode_BlinkingOff,
} LedsManager_Mode_T;

typedef struct
{
	LedsManager_Mode_T eMode;
	uint16_t u16Timeout;
} LedsManager_T;

LedsManager_T kLedsManager;

/*! Public functions */
void LedsManager_Perform( void )
{
	Counter_TickTimeout( &kLedsManager.u16Timeout );

	switch ( kLedsManager.eMode )
	{
	case LedsMode_Off:
		AllLedsOff();
		break;

	case LedsMode_On:
		AllLedsOn();
		break;

	case LedsMode_BlinkingOn:
		if( Counter_IsTimeoutExpired( &kLedsManager.u16Timeout ) )
		{
			AllLedsOff();
			Counter_SetTimeout( &kLedsManager.u16Timeout, 25 );
			kLedsManager.eMode = LedsMode_BlinkingOff;
		}
		break;

	case LedsMode_BlinkingOff:
		if( Counter_IsTimeoutExpired( &kLedsManager.u16Timeout ) )
		{
			AllLedsOn();
			Counter_SetTimeout( &kLedsManager.u16Timeout, 25 );
			kLedsManager.eMode = LedsMode_BlinkingOn;
		}
		break;

	default:
		break;
	}
}

void LedsManager_SetBlink( void )
{
	AllLedsOn();
	Counter_SetTimeout( &kLedsManager.u16Timeout, 25 );
	kLedsManager.eMode = LedsMode_BlinkingOn;
}

void LedsManager_SetAllOff( void )
{
	kLedsManager.eMode = LedsMode_Off;
}

void LedsManager_SetAllOn( void )
{
	kLedsManager.eMode = LedsMode_On;
}
