/*
 * main.c
 *
 *  Created on: Jan 26, 2024
 *      Author: Sayed
 */
#include <string.h>
#include "GPIO_driver.h"
#include "SPI_driver.h"
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

	/*configuring the Pins alternate function as SPI2*/
	SPI2_GPIOInit(GPIOB, GPIO_PIN_NO_9,  5); /*NSS*/
	SPI2_GPIOInit(GPIOB, GPIO_PIN_NO_10, 5); /*SCK*/
	SPI2_GPIOInit(GPIOB, GPIO_PIN_NO_14, 5); /*MISO*/
	SPI2_GPIOInit(GPIOB, GPIO_PIN_NO_15, 5); /*MOSI*/

	/*configuring the SPI2 registers*/
	SPI_Handle test;
	test.pSPIx = SPI2;
	test.config.SPI_BusConfig = SPI_BUS_FD;
	test.config.SPI_ModeConfig = SPI_MODE_SLAVE;
	test.config.SPI_SclkSpeed = SPI_ClckSPeed_DIV8;
	test.config.SPI_DFF = SPI_DFF_8;
	test.config.SPI_COPL = SPI_CPOL_LOW;
	test.config.SPI_CPHA = SPI_CPHA_LOW;
	test.config.SPI_SSM = SPI_SSM_DI;
	SPI_CLKCNT(test.pSPIx, ENABLE);
	SPI_Init(&test);

	/*enabling the SPI*/
	SPI_Enable(test.pSPIx, ENABLE);

	uint8_t RData;


	while(1){
		/*first frame will contain the data length to be stored*/
		//SPI_ReceiveData(test.pSPIx, &RDataLen, 2);

		/*wait until bsy flag is 0*/
		//while(GetFlagStatus(test.pSPIx, SPI_BSY_FLAG) && !(GetFlagStatus(test.pSPIx, SPI_RXNE_FLAG)));

		/*read the data and store it in RData*/
		SPI_ReceiveData(test.pSPIx, &RData, 1);

		/*wait for BSY flag to sit since there is 2 ABP clocks between writing and the BSY flag bit to sit*/
		while(GetFlagStatus(test.pSPIx, SPI_RXNE_FLAG));
		while(GetFlagStatus(test.pSPIx, SPI_BSY_FLAG));

		/*if button in master is pressed, toggle the LED*/
		if(RData & 1U){
			GPIO_ToggleOutputPin(GPIOLed.pGPIOx, GPIOLed.GPIO_PinConfig.GPIO_PinNumber);
			//delay(5);
		}
	}
}
