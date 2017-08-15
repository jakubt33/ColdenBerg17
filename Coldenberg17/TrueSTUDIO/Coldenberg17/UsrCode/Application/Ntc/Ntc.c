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
#define dTempMax		28
#define dTempMin		6

typedef enum
{
	d6_0C = 0,
	d6_5C,
	d7_0C,
	d7_5C,
	d8_0C,
	d8_5C,
	d9_0C,
	d9_5C,
	d10_0C,
	d10_5C,
	d11_0C,
	d11_5C,
	d12_0C,
	d12_5C,
	d13_0C,
	d13_5C,
	d14_0C,
	d14_5C,
	d15_0C,
	d15_5C,
	d16_0C,
	d16_5C,
	d17_0C,
	d17_5C,
	d18_0C,
	d18_5C,
	d19_0C,
	d19_5C,
	d20_0C,
	d20_5C,
	d21_0C,
	d21_5C,
	d22_0C,
	d22_5C,
	d23_0C,
	d23_5C,
	d24_0C,
	d24_5C,
	d25_0C,
	d25_5C,
	d26_0C,
	d26_5C,
	d27_0C,
	d27_5C,
	d28_0C,
	dTempLast,
}Celcius_T;

uint16_t tempTable[dTempLast+1][2] =
{
// Celsius = ADC max value
	[ d6_0C  ] = { 2400, 2424 },
	[ d6_5C  ] = { 2423, 2409 },
	[ d7_0C  ] = { 2408, 2388 },
	[ d7_5C  ] = { 2387, 2367 },
	[ d8_0C  ] = { 2366, 2343 },
	[ d8_5C  ] = { 2342, 2313 },
	[ d9_0C  ] = { 2312, 2286 },
	[ d9_5C  ] = { 2285, 2250 },
	[ d10_0C ] = { 2249, 2208 },
	[ d10_5C ] = { 2207, 2184 },
	[ d11_0C ] = { 2183, 2157 },
	[ d11_5C ] = { 2156, 2121 },
	[ d12_0C ] = { 2120, 2091 },
	[ d12_5C ] = { 2090, 2073 },
	[ d13_0C ] = { 2072, 2055 },
	[ d13_5C ] = { 2054, 2025 },
	[ d14_0C ] = { 2024, 2001 },
	[ d14_5C ] = { 2000, 1968 },
	[ d15_0C ] = { 1967, 1935 },
	[ d15_5C ] = { 1934, 1914 },
	[ d16_0C ] = { 1913, 1890 },
	[ d16_5C ] = { 1889, 1860 },
	[ d17_0C ] = { 1859, 1836 },
	[ d17_5C ] = { 1835, 1839 },
	[ d18_0C ] = { 1838, 1809 },
	[ d18_5C ] = { 1808, 1755 },
	[ d19_0C ] = { 1754, 1749 },
	[ d19_5C ] = { 1748, 1746 },
	[ d20_0C ] = { 1745, 1719 },
	[ d20_5C ] = { 1718, 1671 },
	[ d21_0C ] = { 1670, 1641 },
	[ d21_5C ] = { 1640, 1632 },
	[ d22_0C ] = { 1631, 1614 },
	[ d22_5C ] = { 1613, 1590 },
	[ d23_0C ] = { 1589, 1557 },
	[ d23_5C ] = { 1556, 1530 },
	[ d24_0C ] = { 1529, 1503 },
	[ d24_5C ] = { 1502, 1470 },
	[ d25_0C ] = { 1469, 1431 },
	[ d25_5C ] = { 1430, 1392 },
	[ d26_0C ] = { 1391, 1365 },
	[ d26_5C ] = { 1364, 1344 },
	[ d27_0C ] = { 1343, 1323 },
	[ d27_5C ] = { 1322, 1296 },
	[ d28_0C ] = { 1295, 1350 },

	[ dTempLast ] = { 0, 1349 }
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

	uint8_t tempInterator = 0u;

	/* Temperature is too low so return 0deg!! */
	if( tempTable[tempInterator][0] <= ADC)
		return 0u;

	while (!( ADC <= tempTable[tempInterator][0] && ADC >= tempTable[tempInterator][1] ))
	{
		tempInterator++;
	}

	//temp resolution is 0.5deg */
	u8Temperature = (tempInterator / 2u ) + dTempMin;
	return (tempInterator < dTempLast) ? u8Temperature : dNtc_ErrorTemp;
}

uint16_t Ntc_GetRawValue( void )
{
	return FIR_GetFilteredValue( &kFilter );
}
