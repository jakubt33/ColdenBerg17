/*
 * Display.c
 *
 *  Created on: Aug 14, 2016
 *      Author: Kuba
 */
#include "stdbool.h"
#include "Drivers/PortsDefs.h"
#include "Display.h"

//Private defines
#define DIG_1_SetOff()  HAL_GPIO_WritePin(DIG_1_GPIO, DIG_1_PIN, !DIG1_PinActiveState)
#define DIG_1_SetOn()   HAL_GPIO_WritePin(DIG_1_GPIO, DIG_1_PIN, DIG1_PinActiveState)
#define DIG_1_IsOn()    HAL_GPIO_ReadPin(DIG_1_GPIO, DIG_1_PIN)

#define DIG_2_SetOff()  HAL_GPIO_WritePin(DIG_2_GPIO, DIG_2_PIN, !DIG2_PinActiveState)
#define DIG_2_SetOn()   HAL_GPIO_WritePin(DIG_2_GPIO, DIG_2_PIN, DIG2_PinActiveState)
#define DIG_2_IsOn()    HAL_GPIO_ReadPin(DIG_2_GPIO, DIG_2_PIN)

#define DIG_A_SetOff()  HAL_GPIO_WritePin(DIG_A_GPIO, DIG_A_PIN, !DIG_A_PinActiveState)
#define DIG_A_SetOn()   HAL_GPIO_WritePin(DIG_A_GPIO, DIG_A_PIN, DIG_A_PinActiveState)
#define DIG_A_IsOn()    HAL_GPIO_ReadPin(DIG_A_GPIO, DIG_A_PIN)

#define DIG_B_SetOff()  HAL_GPIO_WritePin(DIG_B_GPIO, DIG_B_PIN, !DIG_B_PinActiveState)
#define DIG_B_SetOn()   HAL_GPIO_WritePin(DIG_B_GPIO, DIG_B_PIN, DIG_B_PinActiveState)
#define DIG_B_IsOn()    HAL_GPIO_ReadPin(DIG_B_GPIO, DIG_B_PIN)

#define DIG_C_SetOff()  HAL_GPIO_WritePin(DIG_C_GPIO, DIG_C_PIN, !DIG_C_PinActiveState)
#define DIG_C_SetOn()   HAL_GPIO_WritePin(DIG_C_GPIO, DIG_C_PIN, DIG_C_PinActiveState)
#define DIG_C_IsOn()    HAL_GPIO_ReadPin(DIG_C_GPIO, DIG_C_PIN)

#define DIG_D_SetOff()  HAL_GPIO_WritePin(DIG_D_GPIO, DIG_D_PIN, !DIG_D_PinActiveState)
#define DIG_D_SetOn()   HAL_GPIO_WritePin(DIG_D_GPIO, DIG_D_PIN, DIG_D_PinActiveState)
#define DIG_D_IsOn()    HAL_GPIO_ReadPin(DIG_D_GPIO, DIG_D_PIN)

#define DIG_E_SetOff()  HAL_GPIO_WritePin(DIG_E_GPIO, DIG_E_PIN, !DIG_E_PinActiveState)
#define DIG_E_SetOn()   HAL_GPIO_WritePin(DIG_E_GPIO, DIG_E_PIN, DIG_E_PinActiveState)
#define DIG_E_IsOn()    HAL_GPIO_ReadPin(DIG_E_GPIO, DIG_E_PIN)

#define DIG_F_SetOff()  HAL_GPIO_WritePin(DIG_F_GPIO, DIG_F_PIN, !DIG_F_PinActiveState)
#define DIG_F_SetOn()   HAL_GPIO_WritePin(DIG_F_GPIO, DIG_F_PIN, DIG_F_PinActiveState)
#define DIG_F_IsOn()    HAL_GPIO_ReadPin(DIG_F_GPIO, DIG_F_PIN)

#define DIG_G_SetOff()  HAL_GPIO_WritePin(DIG_G_GPIO, DIG_G_PIN, !DIG_G_PinActiveState)
#define DIG_G_SetOn()   HAL_GPIO_WritePin(DIG_G_GPIO, DIG_G_PIN, DIG_G_PinActiveState)
#define DIG_G_IsOn()    HAL_GPIO_ReadPin(DIG_G_GPIO, DIG_G_PIN)

//Private prototypes
static void privDisplayNumber(uint8_t u8Number);

//Private prototypes of functions displaying only one digit
static void Display_0(void);
static void Display_1(void);
static void Display_2(void);
static void Display_3(void);
static void Display_4(void);
static void Display_5(void);
static void Display_6(void);
static void Display_7(void);
static void Display_8(void);
static void Display_9(void);

static void(*DigitTable[10])(void) = { 	Display_0,
										Display_1,
										Display_2,
										Display_3,
										Display_4,
										Display_5,
										Display_6,
										Display_7,
										Display_8,
										Display_9};

static uint8_t u8DisplayNumber = 0U;

/*! Public functions */
void Display_Perform(void)
{
	privDisplayNumber(u8DisplayNumber);
}

void Display_InitState(void)
{
	DIG_1_SetOff();
	DIG_2_SetOff();
	DIG_A_SetOff();
	DIG_B_SetOff();
	DIG_C_SetOff();
	DIG_D_SetOff();
	DIG_E_SetOff();
	DIG_F_SetOff();
	DIG_G_SetOff();
}

void privDisplayNumber(uint8_t u8Number)
{
	if(u8Number>99) u8Number = 99;

	uint8_t u8Dig1 = u8Number/10;
	uint8_t u8Dig2 = u8Number%10;
	static bool bDig1 = false;//start with last digit
	if(bDig1)
	{
		DIG_1_SetOn();
		DIG_2_SetOff();
		DigitTable[u8Dig1]();
		bDig1=false;
	}
	else
	{
		DIG_1_SetOff();
		DIG_2_SetOn();
		DigitTable[u8Dig2]();
		bDig1=true;
	}
}

static void Display_0(void)
{
	DIG_A_SetOn();
	DIG_B_SetOn();
	DIG_C_SetOn();
	DIG_D_SetOn();
	DIG_E_SetOn();
	DIG_F_SetOn();
	DIG_G_SetOff();
}

static void Display_1(void)
{
	DIG_A_SetOff();
	DIG_B_SetOn();
	DIG_C_SetOn();
	DIG_D_SetOff();
	DIG_E_SetOff();
	DIG_F_SetOff();
	DIG_G_SetOff();
}

static void Display_2(void)
{
	DIG_A_SetOn();
	DIG_B_SetOn();
	DIG_C_SetOff();
	DIG_D_SetOn();
	DIG_E_SetOn();
	DIG_F_SetOff();
	DIG_G_SetOn();
}
static void Display_3(void)
{
	DIG_A_SetOn();
	DIG_B_SetOn();
	DIG_C_SetOn();
	DIG_D_SetOn();
	DIG_E_SetOff();
	DIG_F_SetOff();
	DIG_G_SetOn();
}
static void Display_4(void)
{
	DIG_A_SetOff();
	DIG_B_SetOn();
	DIG_C_SetOn();
	DIG_D_SetOff();
	DIG_E_SetOff();
	DIG_F_SetOn();
	DIG_G_SetOn();
}
static void Display_5(void)
{
	DIG_A_SetOn();
	DIG_B_SetOff();
	DIG_C_SetOn();
	DIG_D_SetOn();
	DIG_E_SetOff();
	DIG_F_SetOn();
	DIG_G_SetOn();
}
static void Display_6(void)
{
	DIG_A_SetOn();
	DIG_B_SetOff();
	DIG_C_SetOn();
	DIG_D_SetOn();
	DIG_E_SetOn();
	DIG_F_SetOn();
	DIG_G_SetOn();
}

static void Display_7(void)
{
	DIG_A_SetOn();
	DIG_B_SetOn();
	DIG_C_SetOn();
	DIG_D_SetOff();
	DIG_E_SetOff();
	DIG_F_SetOff();
	DIG_G_SetOff();
}
static void Display_8(void)
{
	DIG_A_SetOn();
	DIG_B_SetOn();
	DIG_C_SetOn();
	DIG_D_SetOn();
	DIG_E_SetOn();
	DIG_F_SetOn();
	DIG_G_SetOn();
}
static void Display_9(void)
{
	DIG_A_SetOn();
	DIG_B_SetOn();
	DIG_C_SetOn();
	DIG_D_SetOn();
	DIG_E_SetOff();
	DIG_F_SetOn();
	DIG_G_SetOn();
}

void Display_DisplayNumber(uint8_t u8NumberToDisplay)
{
	u8DisplayNumber = u8NumberToDisplay;
}
