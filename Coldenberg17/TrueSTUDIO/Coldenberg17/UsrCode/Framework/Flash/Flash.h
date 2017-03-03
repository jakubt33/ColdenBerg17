/*
 * Flash.h
 *
 *  Created on: Aug 14, 2016
 *      Author: Kuba
 */

#ifndef FLASH_H_
#define FLASH_H_

#include "stdbool.h"
#include <stdint.h>

void Flash_SaveValue( uint16_t u16NewValue );
uint16_t Flash_GetLastValue( void );

#endif /* FLASH_H_ */
