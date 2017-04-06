/*
 * FIR.c
 *
 *  Created on: Aug 14, 2016
 *      Author: Kuba
 */

#include "FIR.h"
#include "Drivers/PortsDefs.h"

void FIR_Initialize( FIR_T *kFIR_Struct, FIR_Buffer *tu16Buffer, uint16_t u16BufferSize )
{
	kFIR_Struct->tu16Buffer = tu16Buffer;
	kFIR_Struct->u16Position = 0u;
	kFIR_Struct->u16Size = u16BufferSize;
	kFIR_Struct->u32FilteredValue = 0u;
}

void FIR_RegisterValue( FIR_T *kFIR_Struct, uint16_t u16NewValue )
{
	if ( kFIR_Struct->u16Position >= kFIR_Struct->u16Size )
	{
		kFIR_Struct->u16Position = 0u;
	}
	//Register value
	kFIR_Struct->tu16Buffer[ kFIR_Struct->u16Position++ ] = u16NewValue;

	//Calculate filtered value
	uint16_t uCounter = 0;
	uint32_t uSum = 0;
	for ( ; uCounter < kFIR_Struct->u16Size; uCounter++ )
	{
		uSum += kFIR_Struct->tu16Buffer[ uCounter ];
	}
	kFIR_Struct->u32FilteredValue = uSum/kFIR_Struct->u16Size;
}

uint16_t FIR_GetFilteredValue( FIR_T *kFIR_Struct )
{
	return kFIR_Struct->u32FilteredValue;
}

/*! Public functions */
