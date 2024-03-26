/*
 * 008USART_MasterSendData.c
 *
 *  Created on: Feb 11, 2024
 *      Author: Sayed
 */

#include "GPIO_driver.h"
#include "RCC_driver.h"
#include "bsp.h"
#include "USART_driver.h"

uint8_t data[] =  "Hello From USART1";
uint8_t data_size = sizeof(data);
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

	  /*configuring the switch*/
	  SYSCFG_CLKEN;
	  GPIO_Handle_t SW;
	  SW.pGPIOx = GPIOC;
	  SW.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_13;
	  SW.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IT_RT;
	  SW.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	  GPIO_Init(&SW);

	  GPIO_IRQInterruptConfig(EXTI10_15, ENABLE);
	  GPIO_IRQPriorityConfig(EXTI10_15, 1);

	while(1){
	}
}

void EXTI15_10_IRQHandler(void){
	__asm(/*creating critical section to eliminate the race condition*/
	  "CPSID  I \n"  /*disabling the interrupt*/
	);
	if(EXTI ->PR & (1 << GPIO_PIN_NO_13)){ /*if the interrupt is triggered by the required pin*/
		USART_SendData(&test, &data_size, sizeof(data_size));  /*sending the size of the data in the first byte*/
		USART_SendData(&test, data, data_size);  /*sending the data*/
		EXTI ->PR |= (1 << GPIO_PIN_NO_13); /*clear the pending bit in EXTI*/
	}
	__asm(
	  "CPSIE  I \n"  /*enabling the interrupt*/
	);
}

