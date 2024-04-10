/*
 * firmware.c
 *
 *  Created on: Apr 7, 2024
 *      Author: Sayed
 */

#include "USART_driver.h"
#include "RCC_driver.h"
#include "bsp.h"

static void USART_setup(USART_Handle_t *pUSARTHandle);

#define RingBufferSize   100
#define BOOTLOADER_SIZE  (0x8000)
#define SCB_VTOR		((uint32_t *)0xE000ED08U)


char data[] = "Hello\r\n";

typedef struct RingBuff{
	uint8_t buffer[RingBufferSize];
	uint8_t read_index;
	uint8_t write_index;
}RingBuff;

RingBuff Ring;
USART_Handle_t USART;
GPIO_Handle_t Button;

int main(void){
	*SCB_VTOR = FLASH_BASEADRR | BOOTLOADER_SIZE ; //offset vector table

	Button.pGPIOx = GPIOC;
	GPIO_ButtonInitIT(Button.pGPIOx, GPIO_PIN_NO_13);

	USART_GPIOInit(GPIOA, GPIO_PIN_NO_2, 7); //TX
	USART_GPIOInit(GPIOA, GPIO_PIN_NO_3, 7); //RX

	USART.pUSARTx = USART2;
	USART_setup(&USART);

	Ring.read_index = 0;
	Ring.write_index = 0;
	while(1){
		/*delay(50);
		*USART_SendData(&USART, (uint8_t *)data, sizeof(data));
		*/
	}
}



static void USART_setup(USART_Handle_t *pUSARTHandle){
	pUSARTHandle->USART_Config.USART_Baud =  USART_STD_BAUD_115200;
	pUSARTHandle->USART_Config.USART_Mode =  USART_MODE_TXRX;
	pUSARTHandle->USART_Config.USART_NoOfStopBits = USART_STOPBITS_1;
	pUSARTHandle->USART_Config.USART_ParityControl = USART_PARITY_DISABLE;
	pUSARTHandle->USART_Config.USART_WordLength = USART_WORDLEN_8BITS;
	USART_PeriClockControl(pUSARTHandle->pUSARTx, ENABLE);
	USART_Init(pUSARTHandle);
	*ISER1 |= (1 << (IRQ_USART2 % 32));//enable USART2 NVIC line
	pUSARTHandle->pUSARTx->CR1 |= (1U << USART_CR1_RXNEIE);//enable RXNE interrupt
}


void EXTI15_10_IRQHandler(void){
	if(! GPIO_ReadFromInputPin(Button.pGPIOx, Button.GPIO_PinConfig.GPIO_PinNumber)){
		EXTI ->PR |= (1 << Button.GPIO_PinConfig.GPIO_PinNumber); /*clear the pending bit in EXTI*/
		if(Ring.write_index == Ring.read_index){
			;
		}else{
			USART_SendData(&USART, (uint8_t *)(&Ring.buffer[Ring.read_index]), 1);
			Ring.read_index = (Ring.read_index + 1) & 0x7FU;
		}
	}
}

void USART2_IRQHandler(void){
	//if(Ring.write_index == Ring.read_index && (Ring.write_index != 0)){
		//;
	//}else{
		Ring.buffer[Ring.write_index] = (uint8_t)USART.pUSARTx->DR;
		Ring.write_index = (1 + Ring.write_index)& 0x7FU;
	//}
}

