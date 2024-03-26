/*
 * 008USART_MasterSendData.c
 *
 *  Created on: Feb 11, 2024
 *      Author: Sayed
 */

#include "GPIO_driver.h"
#include "RCC_driver.h"
#include "bsp.h"
#include "UART_driver.h"

uint8_t data[] =  "Hello\n";
USART_Handle_t test;

int main(void){
	test.pUSARTx = USART1;
	test.USART_Config.USART_Baud = USART_STD_BAUD_115200;
	test.USART_Config.USART_NoOfStopBits = USART_STOPBITS_1;
	test.USART_Config.USART_ParityControl = USART_PARITY_DISABLE;
	test.USART_Config.USART_Mode = USART_MODE_TXRX;
	test.USART_Config.USART_WordLength = USART_WORDLEN_8BITS;
	USART_Init(&test);

	USART_GPIOInit(GPIOA,GPIO_PIN_NO_9,7);  /*TX*/
	USART_GPIOInit(GPIOA,GPIO_PIN_NO_10,7);  /*RX*/


	GPIO_ButtonInit(GPIOC , GPIO_PIN_NO_13);

	systick_init();

	while(1){
	}
}
void SysTick_Handler(void){
	USART_SendData(&test, data, sizeof(data));
}
