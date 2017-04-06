/*
 * Ntc.c
 *
 *  Created on: Aug 14, 2016
 *      Author: Kuba
 */

#include "Ntc.h"
#include "Drivers/PortsDefs.h"

#include "Framework/FIR/FIR.h"

#define dBufferSize 100u //10s (100ms *100)

FIR_Buffer tBuffer[ dBufferSize ];
FIR_T kFilter;

extern ADC_HandleTypeDef hadc1;
#define dTempRange 32
#define dADCModifier 0

// 9,5st - 2360
//11,0st - 2200
//19,0st - 1800
//24,5st - 1380
uint16_t tempTable[dTempRange] =
{
// Celsius = ADC max value
	[0]  = 3050,
	[1]  = 2988 - dADCModifier,
	[2]  = 2922 - dADCModifier,
	[3]  = 2856 - dADCModifier,
	[4]  = 2790 - dADCModifier,
	[5]  = 2724 - dADCModifier,
	[6]  = 2658 - dADCModifier,
	[7]  = 2592 - dADCModifier,
	[8]  = 2526 - dADCModifier,
	[9]  = 2460 - dADCModifier,
		[10] = 2200 - dADCModifier,
	[11] = 2328 - dADCModifier,
	[12] = 2262 - dADCModifier,
	[13] = 2196 - dADCModifier,
	[14] = 2130 - dADCModifier,
	[15] = 2064 - dADCModifier,
	[16] = 1998 - dADCModifier,
	[17] = 1932 - dADCModifier,
	[18] = 1866 - dADCModifier,
		[19] = 1800 - dADCModifier,
	[20] = 1720 - dADCModifier,
	[21] = 1640 - dADCModifier,
	[22] = 1560 - dADCModifier,
	[23] = 1480 - dADCModifier,
	[24] = 1400 - dADCModifier,
	[25] = 1320 - dADCModifier,
	[26] = 1240 - dADCModifier,
	[27] = 1160 - dADCModifier,
	[28] = 1080 - dADCModifier,
	[29] = 1000 - dADCModifier,
	[30] =  920 - dADCModifier,

	[31] = 0x0,
};


/*! Public functions */
void Ntc_Initialize( void )
{
	FIR_Initialize( &kFilter, tBuffer, dBufferSize );
	HAL_ADC_Start( &hadc1 );
}

/*! Call every 100ms */
void Ntc_Perform( void )
{
    if (HAL_ADC_PollForConversion( &hadc1, 100) == HAL_OK)
    {
		FIR_RegisterValue( &kFilter, HAL_ADC_GetValue(&hadc1) );
    }
}

uint16_t Ntc_GetValue( void  )
{
	uint8_t u8Temperature = 0u;
	uint16_t ADC = FIR_GetFilteredValue( &kFilter );
	while( tempTable[u8Temperature] > ADC )
	{
		u8Temperature++;
	}

	return (u8Temperature < dTempRange - 1U) ? u8Temperature : dNtc_ErrorTemp;
}

uint16_t Ntc_GetRawValue( void )
{
	return FIR_GetFilteredValue( &kFilter );
}
