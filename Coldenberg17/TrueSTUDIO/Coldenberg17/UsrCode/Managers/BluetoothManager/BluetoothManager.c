/*
 * Bluetooth.c
 *
 *  Created on: Apr 6, 2017
 *      Author: Kuba
 */
#include "BluetoothManager.h"
#include "Drivers/PortsDefs.h"
#include "stm32f1xx_hal_uart.h"

#include "Application/Ntc/Ntc.h"

//Private defines
#define Bluetooth_IsConnected()    HAL_GPIO_ReadPin(BLUETOOTH_GPIO, BLUETOOTH_PIN)

extern UART_HandleTypeDef huart2;
uint8_t u8AdcValue = 0u;

/*! Public functions */
void BluetoothManager_Perform(void)
{
	if ( Bluetooth_IsConnected() )
	{
		u8AdcValue = Ntc_GetRawValue()/12;
		HAL_UART_Transmit_IT(&huart2, &u8AdcValue, 1);
	}

}

