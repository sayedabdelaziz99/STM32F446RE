/*
 * GPIO_driver.c
 *
 *  Created on: Jan 23, 2024
 *      Author: Sayed
 */
#include "GPIO_Driver.h"
/*********************************************************************
 * @fn      		  - GPIO_CLKCNT
 *
 * @brief             - This function enables or disables peripheral clock for the given GPIO port
 *
 * @param[in]         - base address of the gpio peripheral
 * @param[in]         - ENABLE or DISABLE macros
 * @param[in]         -
 *
 * @return            -  none
 *
 * @Note              -  none

 */
void GPIO_CLKCNT(GPIO_RegDef_t *pGPIOx, uint8_t EnorDi)
{
	if(EnorDi == ENABLE)
	{
	  if(pGPIOx == GPIOA){GPIOA_CLKEN;}
	  else if (pGPIOx == GPIOB){GPIOB_CLKEN;}
	  else if (pGPIOx == GPIOC){GPIOC_CLKEN;}
	  else if (pGPIOx == GPIOD){GPIOD_CLKEN;}
	  else if (pGPIOx == GPIOE){GPIOE_CLKEN;}
	  else if (pGPIOx == GPIOF){GPIOF_CLKEN;}
	  else if (pGPIOx == GPIOG){GPIOG_CLKEN;}
	  else if (pGPIOx == GPIOH){GPIOH_CLKEN;}
	}
	else
	{
	  if(pGPIOx == GPIOA){GPIOA_CLKDI;}
	  else if (pGPIOx == GPIOB){GPIOB_CLKDI;}
	  else if (pGPIOx == GPIOC){GPIOC_CLKDI;}
	  else if (pGPIOx == GPIOD){GPIOD_CLKDI;}
	  else if (pGPIOx == GPIOE){GPIOE_CLKDI;}
	  else if (pGPIOx == GPIOF){GPIOF_CLKDI;}
	  else if (pGPIOx == GPIOG){GPIOG_CLKDI;}
	  else if (pGPIOx == GPIOH){GPIOH_CLKDI;}
	}
}


/*********************************************************************
 * @fn      		  - GPIO_PORTCODE
 *
 * @brief             -converts the port number to it's equivilent code to configure the EXTI line
 *
 * @param[in]         - pointer to the PORT
 *
 * @return            - the code of the given port
 *
 * @Note              -

 */
static uint8_t GPIO_PORTCODE(GPIO_RegDef_t *pGPIOx){
	uint8_t volatile portcode;
	uint32_t offset = (uint32_t)((uint32_t)pGPIOx - GPIOA_BASEADDR); /*calculate the offset from the base address*/
	portcode = offset / 0x400;   /*portcode will range from 0 to 8 since the offset is a multiply of 400*/
	return portcode;
}

/*********************************************************************
 * @fn      		  - GPIO_Init
 *
 * @brief             -intializes the given port
 *
 * @param[in]         -pointer to the GPIO Handle variable which contains port address and the configurations required
 *
 * @return            -
 *
 * @Note              -

 */
void GPIO_Init(GPIO_Handle_t *pGPIOHandle)
{
	 uint32_t temp=0; //temp. register
	//1 . configure the mode of gpio pin

	if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode <= GPIO_MODE_ANALOG)
	{
		//the non interrupt mode
		temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber ) );
		pGPIOHandle->pGPIOx->MODER &= ~( 0x3 << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber)); //clearing
		pGPIOHandle->pGPIOx->MODER |= temp; //setting

	}else
	{
		if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_FT){
			/*configure the falling edge trigger register*/
			pGPIOHandle->pGPIOx->MODER &= ~( 0x0 << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
			EXTI ->RTSR &= ~(1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
			EXTI ->FTSR |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
		}else if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_RT){
			/*configure the rising edge trigger register*/
			pGPIOHandle->pGPIOx->MODER &= ~( 0x0 << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
			EXTI ->FTSR &= ~(1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
			EXTI ->RTSR |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
		}
		else{
			/*configure the falling and rising edge trigger registers*/
			pGPIOHandle->pGPIOx->MODER &= ~( 0x0 << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
			EXTI ->FTSR |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
			EXTI ->RTSR |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
		}

		/*configure the gpio port selection(SYSCONFIG_EXTI register)*/
		uint8_t tmp1 = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber / 4;  /*which EXTICR to configure*/
		uint8_t tmp2 = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber % 4;  /*which Field of the EXTICR to configure*/
		uint8_t portcode = GPIO_PORTCODE(pGPIOHandle->pGPIOx);          /*the code that represents the port whoes pin is goning to trigger the interrupt*/
		SYSCFG->EXTICR[tmp1] = (portcode << tmp2 * 4);                  /*every field is four bits wide so  we multiply by 4*/
		/*configure the exti interrupt delivery(interrupt mask register)*/
		EXTI ->IMR |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
	}

	//2. configure the speed
	temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinSpeed << ( 2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber) );
	pGPIOHandle->pGPIOx->OSPEEDER &= ~( 0x3 << ( 2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber)); //clearing
	pGPIOHandle->pGPIOx->OSPEEDER |= temp;

	//3. configure the pupd settings
	temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinPuPdControl << ( 2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber) );
	pGPIOHandle->pGPIOx->PUPDR &= ~( 0x3 << ( 2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber)); //clearing
	pGPIOHandle->pGPIOx->PUPDR |= temp;


	//4. configure the optype
	temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinOPType << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber );
	pGPIOHandle->pGPIOx->OTYPER &= ~( 0x1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber); //clearing
	pGPIOHandle->pGPIOx->OTYPER |= temp;

	//5. configure the alt functionality
	if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_ALTFN)
	{
		//configure the alt function registers.
		uint8_t temp1, temp2;
		temp1 = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber / 8;
		temp2 = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber  % 8;
		pGPIOHandle->pGPIOx->AFR[temp1] &= ~(0xF << ( 4 * temp2 ) ); //clearing
		pGPIOHandle->pGPIOx->AFR[temp1] |= (pGPIOHandle->GPIO_PinConfig.GPIO_PinAltFunMode << ( 4 * temp2 ) );
	}

}


/*********************************************************************
 * @fn      		  - GPIO_DeInit
 *
 * @brief             -stops the clock for a given port
 *
 * @param[in]         -pointer to the port need to be disabled
 * @param[in]         -
 * @param[in]         -
 *
 * @return            -
 *
 * @Note              -

 */
void GPIO_DeInit(GPIO_RegDef_t *pGPIOx)
{
	if(pGPIOx == GPIOA){GPIOA_RESET;}
	else if (pGPIOx == GPIOB){GPIOB_RESET;}
	else if (pGPIOx == GPIOC){GPIOC_RESET;}
	else if (pGPIOx == GPIOD){GPIOD_RESET;}
	else if (pGPIOx == GPIOE){GPIOE_RESET;}
	else if (pGPIOx == GPIOF){GPIOF_RESET;}
	else if (pGPIOx == GPIOG){GPIOG_RESET;}
	else if (pGPIOx == GPIOH){GPIOH_RESET;}
}



/*********************************************************************
 * @fn      		  - GPIO_ReadFromInputPin
 *
 * @brief             -reads the status of a given pin number at a given port
 *
 * @param[in]         -pointer to the port
 * @param[in]         -the pin number which to be read
 * @param[in]         -
 *
 * @return            -   0 or 1
 *
 * @Note              -

 */
uint8_t GPIO_ReadFromInputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber)
{
   uint8_t value;

   value = (uint8_t )((pGPIOx->IDR  >> PinNumber) & 0x00000001 ) ;

   return value;
}


/*********************************************************************
 * @fn      		  - GPIO_ReadFromInputPort
 *
 * @brief             -reads the value of the whole port
 *
 * @param[in]         -
 * @param[in]         -pointer to the port
 * @param[in]         -
 *
 * @return            -
 *
 * @Note              -

 */
inline uint16_t GPIO_ReadFromInputPort(GPIO_RegDef_t *pGPIOx)
{
	return ((uint16_t)pGPIOx->IDR);
}


/*********************************************************************
 * @fn      		  - GPIO_WriteToOutputPin
 *
 * @brief             -writes a value to a given pin of a given port
 *
 * @param[in]         -pointer to the port
 * @param[in]         -the pin number to be modefied
 * @param[in]         -the value to be written
 *
 * @return            -
 *
 * @Note              -

 */
void GPIO_WriteToOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber, uint8_t Value)
{

	if(Value == SET)
	{
		//write 1 to the output data register at the bit field corresponding to the pin number
		pGPIOx->ODR |= ( 1 << PinNumber);
	}else
	{
		//write 0
		pGPIOx->ODR &= ~( 1 << PinNumber);
	}
}


/*********************************************************************
 * @fn      		  - GPIO_WriteToOutputPort
 *
 * @brief             -writes a value to a given port
 *
 * @param[in]         -pointer to the port
 * @param[in]         -the value to be written
 * @param[in]         -
 *
 * @return            -
 *
 * @Note              -

 */
inline void GPIO_WriteToOutputPort(GPIO_RegDef_t *pGPIOx, uint16_t Value)
{
	pGPIOx->ODR  = Value;
}


/*********************************************************************
 * @fn      		  - GPIO_ToggleOutputPin
 *
 * @brief             -toggles a given pin
 *
 * @param[in]         -pointer to the port which has the pin in it
 * @param[in]         -the pin number to be toggled
 * @param[in]         -
 *
 * @return            -
 *
 * @Note              -

 */
inline void GPIO_ToggleOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber)
{
	pGPIOx->ODR  ^= ( 1 << PinNumber);
}



/*********************************************************************
 * @fn      		  - GPIO_IRQConfig
 *
 * @brief             -enables of disables a given irq number in the NVIC
 *
 * @param[in]         -the irq number
 * @param[in]         -enable or disable
 * @param[in]         -
 *
 * @return            -
 *
 * @Note              -

 */
void GPIO_IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnorDi)
{
if(EnorDi == ENABLE){
	if(IRQNumber <= 31){
		/*configure ISER0*/
		*ISER0 |= (1 << IRQNumber);
	}else if(IRQNumber >= 32 && IRQNumber < 64){
		/*configure ISER1*/
		*ISER1 |= (1 << (IRQNumber % 32));
	}else if(IRQNumber >= 64 && IRQNumber < 96){
		*ISER2 |= (1 << (IRQNumber % 64));
	}
}else{
	if(IRQNumber <= 31){
		/*configure ISER0*/
		*ICER0 |= (1 << IRQNumber);
	}else if(IRQNumber >= 32 && IRQNumber < 64){
		/*configure ISER1*/
		*ICER1 |= (1 << (IRQNumber % 32));
	}else if(IRQNumber >= 64 && IRQNumber < 96){
		*ICER2 |= (1 << (IRQNumber % 64));
	}
}
}



/*********************************************************************
 * @fn      		  - SPI_IRQPriorityConfig
 *
 * @brief             -changes the priorty of a given irq number
 *
 * @param[in]         -the irq number
 * @param[in]         -the priority of it
 * @param[in]         -
 *
 * @return            -
 *
 * @Note              -

 */
void GPIO_IRQPriorityConfig(uint8_t IRQNumber,uint32_t IRQPriority)
{
	uint8_t iprx = IRQNumber / 4;
	uint8_t iprx_section = IRQNumber % 4;
	uint8_t shift_ammount = (8 * iprx_section) + (8 - NO_PI_BITS_IMPLEMENTED);
	*(IPR_BASEADDR + (iprx * 4)) |= (IRQPriority << shift_ammount);
}
/*********************************************************************
 * @fn      		  - GPIO_IRQHandling
 *
 * @brief             -the ISR to be excuted when irq interrupt is presented
 *
 * @param[in]         -the pin number which will trigger the interrupt
 * @param[in]         -
 * @param[in]         -
 *
 * @return            -
 *
 * @Note              -

 */
void GPIO_IRQHandling(uint8_t PinNumber)
{

}

