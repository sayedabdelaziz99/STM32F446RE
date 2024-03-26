/*
 * 002interrupt.c
 *
 *  Created on: Jan 24, 2024
 *      Author: Sayed
 */

#include "GPIO_driver.h"
#include "bsp.h"
int main(void){
	  /*configuring the LED*/
	  GPIO_Handle_t GPIOLed;
	  GPIOLed.pGPIOx = GPIOA;
	  GPIOLed.GPIO_PinConfig.GPIO_PinNumber =  GPIO_PIN_NO_5;
	  GPIOLed.GPIO_PinConfig.GPIO_PinMode   =  GPIO_MODE_OUT;
	  GPIOLed.GPIO_PinConfig.GPIO_PinSpeed  =  GPIO_SPEED_FAST;
	  GPIOLed.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	  GPIOLed.GPIO_PinConfig.GPIO_PinPuPdControl  = GPIO_NO_PUPD;
	  GPIO_Init(&GPIOLed);

	  /*configuring the switch*/
	  SYSCFG_CLKEN;
	  GPIO_Handle_t SW;
	  SW.pGPIOx = GPIOC;
	  SW.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_13;
	  SW.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IT_RT;
	  SW.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	  GPIO_Init(&SW);

	  GPIO_IRQInterruptConfig(IRQ_EXTI10_15, ENABLE);
	  GPIO_IRQPriorityConfig(IRQ_EXTI10_15, 1);
while(1){

}
}
void EXTI15_10_IRQHandler(void){
	GPIO_IRQHandling(GPIO_PIN_NO_13);
	GPIO_ToggleOutputPin(GPIOA, GPIO_PIN_NO_5);
}
