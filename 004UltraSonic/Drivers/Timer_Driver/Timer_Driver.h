/*
 * Timer_Driver.h
 *
 *  Created on: Mar 14, 2024
 *      Author: Sayed
 */

#ifndef TIMER_DRIVER_TIMER_DRIVER_H_
#define TIMER_DRIVER_TIMER_DRIVER_H_
#include "STMF446RE.h"

typedef struct {
	uint16_t AutoReloadVal;
	uint16_t PreScalerVal;
	uint8_t InterruptEnorDi;
}BasicTimer_config;

typedef struct {
	BasicTimer_type *pTIMx;
	BasicTimer_config config;
}BasicTimer_Handle_t;



void TimerStart(BasicTimer_type *pTIMx,uint8_t EnorDi);
void BasicTimerInit(BasicTimer_Handle_t *pTimerHandle);
#endif /* TIMER_DRIVER_TIMER_DRIVER_H_ */
