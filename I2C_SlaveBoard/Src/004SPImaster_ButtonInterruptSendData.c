/*
 * main.c
 *
 *  Created on: Jan 31, 2024
 *      Author: Sayed
 */
#include <string.h>
#include "GPIO_driver.h"
#include "SPI_driver.h"
#include "bsp.h"

int main(void){
  /*configuring the switch*/
  SYSCFG_CLKEN;
  GPIO_Handle_t SW;
  SW.pGPIOx = GPIOC;
  SW.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_13;
  SW.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IT_FT;
  SW.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
  GPIO_Init(&SW);

  GPIO_IRQInterruptConfig(EXTI10_15, ENABLE);
  GPIO_IRQPriorityConfig(EXTI10_15, 1);

  /*configuring the Pins alternate function as SPI2*/
  SPI2_GPIOInit(GPIOB, GPIO_PIN_NO_9,  5); /*NSS*/
  SPI2_GPIOInit(GPIOB, GPIO_PIN_NO_10, 5); /*SCK*/
  SPI2_GPIOInit(GPIOB, GPIO_PIN_NO_14, 5); /*MISO*/
  SPI2_GPIOInit(GPIOB, GPIO_PIN_NO_15, 5); /*MOSI*/

  while(1){
	  ;
	}
}

void EXTI15_10_IRQHandler(void){
	__asm(
	  "CPSID  I \n"
	);
	if(EXTI ->PR & (1 << GPIO_PIN_NO_13)){ /*if the interruput is triggerd by the required pin*/
		/*configuring the SPI2 registers*/
		SPI_Handle test;
		test.pSPIx = SPI2;
	    test.config.SPI_BusConfig = SPI_BUS_FD;
		test.config.SPI_ModeConfig = SPI_MODE_MASTER;
		test.config.SPI_SclkSpeed = SPI_ClckSPeed_DIV8;
		test.config.SPI_DFF = SPI_DFF_8;
		test.config.SPI_COPL = SPI_CPOL_LOW;
		test.config.SPI_CPHA = SPI_CPHA_LOW;
		test.config.SPI_SSM = SPI_SSM_DI;
		/*enabling the clock for SPI2*/
		SPI_CLKCNT(test.pSPIx, ENABLE);
		 /*intializing the clock with the previous configurations*/
		SPI_Init(&test);

		/*enabling SSOE so NSS will pulled down when SPI is enabled*/
		SSOE_Enable(test.pSPIx, ENABLE);
		uint8_t data = 0x01; /*datat to be sent*/
		uint8_t Rdata; /*dummy data read while sending the datat*/

		/*enabling the SPI*/
		SPI_Enable(test.pSPIx, ENABLE);

		/*sending the data*/
		SPI_SendData(test.pSPIx, &data, sizeof(data));

		/*wait for BSY flag to sit since there is 2 ABP clocks between writing and the BSY flag bit to sit*/
		while(!(GetFlagStatus(test.pSPIx, SPI_TXE_FLAG)));
		while(GetFlagStatus(test.pSPIx, SPI_BSY_FLAG));

		/*read the dummy data sent by the slave*/
		SPI_ReceiveData(test.pSPIx, &Rdata, 1);

		/*waiting until busy flag is 0 and the bits are all transmitted*/
		while(GetFlagStatus(test.pSPIx, SPI_BSY_FLAG));

		/*desabling SPI after data transmittion is done*/
		SPI_Enable(test.pSPIx, DISABLE);
		EXTI ->PR |= (1 << GPIO_PIN_NO_13); /*clear the pending bit in EXTI*/
	}
	__asm(
	  "CPSIE  I \n"
	);
}
