/*
 * Flash.c
 *
 *  Created on: Aug 14, 2016
 *      Author: Kuba
 */

#include "Flash.h"
#include "Drivers/PortsDefs.h"
#include "stm32f1xx_hal_flash.h"

#define MemoryBlockStartAddress 0x08010000

static uint32_t u32Address = MemoryBlockStartAddress;

static FLASH_EraseInitTypeDef EraseInitStruct =
{
	.TypeErase   = FLASH_TYPEERASE_PAGES,
	.PageAddress = MemoryBlockStartAddress,
	.NbPages     = 1,
};

/*! Public functions */
void Flash_SaveValue( uint16_t u16NewValue )
{
	uint16_t u16LastValue = *(uint16_t *)u32Address;
	while( (u16LastValue != 0xFFFF) && (u32Address < MemoryBlockStartAddress + FLASH_PAGE_SIZE - 2) )
	{
		u32Address += 2;
		u16LastValue = *(uint16_t *)u32Address;
	}

	//page should be erased (-2 for safety)
	HAL_FLASH_Unlock();
	if( u32Address >= MemoryBlockStartAddress + FLASH_PAGE_SIZE - 2u )
	{
		uint32_t u32PageError;
		HAL_FLASHEx_Erase(&EraseInitStruct, &u32PageError);

		u32Address = MemoryBlockStartAddress;
	}

	HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD, u32Address, u16NewValue);
	HAL_FLASH_Lock();

	u32Address += 2;
}

uint16_t Flash_GetLastValue( void )
{
	uint32_t uAddress = MemoryBlockStartAddress;
	uint16_t uTempLastValue = *(uint16_t *)uAddress;
	uint16_t uLastValue = uTempLastValue;
	while( (uTempLastValue != 0xFFFF) && (uAddress < MemoryBlockStartAddress + FLASH_PAGE_SIZE - 2) )
	{
		uLastValue = uTempLastValue;
		uAddress += 2;
		uTempLastValue = *(uint16_t *)uAddress;
	}
	return uLastValue;
}
