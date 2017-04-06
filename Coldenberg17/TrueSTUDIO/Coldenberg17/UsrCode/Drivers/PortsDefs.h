/*
 * PortsDefs.h
 *
 *  Created on: Aug 14, 2016
 *      Author: Kuba
 */

#ifndef PORTSDEFS_H_
#define PORTSDEFS_H_

#include "stm32f1xx_hal_gpio.h"

//LEDs
#define LED1_GPIO    GPIOB
#define LED1_PIN     GPIO_PIN_5
#define LED1_PinActiveState  1

#define LED2_GPIO    GPIOB
#define LED2_PIN     GPIO_PIN_4
#define LED2_PinActiveState  1

#define LED3_GPIO    GPIOB
#define LED3_PIN     GPIO_PIN_3
#define LED3_PinActiveState  1


//Display
#define DIG_1_GPIO    GPIOA
#define DIG_1_PIN     GPIO_PIN_7
#define DIG1_PinActiveState	0
#define DIG_2_GPIO    GPIOA
#define DIG_2_PIN     GPIO_PIN_10
#define DIG2_PinActiveState	0

#define DIG_A_GPIO    GPIOA
#define DIG_A_PIN     GPIO_PIN_12
#define DIG_A_PinActiveState 1
#define DIG_B_GPIO    GPIOA
#define DIG_B_PIN     GPIO_PIN_5
#define DIG_B_PinActiveState 1
#define DIG_C_GPIO    GPIOA
#define DIG_C_PIN     GPIO_PIN_1
#define DIG_C_PinActiveState 1
#define DIG_D_GPIO    GPIOA
#define DIG_D_PIN     GPIO_PIN_6
#define DIG_D_PinActiveState 1
#define DIG_E_GPIO    GPIOA
#define DIG_E_PIN     GPIO_PIN_4
#define DIG_E_PinActiveState 1
#define DIG_F_GPIO    GPIOA
#define DIG_F_PIN     GPIO_PIN_8
#define DIG_F_PinActiveState 1
#define DIG_G_GPIO    GPIOA
#define DIG_G_PIN     GPIO_PIN_11
#define DIG_G_PinActiveState 1

//Buttons
#define BUTTON_1_GPIO    GPIOB
#define BUTTON_1_PIN     GPIO_PIN_9

#define BUTTON_2_GPIO    GPIOB
#define BUTTON_2_PIN     GPIO_PIN_8

#define BUTTON_3_GPIO    GPIOB
#define BUTTON_3_PIN     GPIO_PIN_7

//Relays
#define RelayCompressor_GPIO			GPIOB
#define RelayCompressor_PIN     		GPIO_PIN_15
#define RelayCompressor_PinActiveState	1U

#define RelayTapfied_GPIO    			GPIOB
#define RelayTapfied_PIN     			GPIO_PIN_14
#define RelayTapfied_PinActiveState		1U

#define RelayLight_GPIO    				GPIOB
#define RelayLight_PIN     				GPIO_PIN_13
#define RelayLight_PinActiveState		1U

//BLuetooth
#define BLUETOOTH_GPIO 		GPIOB
#define BLUETOOTH_PIN 		GPIO_PIN_8

#endif /* PORTSDEFS_H_ */
