/*
 * bsp.c
 *
 *  Created on: Jan 22, 2024
 *      Author: Sayed
 */
#include "GPIO_driver.h"
#include "bsp.h"

void systick_init(void){
SysTick -> CVR = 0x1U;
SysTick ->RVR = 16000000;
SysTick ->CSR |= (1 << 0);
SysTick ->CSR |= (1 << 1);
SysTick ->CSR |= (1 << 2);
}

void SPI2_GPIOInit(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber, uint8_t ALTFN_Mode){
GPIO_Handle_t SPIPins;
SPIPins.pGPIOx = pGPIOx;
/*configuring pin 9 to be NSS*/
SPIPins.GPIO_PinConfig.GPIO_PinNumber =  PinNumber;
SPIPins.GPIO_PinConfig.GPIO_PinMode   =  GPIO_MODE_ALTFN;
SPIPins.GPIO_PinConfig.GPIO_PinAltFunMode   =  ALTFN_Mode;
SPIPins.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
SPIPins.GPIO_PinConfig.GPIO_PinPuPdControl  = GPIO_NO_PUPD;
GPIO_Init(&SPIPins);
}
void SysTick_Handler(void){
	GPIO_ToggleOutputPin(GPIOA, GPIO_PIN_NO_5);
}

void delay(uint32_t ms){
	for(uint32_t i = 0; i < (ms * (SysClock / 1000)); i++){
		;
	}
}
