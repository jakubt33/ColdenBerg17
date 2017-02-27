/*
 * Counter.h
 *
 *  Created on: Aug 14, 2016
 *      Author: Kuba
 */

#ifndef Counter_H_
#define Counter_H_

#include "stdbool.h"
#include <stdint.h>

void Counter_SetTimeout( uint16_t *u16Counter, uint16_t u16NewTimeout );
void Counter_TickTimeout( uint16_t *u16Counter );
bool Counter_IsTimeoutExpired( uint16_t *u16Counter );

#endif /* Counter_H_ */
