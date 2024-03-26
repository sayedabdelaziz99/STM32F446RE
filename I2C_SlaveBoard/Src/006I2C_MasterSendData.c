/*
 * 006I2C_MasterSendData.c
 *
 *  Created on: Feb 5, 2024
 *      Author: Sayed
 */
#include "GPIO_driver.h"
#include "RCC_driver.h"
#include "I2C_driver.h"
#include "bsp.h"

int main(void){
  uint8_t data = 0x1;

  I2C_Handle test;
  test.pI2Cx = I2C1;
  test.I2C_Config.I2C_SCLSpeed = I2C_SCL_SM;
  test.I2C_Config.I2C_DeviceAddress = 0x68U;
  test.I2C_Config.I2C_ACKControl = I2C_ACK_ENABLE;
  test.I2C_Config.I2C_AddressMode = I2C_AddressMode_7bit;
  I2C_CLKCNT(test.pI2Cx, ENABLE);
  I2C_Init(&test);
/*configuring the pins first*/
    I2C1_GPIOInit(GPIOB, GPIO_PIN_NO_6, 4);  /*scl*/
    I2C1_GPIOInit(GPIOB, GPIO_PIN_NO_7, 4);  /*sda*/
/*configuring the switch*/
  GPIO_Handle_t SW;
  SW.pGPIOx = GPIOC;
  SW.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_13;
  SW.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IN;
  SW.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
  GPIO_CLKCNT(GPIOC,ENABLE);
  GPIO_Init(&SW);


	while(1){
		while(GPIO_ReadFromInputPin(SW.pGPIOx, GPIO_PIN_NO_13));
		/*send the data*/
		I2C_MasterSendData(&test, &data, sizeof(data), 0x65U);
	}
}
