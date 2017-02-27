/*
 * Buttons.c
 *
 *  Created on: Aug 14, 2016
 *      Author: Kuba
 */
#include "Buttons.h"
#include "Drivers/PortsDefs.h"
#include "Framework/Debouncer/Debouncer.h"

//Private defines
#define BUTTON_1_IsOn()    !HAL_GPIO_ReadPin(BUTTON_1_GPIO, BUTTON_1_PIN)
#define BUTTON_2_IsOn()    !HAL_GPIO_ReadPin(BUTTON_2_GPIO, BUTTON_2_PIN)
#define BUTTON_3_IsOn()    !HAL_GPIO_ReadPin(BUTTON_3_GPIO, BUTTON_3_PIN)

#define dTimeUnit 			10U /*! ms */
#define dDebounceTime 		40U /*! ms */
#define dDebounceInitValue 	dDebounceTime/dTimeUnit

static bool Buttons_privIsPreseed(Button_Select_T eButton);

typedef struct Button
{
	Debouncer_T kDebouncer;
	Button_Event_T eEvent;
	uint16_t u16PressedCounter;
}Button_T;

Button_T tButtons[3];

/*! Public functions */
void Buttons_Perform(void) //pass number in argument
{
	Debouncer_Apply(&tButtons[dButton1].kDebouncer, BUTTON_1_IsOn());
	Debouncer_Apply(&tButtons[dButton2].kDebouncer, BUTTON_2_IsOn());
	Debouncer_Apply(&tButtons[dButton3].kDebouncer, BUTTON_3_IsOn());
}

void Buttons_Init(void)
{
	static uint8_t u8Counter=0;
	for(u8Counter=0; u8Counter<dButton_Last; u8Counter++)
	{
		Debouncer_Init(&tButtons[u8Counter].kDebouncer, dDebounceInitValue, 0);
		tButtons[u8Counter].eEvent = dButtonEvent_None;
		tButtons[u8Counter].u16PressedCounter = 0U;
	}
}

static bool Buttons_privIsPreseed(Button_Select_T eButton)
{
	return Debouncer_GetData(&tButtons[eButton].kDebouncer);
}

//call it in logic loop, every 10ms
void Buttons_GenerateEvent(void)
{
	uint8_t u8Counter=0;
	for(u8Counter=0; u8Counter<dButton_Last; u8Counter++)
	{
		tButtons[u8Counter].eEvent = dButtonEvent_None;
		if( Buttons_privIsPreseed(u8Counter) )
		{
			tButtons[u8Counter].u16PressedCounter++;
			if( tButtons[u8Counter].u16PressedCounter%(200/dTimeUnit) == 0U )
			{
				tButtons[u8Counter].eEvent = dButtonEvent_Pressed200ms;
			}
			if( tButtons[u8Counter].u16PressedCounter == (3000/dTimeUnit) )
			{
				tButtons[u8Counter].eEvent = dButtonEvent_Pressed3s;
			}
		}
		else
		{
			if( tButtons[u8Counter].u16PressedCounter != 0U )
			{
				tButtons[u8Counter].eEvent = dButtonEvent_Click;
			}
			tButtons[u8Counter].u16PressedCounter=0U;
		}
	}
}

Button_Event_T Button_GetEvent(Button_Select_T eButton)
{
	return tButtons[eButton].eEvent;
}

