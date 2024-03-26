/*
 * Timer_Driver.c
 *
 *  Created on: Mar 14, 2024
 *      Author: Sayed
 */

#include "Timer_Driver.h"

void TimerStart(BasicTimer_type *pTIMx,uint8_t EnorDi){
	if(EnorDi == ENABLE){
		pTIMx->CR1 |= (1 << TIM_CR1_CEN);
	}
	else{
		pTIMx->CR1 &= ~(1 << TIM_CR1_CEN);
	}
}

static void TimerClkEnable(BasicTimer_type *pTIMx, uint8_t EnorDi){
	if(EnorDi == ENABLE){
		if(pTIMx == TIM6){TIM6_CLKEN();}
		else if(pTIMx == TIM7){TIM7_CLKEN();}
	}else{
		if(pTIMx == TIM6){TIM6_CLKDI();}
		else if(pTIMx == TIM7){TIM7_CLKDI();}
	}
}

void BasicTimerInit(BasicTimer_Handle_t *pTimerHandle){
	/*Enable the clock for the Timer*/
	TimerClkEnable(pTimerHandle->pTIMx, ENABLE);

	/*set the auto reload value*/
	pTimerHandle->pTIMx->ARR = pTimerHandle->config.AutoReloadVal;

	/*set the Prescaler Value*/
	pTimerHandle->pTIMx->PSC = pTimerHandle->config.PreScalerVal;

	/*Enable the auto reload register*/
	pTimerHandle->pTIMx->CR1 |= (1 << TIM_CR1_ARPE);

	/*Enable interrupts*/
	if(pTimerHandle->config.InterruptEnorDi == ENABLE){
		pTimerHandle->pTIMx->DIER |= (1 << TIM_DIER_UIE);
	}
}
