/*
 * receive.c
 *
 *  Created on: Mar 20, 2024
 *      Author: Sayed
 */

#include "GPIO_driver.h"
#include "RCC_driver.h"
#include "USART_driver.h"
#include "I2C_driver.h"
#include "bsp.h"
#include "string.h"
#include "RTC_driver.h"
#include "Timer_Driver.h"
#include <stdio.h>
#include <stdlib.h>
//extern void initialise_monitor_handles(void);

#define TICKS_ATMAX_DISTANCE		3226U

static void CANInit();
static void CANRxconfig();
static void ReadFIFO();
static void UARTConfig();
static void shift(uint8_t *pData);
static void I2C_Config(I2C_Handle *pI2CHandle);

uint32_t numTicks;
const float speedOfSound = 343/2;
float distance;
char uartBuf[100];

USART_Handle_t hUART;
uint32_t data[8];

int main(void){
	//enable floating point full access
	SCB ->CPACR |= ((3UL << 20U)|(3UL << 22U));

	GPIO_CAN1Init(GPIOA, GPIO_PIN_NO_11, 9);//RX
	GPIO_CAN1Init(GPIOA, GPIO_PIN_NO_12, 9);//TX
	GPIO_LEDInit();
	CANInit();
	CANRxconfig();
	systick_init(1U);
	//enter normal mode
	CAN1 ->MCR &= ~(1 << 0);
	//wait until CAN is in normal mode
	while(CAN1 ->MSR & (1 << 0));

	//configuring the UART peripheral
	UARTConfig();
	//initializing UART2 Pins
	USART_GPIOInit(GPIOA,GPIO_PIN_NO_2,7);  /*TX*/
	USART_GPIOInit(GPIOA,GPIO_PIN_NO_3,7);  /*RX*/

	//configure I2C
	I2C_Handle RTC;
	I2C_Config(&RTC);
	RTC_SetTime(&RTC);
	uint8_t TimeBuffer[7];
	while(1){
	delay(50);
	RTC_ReadTime(TimeBuffer, &RTC);
	shift(TimeBuffer);
	distance = (numTicks/10000.0) * speedOfSound;
	sprintf(uartBuf, "Distance = %.1f(cm) at %d:%d:%d O'Clock\r\n", distance,TimeBuffer[2],TimeBuffer[1],TimeBuffer[0]);
	USART_SendData(&hUART, (uint8_t *)uartBuf, sizeof(uartBuf));  /*sending the data*/
	}
}




static void CANInit(){
	//enable the clock for the bus
	RCC ->APB1ENR |= (1 << RCC_APB1ENR_CAN1EN);
	//clear sleep bit in MCR
	CAN1 ->MCR &= ~(1U << 1);
	//initialize the CAN bus
	CAN1 ->MCR |= (1 << 0);
	//wait until CAN enters initialization mode
	while(! (CAN1 ->MSR & (1 << 0)));
	CAN1 ->BTR &= 0x00000000U;
	CAN1 ->BTR |= (1U << 24);//SWj
	CAN1 ->BTR |= (13U << 16);//seg1
	CAN1 ->BTR |= (2U << 20);//seg2
	CAN1 ->BTR |= (2U << 0);//BRP
}

static void CANRxconfig(){
	//configure the filter banks to accept all IDs
	//initialize the filter bank
	CAN1 ->FMR |= (1U << 0);
	//enable interrupt for pending messages on FIFO 0
	CAN1 ->IER |= (1U << 1);
	//enable NVIC interrupt for CAN RX (IRQ no. 20) ISER0;
	*ISER0 |= (1U << 20);
	//set it to MASK MODE
	CAN1 ->FM1R &= ~(1 << 0);
	//use single 32bit register
	CAN1 ->FS1R |= (1 << 0);
	//assign the message to FIFO 0
	CAN1 ->FFA1R &= ~(1U << 0);
	//set the ID in the filter bank
	CAN1 ->sFilterRegister[0].FR1 = 0x55U << 5;
	//set the MASK
	CAN1 ->sFilterRegister[0].FR2 = 0x7FFU << 5;
	//activate the filter
	CAN1 ->FMR &= ~(1U << 0);
	CAN1 ->FA1R |= (1U << 0);
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

static void shift(uint8_t *pData){
	for(uint8_t i = 0; i < 7; i++){
		uint8_t MSB = pData[i] >> 4;
		uint8_t LSB = pData[i] & 0xF;
		pData[i] = MSB * 10 + LSB;
	}
}

static void I2C_Config(I2C_Handle *pI2CHandle){
	I2C1_GPIOInit(GPIOB, GPIO_PIN_NO_6, 4);//SCL
	I2C1_GPIOInit(GPIOB, GPIO_PIN_NO_7, 4);//SDA

	pI2CHandle->pI2Cx = I2C1;
	pI2CHandle->I2C_Config.I2C_SCLSpeed = I2C_SCL_SM;
	pI2CHandle->I2C_Config.I2C_DeviceAddress = 0x68U;
	pI2CHandle->I2C_Config.I2C_ACKControl = I2C_ACK_ENABLE;
	pI2CHandle->I2C_Config.I2C_AddressMode = I2C_AddressMode_7bit;
	I2C_CLKCNT(pI2CHandle->pI2Cx, ENABLE);
	I2C_Init(pI2CHandle);
}

void CAN1_RX0_IRQHandler(void){
	__asm(
			"CPSID I  \n"
	);
	*ICPR0 |= (1U << 20);
	ReadFIFO();
	uint32_t Ticks = data[0] | (data[1] << 8);
	SysTick ->RVR = Ticks * TICKS_ATMAX_DISTANCE;
	__asm(
			"CPSIE I  \n"
	);
}

static void ReadFIFO(){
	uint32_t dataLength = (CAN1->sFIFOMailBox[0].RDTR & 0xF);
	for(uint8_t i = 0; i < dataLength; i++){
		if(i < 4){
			data[i] = (CAN1 ->sFIFOMailBox[0].RDLR >> (i * 8)) & 0xFFU;
		}else{
			data[i] = (CAN1 ->sFIFOMailBox[0].RDHR >> ((i - 4) * 8)) & 0xFFU;
		}
	}
	numTicks = data[0] | (data[1] << 8);
	//release the FIFO
	CAN1 ->RF0R |= (1U << 5);
}

void SysTick_Handler(){
	__asm(
			"CPSID I  \n"
	);
	if(distance < 70){
		GPIO_ToggleOutputPin(GPIOA, GPIO_PIN_NO_5);
	}else{
		GPIO_WriteToOutputPin(GPIOA, GPIO_PIN_NO_5, 0);
	}
	__asm(
			"CPSIE I  \n"
	);
}
