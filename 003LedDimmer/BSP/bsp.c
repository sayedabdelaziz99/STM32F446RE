/*
 * bsp.c
 *
 *  Created on: Jan 22, 2024
 *      Author: Sayed
 */
#include "GPIO_driver.h"
#include "bsp.h"
#include "SPI_driver.h"

void systick_init(uint16_t Ticks_PerSecond){
SysTick -> CVR = 0x1U;
SysTick ->RVR = SysClock / Ticks_PerSecond;
SysTick ->CSR |= (1 << 0);
SysTick ->CSR |= (1 << 1);
SysTick ->CSR |= (1 << 2);
}

void SPI2_GPIOInit(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber, uint8_t ALTFN_Mode){
GPIO_Handle_t SPIPins;
SPIPins.pGPIOx = pGPIOx;
SPIPins.GPIO_PinConfig.GPIO_PinNumber =  PinNumber;
SPIPins.GPIO_PinConfig.GPIO_PinMode   =  GPIO_MODE_ALTFN;
SPIPins.GPIO_PinConfig.GPIO_PinAltFunMode   =  ALTFN_Mode;
SPIPins.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
SPIPins.GPIO_PinConfig.GPIO_PinPuPdControl  = GPIO_NO_PUPD;
GPIO_CLKCNT(pGPIOx, ENABLE);
GPIO_Init(&SPIPins);
}

void I2C1_GPIOInit(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber, uint8_t ALTFN_Mode){
GPIO_Handle_t I2CPins;
I2CPins.pGPIOx = pGPIOx;
I2CPins.GPIO_PinConfig.GPIO_PinNumber =  PinNumber;
I2CPins.GPIO_PinConfig.GPIO_PinMode   =  GPIO_MODE_ALTFN;
I2CPins.GPIO_PinConfig.GPIO_PinAltFunMode   =  ALTFN_Mode;
I2CPins.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_OD;
I2CPins.GPIO_PinConfig.GPIO_PinPuPdControl  = GPIO_PIN_PU;
I2CPins.GPIO_PinConfig.GPIO_PinSpeed = GPOI_SPEED_HIGH;
GPIO_CLKCNT(pGPIOx, ENABLE);
pGPIOx->LCKR &= ~(1 << PinNumber);
GPIO_Init(&I2CPins);
}

void USART_GPIOInit(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber, uint8_t ALTFN_Mode){
  GPIO_Handle_t USARTpins;
  USARTpins.pGPIOx = pGPIOx;
  USARTpins.GPIO_PinConfig.GPIO_PinNumber =  PinNumber;
  USARTpins.GPIO_PinConfig.GPIO_PinMode   =  GPIO_MODE_ALTFN;
  USARTpins.GPIO_PinConfig.GPIO_PinAltFunMode   =  ALTFN_Mode;
  USARTpins.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
  USARTpins.GPIO_PinConfig.GPIO_PinPuPdControl  = GPIO_PIN_PU;
  USARTpins.GPIO_PinConfig.GPIO_PinSpeed = GPOI_SPEED_HIGH;
  GPIO_CLKCNT(pGPIOx, ENABLE);
  pGPIOx->LCKR &= ~(1 << PinNumber);
  GPIO_Init(&USARTpins);
}

void GPIO_ButtonInit(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber){
	  GPIO_Handle_t SW;
	  SW.pGPIOx = pGPIOx;
	  SW.GPIO_PinConfig.GPIO_PinNumber = PinNumber;
	  SW.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IN;
	  SW.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	  GPIO_CLKCNT(SW.pGPIOx, ENABLE);
	  GPIO_Init(&SW);
}



void GPIO_TIM2Init(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber, uint8_t ALTFN_Mode){
	GPIO_Handle_t CH;
	CH.pGPIOx = pGPIOx;
	CH.GPIO_PinConfig.GPIO_PinNumber =  GPIO_PIN_NO_5;
	CH.GPIO_PinConfig.GPIO_PinMode   =  GPIO_MODE_ALTFN;
	CH.GPIO_PinConfig.GPIO_PinAltFunMode = ALTFN_Mode;
	CH.GPIO_PinConfig.GPIO_PinSpeed  =  GPIO_SPEED_FAST;
	CH.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	CH.GPIO_PinConfig.GPIO_PinPuPdControl  = GPIO_NO_PUPD;
	GPIO_CLKCNT(pGPIOx, ENABLE);
	pGPIOx->LCKR &= ~(1 << PinNumber);
	GPIO_Init(&CH);
}

void delay(uint32_t ms){
	for(uint32_t i = 0; i < (ms * (SysClock / 1000)); i++){
		;
	}
}
