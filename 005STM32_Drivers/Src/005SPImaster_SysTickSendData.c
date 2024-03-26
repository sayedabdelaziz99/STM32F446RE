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
  /*configuring the LED*/
  GPIO_Handle_t testPin;
  testPin.pGPIOx = GPIOC;
  testPin.GPIO_PinConfig.GPIO_PinNumber =  GPIO_PIN_NO_13;
  testPin.GPIO_PinConfig.GPIO_PinMode   =  GPIO_MODE_OUT;
  testPin.GPIO_PinConfig.GPIO_PinSpeed  =  GPIO_SPEED_FAST;
  testPin.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
  testPin.GPIO_PinConfig.GPIO_PinPuPdControl  = GPIO_NO_PUPD;
  GPIO_Init(&testPin);

  /*configuring the Pins alternate function as SPI2*/
  SPI2_GPIOInit(GPIOB, GPIO_PIN_NO_9,  5); /*NSS*/
  SPI2_GPIOInit(GPIOB, GPIO_PIN_NO_10, 5); /*SCK*/
  SPI2_GPIOInit(GPIOB, GPIO_PIN_NO_14, 5); /*MISO*/
  SPI2_GPIOInit(GPIOB, GPIO_PIN_NO_15, 5); /*MOSI*/

  /*intializing systick*/
  systick_init();

  while(1){
	  ;
	}
}

void SysTick_Handler(void){
  GPIO_ToggleOutputPin(GPIOC, GPIO_PIN_NO_13);
  /*configuring the SPI2 registers*/
  SPI_Handle SPIpin;
  SPIpin.pSPIx = SPI2;
  SPIpin.config.SPI_BusConfig = SPI_BUS_FD;
  SPIpin.config.SPI_ModeConfig = SPI_MODE_MASTER;
  SPIpin.config.SPI_SclkSpeed = SPI_ClckSPeed_DIV8;
  SPIpin.config.SPI_DFF = SPI_DFF_8;
  SPIpin.config.SPI_COPL = SPI_CPOL_LOW;
  SPIpin.config.SPI_CPHA = SPI_CPHA_LOW;
  SPIpin.config.SPI_SSM = SPI_SSM_DI;
  /*enabling the clock for SPI2*/
  SPI_CLKCNT(SPIpin.pSPIx, ENABLE);
  /*intializing the clock with the previous configurations*/
  SPI_Init(&SPIpin);

  /*enabling SSOE so NSS will pulled down when SPI is enabled*/
  SSOE_Enable(SPIpin.pSPIx, ENABLE);
  uint8_t data = 0x01; /*datat to be sent*/
  uint8_t Rdata; /*dummy data read while sending the datat*/

  /*enabling the SPI*/
  SPI_Enable(SPIpin.pSPIx, ENABLE);

  /*sending the data*/
  SPI_SendData(SPIpin.pSPIx, &data, sizeof(data));

  /*wait for BSY flag to sit since there is 2 ABP clocks between writing and the BSY flag bit to sit*/
  while(!(GetFlagStatus(SPIpin.pSPIx, SPI_TXE_FLAG)));
  while(GetFlagStatus(SPIpin.pSPIx, SPI_BSY_FLAG));

  /*read the dummy data sent by the slave*/
  SPI_ReceiveData(SPIpin.pSPIx, &Rdata, 1);

  /*waiting until busy flag is 0 and the bits are all transmitted*/
  while(GetFlagStatus(SPIpin.pSPIx, SPI_BSY_FLAG));

  /*desabling SPI after data transmittion is done*/
  SPI_Enable(SPIpin.pSPIx, DISABLE);
}
