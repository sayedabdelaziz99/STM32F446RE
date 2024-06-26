#include "GPIO_driver.h"
#include "I2C_driver.h"
#include "RTC_driver.h"
#include "USART_driver.h"
#include "bsp.h"
#include <stdio.h>
#include <string.h>

static void UARTConfig();
void I2C_Config(I2C_Handle *pI2CHandle);
static void shift(uint8_t *pData);

USART_Handle_t hUART;
int main(void){

	I2C_Handle RTC;
	I2C_Config(&RTC);
	UARTConfig();
	//initializing UART2 Pins
	USART_GPIOInit(GPIOA,GPIO_PIN_NO_2,7);  /*TX*/
	USART_GPIOInit(GPIOA,GPIO_PIN_NO_3,7);  /*RX*/
	//RTC_SetTime(&RTC);
	uint8_t data[7];
	char buffer[28];
	while(1){
		delay(50);
		RTC_ReadTime(data, &RTC);
		shift(data);
		sprintf(buffer, "Time is %d :%d :%d O'Clock\r\n",data[2],data[1],data[0]);
		USART_SendData(&hUART, (uint8_t *)buffer, sizeof(buffer));
	}
}

static void shift(uint8_t *pData){
	for(uint8_t i = 0; i < 7; i++){
		uint8_t MSB = pData[i] >> 4;
		uint8_t LSB = pData[i] & 0xF;
		pData[i] = MSB * 10 + LSB;
	}
}

void I2C_Config(I2C_Handle *pI2CHandle){
	I2C1_GPIOInit(GPIOB, GPIO_PIN_NO_6, 4);
	I2C1_GPIOInit(GPIOB, GPIO_PIN_NO_7, 4);

	pI2CHandle->pI2Cx = I2C1;
	pI2CHandle->I2C_Config.I2C_SCLSpeed = I2C_SCL_SM;
	pI2CHandle->I2C_Config.I2C_DeviceAddress = 0x68U;
	pI2CHandle->I2C_Config.I2C_ACKControl = I2C_ACK_ENABLE;
	pI2CHandle->I2C_Config.I2C_AddressMode = I2C_AddressMode_7bit;
	I2C_CLKCNT(pI2CHandle->pI2Cx, ENABLE);
	I2C_Init(pI2CHandle);
}

static void UARTConfig(){
	hUART.pUSARTx = USART2;
	hUART.USART_Config.USART_Baud = USART_STD_BAUD_115200;
	hUART.USART_Config.USART_NoOfStopBits = USART_STOPBITS_1;
	hUART.USART_Config.USART_ParityControl = USART_PARITY_DISABLE;
	hUART.USART_Config.USART_Mode = USART_MODE_TXRX;
	hUART.USART_Config.USART_WordLength = USART_WORDLEN_8BITS;
	USART_Init(&hUART);
}

