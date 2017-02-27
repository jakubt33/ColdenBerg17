/*
 * Debouncer.c
 *
 *  Created on: Aug 14, 2016
 *      Author: Kuba
 */

#include "Debouncer.h"

/*! Public functions */
void Debouncer_Init(Debouncer_T *pThis, uint16_t u16InitCount, uint16_t u16InitData) //pass number in argument
{
	pThis->u16Counter = u16InitCount;
	pThis->u16InitCounter = u16InitCount;
	pThis->u16Data = u16InitData;
	pThis->u16CurrrentData = u16InitData;
}

void Debouncer_Apply(Debouncer_T *pThis, uint16_t u16NewData) //pass number in argument
{
	if( u16NewData != pThis->u16CurrrentData )
	{
		pThis->u16Counter = pThis->u16InitCounter;
	}
	else if( pThis->u16Counter != 0U )
	{
		pThis->u16Counter--;
	}

	if(pThis->u16Counter == 0U)
	{
		pThis->u16Data = u16NewData;
	}
	pThis->u16CurrrentData = u16NewData;
}

uint16_t Debouncer_GetData(Debouncer_T *pThis)
{
	return pThis->u16Data;
}

