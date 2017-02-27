/*
 * DEBOUNCER.h
 *
 *  Created on: Aug 14, 2016
 *      Author: Kuba
 */

#ifndef DEBOUNCER_H_
#define DEBOUNCER_H_

#include <stdint.h>

typedef struct Debouncer
{
	uint16_t u16Data;
	uint16_t u16CurrrentData;
	uint16_t u16Counter;
	uint16_t u16InitCounter;
}Debouncer_T;

void Debouncer_Init(Debouncer_T *pThis, uint16_t u16InitCount, uint16_t u16InitData);
void Debouncer_Apply(Debouncer_T *pThis, uint16_t u16NewData);
uint16_t Debouncer_GetData(Debouncer_T *pThis);

#endif /* DEBOUNCER_H_ */
