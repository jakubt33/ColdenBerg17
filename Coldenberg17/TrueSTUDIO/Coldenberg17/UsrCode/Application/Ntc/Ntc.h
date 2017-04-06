/*
 * Ntc.h
 *
 *  Created on: Aug 14, 2016
 *      Author: Kuba
 */

#ifndef NTC_H_
#define NTC_H_

#include "stdbool.h"
#include <stdint.h>

#define dNtc_ErrorTemp 0xffff

void Ntc_Initialize( void );
void Ntc_Perform( void );
uint16_t Ntc_GetValue( void  );
uint16_t Ntc_GetRawValue( void );

#endif /* NTC_H_ */
