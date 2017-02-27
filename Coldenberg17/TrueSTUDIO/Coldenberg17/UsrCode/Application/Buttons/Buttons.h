/*
 * BUTTONS.h
 *
 *  Created on: Aug 14, 2016
 *      Author: Kuba
 */

#ifndef BUTTONS_H_
#define BUTTONS_H_

#include "stdbool.h"
#include <stdint.h>

typedef enum
{
	dButton1,
	dButton2,
	dButton3,

	dButton_Last,
}Button_Select_T;

typedef enum
{
	dButtonEvent_None,
	dButtonEvent_Click,
	dButtonEvent_Pressed200ms,
	dButtonEvent_Pressed3s,
}Button_Event_T;

void Buttons_Init(void);
void Buttons_Perform(void);
void Buttons_GenerateEvent(void);
Button_Event_T Button_GetEvent(Button_Select_T eButton);
#endif /* BUTTONS_H_ */
