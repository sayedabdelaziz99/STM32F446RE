/*
 * 007I2C_SysTickSendData.c
 *
 *  Created on: Feb 8, 2024
 *      Author: Sayed
 */
#include "GPIO_driver.h"
#include "RCC_driver.h"
#include "I2C_driver.h"
#include "bsp.h"
uint8_t state = 0;
int main(void){
	  uint8_t data = 0x15;
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
  systick_init();
	while(1){
		if(state == 1){
		  I2C_MasterSendData(&test, &data, sizeof(data), 0x1U);
		}
	}
}
void SysTick_Handler(){
state ^= 1U;
}
