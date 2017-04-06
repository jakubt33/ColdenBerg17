/*
 * FIR.h
 *
 *  Created on: Aug 14, 2016
 *      Author: Kuba
 */

#ifndef FIR_H_
#define FIR_H_

#include "stdbool.h"
#include <stdint.h>

typedef uint16_t FIR_Buffer;

typedef struct
{
	uint32_t u32FilteredValue;
	uint16_t u16Size;
	uint16_t u16Position;
	FIR_Buffer *tu16Buffer;
} FIR_T;

void FIR_Initialize( FIR_T *kFIR_Struct, FIR_Buffer *tu16Buffer, uint16_t u16BufferSize );
void FIR_RegisterValue( FIR_T *kFIR_Struct, uint16_t u16NewValue );
uint16_t FIR_GetFilteredValue( FIR_T *kFIR_Struct );

#endif /* FIR_H_ */
