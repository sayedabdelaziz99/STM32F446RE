/*
 * SPI_driver.c
 *
 *  Created on: Jan 29, 2024
 *      Author: Sayed
 */
#include "SPI_driver.h"
#include "GPIO_driver.h"

static void SPI_TXE_INTERRUPT_HANDLE(SPI_Handle *pSPIHandle);
static void SPI_RXNE_INTERRUPT_HANDLE(SPI_Handle *pSPIHandle);
static void SPI_ERR_INTERRUPT_HANDLE(SPI_Handle *pSPIHandle);
/*********************************************************************
 * @fn      		  - SPI_CLKCNT
 *
 * @brief             - This function enables or disables peripheral clock for the given SPI
 *
 * @param[in]         - base address of the SPI peripheral
 * @param[in]         - ENABLE or DISABLE macros
 * @param[in]         -
 *
 * @return            -  none
 *
 * @Note              -  none

 */
void SPI_CLKCNT(SPI_type *pSPIx, uint8_t EnorDi){
	if(EnorDi == ENABLE)
	{
	  if(pSPIx == SPI1){SPI1_CLKEN();}
	  else if (pSPIx == SPI2){SPI2_CLKEN();}
	  else if (pSPIx == SPI3){SPI3_CLKEN();}
	  else if (pSPIx == SPI4){SPI4_CLKEN();}
	}
	else
	{
	  if(pSPIx == SPI1){SPI1_CLKDI();}
	  else if (pSPIx == SPI2){SPI2_CLKDI();}
	  else if (pSPIx == SPI3){SPI3_CLKDI();}
	  else if (pSPIx == SPI4){SPI4_CLKDI();}
	}
}

/*
 * SPI initializing
 */
/*********************************************************************
 * @fn      		  - SPI_Init
 *
 * @brief             - this function intializes the specified SPI
 *
 * @param[in]         - pointer to the SPI Handle type
 * @param[in]         -
 * @param[in]         -
 *
 * @return            -  none
 *
 * @Note              -  none

 */
void SPI_Init(SPI_Handle *pSPIHandle){
uint32_t temp = 0;
             /*configure SPI_Mode*/
temp |= (pSPIHandle->config.SPI_ModeConfig << SPI_CR1_MSTR);

             /*configure SPI_Bus*/
if(pSPIHandle ->config.SPI_BusConfig == SPI_BUS_FD){ /*full duplex*/
/*clear the bi-directional bit*/
	temp &= ~(1 << SPI_CR1_BIDIMODE);
}
else if(pSPIHandle ->config.SPI_BusConfig == SPI_BUS_HD){/*full duplex*/
	/*set the bi-directional bit*/
	temp |= (1 << SPI_CR1_BIDIMODE);
}
else{ /*simplex mode*/
	/*clear the bi-directional bit*/
	temp &= ~(1 << SPI_CR1_BIDIMODE);
	/*set the receive only bit*/
	temp |= (1 << SPI_CR1_RXONLY);

}
             /*configure SPI Clock speed (baud rate)*/
temp |= (pSPIHandle ->config.SPI_SclkSpeed << SPI_CR1_BR);

	        /*configure SPI DFF (Data frame format)*/
temp |= (pSPIHandle ->config.SPI_DFF << SPI_CR1_DFF);

            /*configure SPI CPOL (polarity)*/
temp |= (pSPIHandle ->config.SPI_COPL << SPI_CR1_CPOL);

            /*configure SPI CPHA (phase)*/
temp |= (pSPIHandle ->config.SPI_CPHA << SPI_CR1_CPHA);

             /*configure SPI SSM (Software slave management)*/
temp |= (pSPIHandle ->config.SPI_SSM << SPI_CR1_SSM);
            /*pass the configurations to the CR1 register*/
pSPIHandle ->pSPIx->CR1 = temp;
}

/*
 * SPI disabling
 */
/*********************************************************************
 * @fn      		  - SPI_DeInit
 *
 * @brief             - this function stop the clock for a given SPI
 *
 * @param[in]         - base address of the SPI peripheral
 * @param[in]         -
 * @param[in]         -
 *
 * @return            -  none
 *
 * @Note              -  none

 */
void SPI_DeInit(SPI_type *pSPIx){
	if(pSPIx == SPI1){SPI1_CLKDI();}
	else if(pSPIx == SPI2){SPI2_CLKDI();}
	else if(pSPIx == SPI3){SPI3_CLKDI();}
	else{SPI4_CLKDI();}
}

/*
 * SPI data send and receive
 */
/*********************************************************************
 * @fn      		  - SPI_SendData
 *
 * @brief             - this function sends the data over the SPI BUS
 *
 * @param[in]         - base address of the SPI peripheral
 * @param[in]         - a ponter to the TXBuffer (transsmit)
 * @param[in]         -the Length of the datat to be sent
 *
 * @return            -  none
 *
 * @Note              -  this is a blocking method

 */
uint8_t GetFlagStatus(SPI_type *pSPIx ,uint8_t FlagName){
	if(pSPIx->SR & FlagName){
		return SET;
	}
	return RESET;
}
void SPI_SendData(SPI_type *pSPIx, uint8_t *pTXBuffer, uint32_t Len){
	while(Len > 0){
		/*wait until the TX is not embty*/
		while(GetFlagStatus(pSPIx, SPI_TXE_FLAG) == RESET);
		/*check DFF (frame format)*/
		if((pSPIx ->CR1 & (1 << SPI_CR1_DFF))){ /*16bit format*/
			pSPIx ->DR = *((uint16_t *)pTXBuffer);
			Len -=2;
			(uint16_t *)pTXBuffer++;
		}
		else{ /*8bit format*/
			pSPIx ->DR = *pTXBuffer;
			Len --;
			pTXBuffer++;
		}
	}
	/*wait for TXE flag to be sit*/
	while(GetFlagStatus(pSPIx, SPI_TXE_FLAG) == RESET);
	/*wait for BSY flag to reset*/
	while(GetFlagStatus(pSPIx, SPI_BSY_FLAG) == SET);
	/*reading DR and SR to clear the over run flag*/
	uint8_t temp = pSPIx ->DR;
	temp = pSPIx ->SR;
	temp++;
}

uint8_t SPI_SendDataIT(SPI_Handle *pSPIHandle, uint8_t *pTXBuffer, uint32_t Len){
	uint8_t state = pSPIHandle->TxState;
	if(state != SPI_BUSY_IN_TX){
	/*save the Buffer address*/
	pSPIHandle->pTxBuffer = pTXBuffer;
	/*save the length information*/
	pSPIHandle->TxLen = Len;
	/*mark the state as BUST in Transmission*/
	pSPIHandle->TxState = SPI_BUSY_IN_TX;
	/*Enable TXE interrupt*/
	pSPIHandle->pSPIx->CR2 |= (1 << SPI_CR2_TXEIE);
	}

	return state;
}

/*********************************************************************
 * @fn      		  - SPI_ReceiveData
 *
 * @brief             - this function Receives the data sent to the SPI peripheral
 *
 * @param[in]         - base address of the SPI peripheral
 * @param[in]         - a ponter to the RXBuffer (Receive)
 * @param[in]         -the Length of the datat to be sent
 *
 * @return            -  none
 *
 * @Note              -  none

 */
void SPI_ReceiveData(SPI_type *pSPIx, uint8_t *pRXBuffer, uint32_t Len){
	while(Len > 0){
		/*wait for busy bit*/
		while(GetFlagStatus(pSPIx, SPI_BSY_FLAG) == SET);
		/*write some dummy data*/
		//pSPIx ->DR = 0x15;
		/*wait until the RX is not embty*/
		while(GetFlagStatus(pSPIx, SPI_RXNE_FLAG) == RESET);
		/*check DFF (frame format)*/
		if((pSPIx ->CR1 & (1 << SPI_CR1_DFF))){ /*16bit format*/
			*((uint16_t *)pRXBuffer) = pSPIx ->DR;
			Len -=2;
			(uint16_t *)pRXBuffer++;
		}
		else{ /*8bit format*/
			*pRXBuffer = pSPIx ->DR;
			Len --;
			pRXBuffer++;
		}
	}
}

uint8_t SPI_ReceiveDataIT(SPI_Handle *pSPIHandle, uint8_t *pRXBuffer, uint32_t Len){
	uint8_t state = pSPIHandle->RxState;
	if(state != SPI_BUSY_IN_RX){
	/*save the Buffer address*/
	pSPIHandle->pTxBuffer = pRXBuffer;
	/*save the length information*/
	pSPIHandle->RxLen = Len;
	/*mark the state as BUST in Transmission*/
	pSPIHandle->RxState = SPI_BUSY_IN_RX;
	/*Enable TXE interrupt*/
	pSPIHandle->pSPIx->CR2 |= (1 << SPI_CR2_RXNEIE);
	}

	return state;
}

/*
 * IRQ and ISR configuration
 */
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
void SPI_IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnorDi)
{
	if(EnorDi == ENABLE){
		if(IRQNumber >= 32 && IRQNumber < 64){
			/*configure ISER1*/
			*ISER1 |= (1 << (IRQNumber % 32));
		}else if(IRQNumber >= 64 && IRQNumber < 96){
			*ISER2 |= (1 << (IRQNumber % 64));
		}
	}else{
		if(IRQNumber >= 32 && IRQNumber < 64){
			/*configure ISER1*/
			*ICER1 |= (1 << (IRQNumber % 32));
		}else if(IRQNumber >= 64 && IRQNumber < 96){
			*ICER2 |= (1 << (IRQNumber % 64));
		}
	}
}

void SPI_IRQPriorityConfig(uint8_t IRQNumber, uint32_t IRQPriority){

}

void SPI_IRQHandling(SPI_Handle *pSPIHandle){

	uint8_t tmp1 = pSPIHandle->pSPIx->SR & (1 << SPI_SR_TXE);
	uint8_t tmp2 = pSPIHandle->pSPIx->CR2 & (1 << SPI_CR2_TXEIE);
	if(tmp1 && tmp2){
		SPI_TXE_INTERRUPT_HANDLE(pSPIHandle);
	}


	tmp1 = pSPIHandle->pSPIx->SR & (1 << SPI_SR_RXNE);
	tmp2 = pSPIHandle->pSPIx->CR2 & (1 << SPI_CR2_RXNEIE);
	if(tmp1 && tmp2){
		SPI_RXNE_INTERRUPT_HANDLE(pSPIHandle);
	}


	tmp1 = pSPIHandle->pSPIx->SR & (1 << SPI_SR_OVR);
	tmp2 = pSPIHandle->pSPIx->CR2 & (1 << SPI_CR2_ERRIE);
	if(tmp1 && tmp2){
		SPI_ERR_INTERRUPT_HANDLE(pSPIHandle);
	}
}


static void SPI_TXE_INTERRUPT_HANDLE(SPI_Handle *pSPIHandle){
	/*check DFF (frame format)*/
	if((pSPIHandle->pSPIx ->CR1 & (1 << SPI_CR1_DFF))){ /*16bit format*/
		pSPIHandle->pSPIx ->DR = *((uint16_t *)pSPIHandle->pTxBuffer);
		pSPIHandle->TxLen -=2;
		(uint16_t *)pSPIHandle->pTxBuffer++;
	}
	else{ /*8bit format*/
		pSPIHandle->pSPIx ->DR = *(pSPIHandle->pTxBuffer);
		pSPIHandle->TxLen --;
		pSPIHandle->pTxBuffer++;
	}

	if(pSPIHandle->TxLen == 0){
		pSPIHandle->pSPIx->CR2 &= ~(1 << SPI_CR2_TXEIE);
		pSPIHandle->pTxBuffer = NULL;
		pSPIHandle->TxState = SPI_READY;
		SPI_ApplicationCallBack(pSPIHandle,SPI_EVENT_TX_CMPLT);
	}
}


static void SPI_RXNE_INTERRUPT_HANDLE(SPI_Handle *pSPIHandle){
	/*check DFF (frame format)*/
	if((pSPIHandle->pSPIx ->CR1 & (1 << SPI_CR1_DFF))){ /*16bit format*/
		*((uint16_t *)pSPIHandle->pRxBuffer) = pSPIHandle->pSPIx ->DR;
		pSPIHandle->RxLen -=2;
		(uint16_t *)pSPIHandle->pRxBuffer++;
	}
	else{ /*8bit format*/
		*(pSPIHandle->pRxBuffer) = pSPIHandle->pSPIx ->DR;
		pSPIHandle->RxLen --;
		pSPIHandle->pRxBuffer++;
	}
	if(pSPIHandle->RxLen == 0){
		pSPIHandle->pSPIx->CR2 &= ~(1 << SPI_CR2_RXNEIE);
		pSPIHandle->pRxBuffer = NULL;
		pSPIHandle->RxState = SPI_READY;
		SPI_ApplicationCallBack(pSPIHandle,SPI_EVENT_RX_CMPLT);
	}
}

static void SPI_ERR_INTERRUPT_HANDLE(SPI_Handle *pSPIHandle){
	uint8_t tmp;
	if(pSPIHandle->TxState != SPI_BUSY_IN_TX){
		tmp = pSPIHandle->pSPIx->DR;
		tmp = pSPIHandle->pSPIx->SR;
		tmp++;
	}
	SPI_ApplicationCallBack(pSPIHandle,SPI_EVENT_OVR_ERR);
}
void SPI_Enable(SPI_type *pSPIx, uint8_t EnorDi){
	if(EnorDi == ENABLE){
	  pSPIx ->CR1 |= (1 << SPI_CR1_SPE);
	}else{
	  pSPIx ->CR1 &= ~(1 << SPI_CR1_SPE);
	}
}

void SSI_Enable(SPI_type *pSPIx, uint8_t EnorDi){
	if(EnorDi == ENABLE){
	  pSPIx ->CR1 |= (1 << SPI_CR1_SSI);
	}else{
	  pSPIx ->CR1 &= ~(1 << SPI_CR1_SSI);
	}
}

void SSOE_Enable(SPI_type *pSPIx, uint8_t EnorDi){
	if(EnorDi == ENABLE){
	  pSPIx ->CR2 |= (1 << SPI_CR2_SSOE);
	}else{
	  pSPIx ->CR2 &= ~(1 << SPI_CR2_SSOE);
	}
}

__attribute__((weak)) void SPI_ApplicationCallBack(SPI_Handle *pSPIHandle,uint8_t AppEv){

}
