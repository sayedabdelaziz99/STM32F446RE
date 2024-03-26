/*
 * Slave_ReceiveData.c
 *
 *  Created on: Feb 7, 2024
 *      Author: Sayed
 */

#include "GPIO_driver.h"
#include "I2C_driver.h"
#include "RCC_driver.h"
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
  GPIO_CLKCNT(GPIOA,ENABLE);
  GPIO_Init(&GPIOLed);

  uint8_t data[3];
  I2C_Handle test;
  test.pI2Cx = I2C1;
  test.I2C_Config.I2C_SCLSpeed = I2C_SCL_SM;
  test.I2C_Config.I2C_DeviceAddress = 0x61U;
  test.I2C_Config.I2C_ACKControl = I2C_ACK_ENABLE;
  test.I2C_Config.I2C_AddressMode = I2C_AddressMode_7bit;
  I2C_CLKCNT(test.pI2Cx, ENABLE);
  I2C_Init(&test);
  /*configuring the pins first*/
  I2C1_GPIOInit(GPIOB, GPIO_PIN_NO_6, 4);  /*scl*/
  I2C1_GPIOInit(GPIOB, GPIO_PIN_NO_7, 4);  /*sda*/
  while(1){
    I2C_SlaveRecieveData(&test);
  }
}
