/*
 * 001Led&Button.c
 *
 *  Created on: Jan 23, 2024
 *      Author: Sayed
 */
#include <stdint.h>
#include "STMF446RE.h"
#include "GPIO_driver.h"

void delay(uint32_t ms){
	for(int i = 0; i < ms; i++){
		;
	}
}
int main(void)
{
  /*configuring the LED*/
  GPIO_Handle_t GPIOLed;
  GPIOLed.pGPIOx = GPIOA;
  GPIOLed.GPIO_PinConfig.GPIO_PinNumber =  GPIO_PIN_NO_5;
  GPIOLed.GPIO_PinConfig.GPIO_PinMode   =  GPIO_MODE_OUT;
  GPIOLed.GPIO_PinConfig.GPIO_PinSpeed  =  GPIO_SPEED_FAST;
  GPIOLed.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
  GPIOLed.GPIO_PinConfig.GPIO_PinPuPdControl  = GPIO_NO_PUPD;
  GPIO_CLKCNT(GPIOA,ENABLE);
  GPIO_Init(&GPIOLed);

  /*configuring the switch*/
  GPIO_Handle_t SW;
  SW.pGPIOx = GPIOC;
  SW.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_13;
  SW.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IN;
  SW.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
  GPIO_CLKCNT(GPIOC,ENABLE);
  GPIO_Init(&SW);
  while(1){
	  if(GPIO_ReadFromInputPin(SW.pGPIOx, GPIO_PIN_NO_13) == 0){
		delay(100000);
		GPIO_ToggleOutputPin(GPIOA, GPIO_PIN_NO_5);
	}
  }
}
