/*
 * main.c
 *
 *  Created on: Mar 14, 2024
 *      Author: Sayed
 */
#include "GPIO_driver.h"
#include "RCC_driver.h"
#include "bsp.h"
#include "string.h"
#include "Timer_Driver.h"

#define MAX_DISTANCE_TIME	11765U

GPIO_Handle_t Echo, Trigg, LED;
BasicTimer_Handle_t Timer1, Timer2;
uint16_t timer2_Ticks;
const uint32_t Ticks = 1U;
float distance;
const float speedOfSound = 0.0343/2;
int main(void){
/*configuration starts here*/
	/*configure the echo pin*/
	Echo.pGPIOx = GPIOA;
	Echo.GPIO_PinConfig.GPIO_PinNumber =  GPIO_PIN_NO_8;
	Echo.GPIO_PinConfig.GPIO_PinMode   =  GPIO_MODE_IT_RFT;
	Echo.GPIO_PinConfig.GPIO_PinSpeed  =  GPIO_SPEED_FAST;
	Echo.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	Echo.GPIO_PinConfig.GPIO_PinPuPdControl  = GPIO_NO_PUPD;

	/*configure the Trigg Pin*/
	Trigg.pGPIOx = GPIOA;
	Trigg.GPIO_PinConfig.GPIO_PinNumber =  GPIO_PIN_NO_9;
	Trigg.GPIO_PinConfig.GPIO_PinMode   =  GPIO_MODE_OUT;
	Trigg.GPIO_PinConfig.GPIO_PinSpeed  =  GPIO_SPEED_FAST;
	Trigg.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	Trigg.GPIO_PinConfig.GPIO_PinPuPdControl  = GPIO_NO_PUPD;

	/*configure the LED pin*/
	LED.pGPIOx = GPIOA;
	LED.GPIO_PinConfig.GPIO_PinNumber =  GPIO_PIN_NO_5;
	LED.GPIO_PinConfig.GPIO_PinMode   =  GPIO_MODE_OUT;
	LED.GPIO_PinConfig.GPIO_PinSpeed  =  GPIO_SPEED_FAST;
	LED.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	LED.GPIO_PinConfig.GPIO_PinPuPdControl  = GPIO_NO_PUPD;

	/*configure timer1*/
	Timer1.pTIMx = TIM6;
	Timer1.config.InterruptEnorDi = ENABLE;
	Timer1.config.PreScalerVal = 15U;
	Timer1.config.AutoReloadVal = 9U;

	/*configure timer2*/
	Timer2.pTIMx = TIM7;
	Timer2.config.AutoReloadVal = MAX_DISTANCE_TIME;
	Timer2.config.PreScalerVal  = 15U;

/*Configuration ends here*/

/*Initialization starts here*/
	/*initialize the Pins*/
	GPIO_CLKCNT(GPIOA,ENABLE);
	GPIO_Init(&Echo);
	GPIO_Init(&Trigg);
	GPIO_Init(&LED);

	/*initialize the Timer*/
	BasicTimerInit(&Timer1);
	BasicTimerInit(&Timer2);

	/*initialize SysTick*/
	systick_init(Ticks);

	/*initializing interrupts for Timer1, Timer2 and Echo pin*/
	GPIO_IRQInterruptConfig(IRQ_TIM6_DAC, ENABLE);
	GPIO_IRQInterruptConfig(IRQ_TIM7, ENABLE);
	GPIO_IRQInterruptConfig(IRQ_EXTI5_9, ENABLE);
/*Initialization ends here*/

	GPIO_IRQPriorityConfig(IRQ_TIM6_DAC, 1);
	GPIO_IRQPriorityConfig(IRQ_TIM7, 2);
	GPIO_IRQPriorityConfig(IRQ_EXTI5_9, 3);
/*Code starts here*/
	while(1){
		delay(1U);
		TimerStart(Timer1.pTIMx, ENABLE);
		GPIO_ToggleOutputPin(Trigg.pGPIOx, Trigg.GPIO_PinConfig.GPIO_PinNumber);
	}

/*Code ends here*/
}

void SysTick_Handler(void){
	__asm(
			"CPSID I	\n"
	);
	GPIO_ToggleOutputPin(LED.pGPIOx, LED.GPIO_PinConfig.GPIO_PinNumber);
	__asm(
			"CPSIE I	\n"
	);
}

void TIM6_DAC_IRQHandler(){
	__asm(
			"CPSID I	\n"
	);
	TimerStart(Timer1.pTIMx, DISABLE);
	Timer1.pTIMx->SR &= ~(1 << TIM_SR_UIF);
	GPIO_ToggleOutputPin(Trigg.pGPIOx, Trigg.GPIO_PinConfig.GPIO_PinNumber);
	__asm(
			"CPSIE I	\n"
	);
}

void EXTI9_5_IRQHandler(){
	__asm(
			"CPSID I	\n"
	);
	EXTI->PR |= (1 << Echo.GPIO_PinConfig.GPIO_PinNumber);
	if(GPIO_ReadFromInputPin(Echo.pGPIOx, Echo.GPIO_PinConfig.GPIO_PinNumber) == 1U){
		TimerStart(Timer2.pTIMx, ENABLE);
	}else{
		TimerStart(Timer2.pTIMx, DISABLE);
		Timer2.pTIMx->SR &= ~(1 << TIM_SR_UIF);
		timer2_Ticks = Timer2.pTIMx->CNT;
		Timer2.pTIMx->CNT = 0U;
		SysTick ->RVR = (7989U / Ticks) * timer2_Ticks;
	}
	__asm(
			"CPSIE I	\n"
	);
}
