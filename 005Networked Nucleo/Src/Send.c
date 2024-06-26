/*
 * main.c
 *
 *  Created on: Mar 14, 2024
 *      Author: Sayed
 */
#include "GPIO_driver.h"
#include "RCC_driver.h"
#include "bsp.h"
#include "string.h"
#include "Timer_Driver.h"
#include <stdio.h>

#define MAX_DISTANCE_TIME	11765U

uint32_t ID = 0x55U;
GPIO_Handle_t Echo, Trigg, LED;
BasicTimer_Handle_t TriggerTimer, EchoTimer;
uint16_t numEchoTicks;


static void CANTxconfig();
static void CANInit();
static void UltraSonicPinConfig();
static void TimerConfig();


int main(void){
	/*initializing the pins for CAN bus*/
	GPIO_CAN1Init(GPIOA, GPIO_PIN_NO_11, 9);//RX
	GPIO_CAN1Init(GPIOA, GPIO_PIN_NO_12, 9);//TX
	/*initializing the CAN bus*/
	CANInit();
	CANTxconfig();

	/*initialize ultraSonic Pins*/
	UltraSonicPinConfig();
	/*configure the timers*/
	TimerConfig();
	/*initialize the Timers*/
	BasicTimerInit(&TriggerTimer);
	BasicTimerInit(&EchoTimer);

	/*initializing interrupts for TriggerTimer, EchoTimer and Echo pin*/
	GPIO_IRQInterruptConfig(IRQ_TIM6_DAC, ENABLE);
	GPIO_IRQInterruptConfig(IRQ_TIM7, ENABLE);
	GPIO_IRQInterruptConfig(IRQ_EXTI5_9, ENABLE);

	/*setting the priority for the ISRs*/
	GPIO_IRQPriorityConfig(IRQ_TIM6_DAC, 1);
	GPIO_IRQPriorityConfig(IRQ_TIM7, 2);
	GPIO_IRQPriorityConfig(IRQ_EXTI5_9, 3);
	//enter normal mode
	CAN1 ->MCR &= ~(1 << 0);
	//wait until CAN is in normal mode
	while(CAN1 ->MSR & (1 << 0));

	while(1){
		delay(10U);
		TimerStart(TriggerTimer.pTIMx, ENABLE);
		GPIO_ToggleOutputPin(Trigg.pGPIOx, Trigg.GPIO_PinConfig.GPIO_PinNumber);
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
	//configure the timings
	 /* pre-scaler = 1
	 * number of time quanta = 16
	 * segment 1 = 13
	 * segment 2 = 2
	 * SJW = 1
	 */
	CAN1 ->BTR &= 0x00000000U;
	CAN1 ->BTR |= (1U << 24);//SWj
	CAN1 ->BTR |= (13U << 16);//seg1
	CAN1 ->BTR |= (2U << 20);//seg2
	CAN1 ->BTR |= (2U << 0);//BRP
}


static void UltraSonicPinConfig(){
	/*configure the echo pin*/
	Echo.pGPIOx = GPIOA;
	Echo.GPIO_PinConfig.GPIO_PinNumber =  GPIO_PIN_NO_8;
	Echo.GPIO_PinConfig.GPIO_PinMode   =  GPIO_MODE_IT_RFT;
	Echo.GPIO_PinConfig.GPIO_PinSpeed  =  GPIO_SPEED_FAST;
	Echo.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	Echo.GPIO_PinConfig.GPIO_PinPuPdControl  = GPIO_NO_PUPD;

	/*configure the Trigg Pin*/
	Trigg.pGPIOx = GPIOA;
	Trigg.GPIO_PinConfig.GPIO_PinNumber =  GPIO_PIN_NO_9;
	Trigg.GPIO_PinConfig.GPIO_PinMode   =  GPIO_MODE_OUT;
	Trigg.GPIO_PinConfig.GPIO_PinSpeed  =  GPIO_SPEED_FAST;
	Trigg.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	Trigg.GPIO_PinConfig.GPIO_PinPuPdControl  = GPIO_NO_PUPD;
	GPIO_CLKCNT(GPIOA,ENABLE);
	GPIO_Init(&Echo);
	GPIO_Init(&Trigg);
}


static void TimerConfig(){
	/*configure timer1*/
	TriggerTimer.pTIMx = TIM6;
	TriggerTimer.config.InterruptEnorDi = ENABLE;
	TriggerTimer.config.PreScalerVal = 15U;
	TriggerTimer.config.AutoReloadVal = 10U;

	/*configure timer2*/
	EchoTimer.pTIMx = TIM7;
	EchoTimer.config.AutoReloadVal = MAX_DISTANCE_TIME;
	EchoTimer.config.PreScalerVal  = 15U;
}

static void CANTxconfig(){
	//configure the mailbox
	CAN1 ->sTxMailBox[0].TIR &= 0x00000000U;
	CAN1 ->sTxMailBox[0].TIR |= (ID << 21);//ID
	CAN1 ->sTxMailBox[0].TIR &= ~(1U << 1);//RTR
	CAN1 ->sTxMailBox[0].TIR &= ~(1U << 2);//IDE
	CAN1 ->sTxMailBox[0].TDTR &= 0x00000000U;
	CAN1 ->sTxMailBox[0].TDLR &= 0x00000000U;
	CAN1 ->sTxMailBox[0].TDHR &= 0x00000000U;
}

void TIM6_DAC_IRQHandler(){
	TimerStart(TriggerTimer.pTIMx, DISABLE);
	TriggerTimer.pTIMx->SR &= ~(1 << TIM_SR_UIF);//clearing OverFlow interrupt
	GPIO_ToggleOutputPin(Trigg.pGPIOx, Trigg.GPIO_PinConfig.GPIO_PinNumber);
}

void EXTI9_5_IRQHandler(){
	EXTI->PR |= (1 << Echo.GPIO_PinConfig.GPIO_PinNumber);
	if(GPIO_ReadFromInputPin(Echo.pGPIOx, Echo.GPIO_PinConfig.GPIO_PinNumber) == 1U){
		TimerStart(EchoTimer.pTIMx, ENABLE);
	}else{
		numEchoTicks = EchoTimer.pTIMx->CNT;
		TimerStart(EchoTimer.pTIMx, DISABLE);
		EchoTimer.pTIMx->SR &= ~(1 << TIM_SR_UIF);
		EchoTimer.pTIMx->CNT = 0U;
		CAN1 ->sTxMailBox[0].TDLR = 0x0U;
		CAN1 ->sTxMailBox[0].TDHR = 0x0U;
		for(uint32_t i = 0; i < sizeof(numEchoTicks); i++){
			uint8_t tmp = (numEchoTicks >> (i * 8)) & 0xFFU;
			if(i < 4){
				CAN1 ->sTxMailBox[0].TDLR |= tmp << (i * 8);
			}else{
				CAN1 ->sTxMailBox[0].TDHR |= tmp << ((i - 4) * 8);
			}
		}
		CAN1 ->sTxMailBox[0].TDTR |= (sizeof(numEchoTicks) << 0);//data size
		//request to send
		CAN1 ->sTxMailBox[0].TIR |= (1 << 0);
	}
}
