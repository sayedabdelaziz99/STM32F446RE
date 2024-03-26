/*
 * I2C_Driver.c
 *
 *  Created on: Feb 2, 2024
 *      Author: Sayed
 */
#include "STMF446RE.h"
#include "I2C_driver.h"
#include "RCC_driver.h"
#include "GPIO_driver.h"

#define DEVICE_ADDRESS   0x1U

static void  I2C_GenerateStartCondition(I2C_type *pI2Cx);
static void I2C_ExecuteAddressPhaseWrite(I2C_type *pI2Cx, uint8_t SlaveAddr);
static void I2C_ExecuteAddressPhaseRead(I2C_type *pI2Cx, uint8_t SlaveAddr);
static void I2C_ClearADDRFlag(I2C_Handle *pI2CHandle);
static void I2C_MasterHandleRXNEInterrupt(I2C_Handle *pI2CHandle );
static void I2C_MasterHandleTXEInterrupt(I2C_Handle *pI2CHandle );
static uint8_t I2C_GenerateDataReceiving(I2C_type *pI2Cx);

static void I2C_GenerateStartCondition(I2C_type *pI2Cx);
uint16_t count = 0;
void I2C_Enable(I2C_type *pI2Cx, uint8_t EnorDi){
    if(EnorDi == ENABLE){
      pI2Cx ->CR1 |= (1 << I2C_CR1_PE);
	}
	else{
		pI2Cx ->CR1 &= ~(1 << I2C_CR1_PE);
	}
}

/*********************************************************************
 * @fn      		  - I2C_CLKCNT
 *
 * @brief             - This function enables or disables peripheral clock for the given I2C
 *
 * @param[in]         - base address of the I2C peripheral
 * @param[in]         - ENABLE or DISABLE macros
 * @param[in]         -
 *
 * @return            -  none
 *
 * @Note              -  none
 */
void I2C_CLKCNT(I2C_type *pI2Cx, uint8_t EnorDi){
	if(EnorDi == ENABLE){
		if(pI2Cx == I2C1){I2C1_CLKEN();}
		else if(pI2Cx == I2C2){I2C2_CLKEN();}
		else if(pI2Cx == I2C3){I2C3_CLKEN();}
	}
	else{
		if(pI2Cx == I2C1){I2C1_CLKDI();}
		else if(pI2Cx == I2C2){I2C2_CLKDI();}
		else if(pI2Cx == I2C3){I2C3_CLKDI();}

	}
}

void I2C_Init(I2C_Handle *pI2CHandle){
/*
* 1.Program the peripheral input clock in I2C_CR2 Register in order to
*  generate correct timings
* 2.Configure the clock control registers
* 3.Configure the rise time register
* 4.Program the I2C_CR1 register to enable the peripheral
* 5.Set the START bit in the I2C_CR1 register to generate a Start condition
*/

/*reset the I2C first*/
  pI2CHandle->pI2Cx->CR1 |= (1 << I2C_CR1_SWRST);
  pI2CHandle->pI2Cx->CR1 &= ~(1 << I2C_CR1_SWRST);

/*enabling the I2C peripheral*/
  I2C_Enable(pI2CHandle->pI2Cx, ENABLE);

  uint32_t tmp;
/*configuring the freq field in CR2 first*/
  tmp = getSystemClock() / 1000000U;
  pI2CHandle->pI2Cx->CR2 = (tmp & 0x3FU);

/*configuring the F/S if standard mode or fast mode then changing ccr value in CCR register*/
  /*configuring F/S*/
  if(pI2CHandle->I2C_Config.I2C_SCLSpeed <= I2C_SCL_SM){/*if it's standard mode*/
	/*configure the mode*/
	pI2CHandle->pI2Cx->CCR &= ~(1 << I2C_CCR_F_S);
	/*CCR = system clock / (2 * speed) */
	tmp = getSystemClock();
	uint32_t CCR_Value = tmp / (2 * pI2CHandle->I2C_Config.I2C_SCLSpeed);
	pI2CHandle->pI2Cx->CCR |= (CCR_Value << I2C_CCR_CCR) & 0x3FU;
  }
  else{/*fast mode*/
	/*configure the mode*/
	pI2CHandle->pI2Cx->CCR |= (1 << I2C_CCR_F_S);
	/*configure the duty cycle*/
	tmp = (pI2CHandle->I2C_Config.I2C_FMDutyCycle << I2C_CCR_DUTY) & 0x1;
	pI2CHandle->pI2Cx->CCR |= tmp;
	/*configure the CCR field*/
	if(pI2CHandle->I2C_Config.I2C_FMDutyCycle == I2C_FM_DUTY_2){
	  tmp = (getSystemClock() / (3 *pI2CHandle->I2C_Config.I2C_SCLSpeed)) & 0xFFFU;
	  pI2CHandle->pI2Cx->CCR |= tmp;
	}
	else{
	  tmp = (getSystemClock() / (25 *pI2CHandle->I2C_Config.I2C_SCLSpeed)) & 0xFFFU;
	  pI2CHandle->pI2Cx->CCR |= tmp;
	}
  }

  /*configure the rise time*/
  if(pI2CHandle->I2C_Config.I2C_SCLSpeed == I2C_SCL_SM){/*if it's standered mode*/
	/*rise time = (system time period / maximum allowed rise time for sm) + 1*/
	uint32_t clock = getSystemClock();
	tmp = (clock / 1000000U) + 1;
	pI2CHandle->pI2Cx->TRISE = tmp & 0x3FU;
  }
  else{/*fast mode*/
		tmp = ((getSystemClock() * 300) / 1000000U) + 1;
		pI2CHandle->pI2Cx->TRISE = tmp & 0x3FU;
	}

  /*configure Device Own Address in case it's used as slave*/
  pI2CHandle ->pI2Cx->OAR1 |= (DEVICE_ADDRESS << 1);

  /*configuring the addressing mode*/
  tmp = pI2CHandle->I2C_Config.I2C_AddressMode;
  pI2CHandle->pI2Cx->OAR1 |= ((tmp << I2C_OAR1_ADD0) & 0x7FU);

  /*enabling the ACK*/
    pI2CHandle->pI2Cx->CR1 |= (1 << I2C_CR1_ACK);
}


/*********************************************************************
 * @fn      		  - I2C_DeInit
 *
 * @brief             - this function stops the clock for a given I2C
 *
 * @param[in]         - base address of the I2C peripheral
 * @param[in]         -
 * @param[in]         -
 *
 * @return            -  none
 *
 * @Note              -  none

 */
void I2C_DeInit(I2C_type *pI2Cx){
	if(pI2Cx == I2C1){I2C1_CLKDI();}
	else if(pI2Cx == I2C2){I2C2_CLKDI();}
	else{I2C3_CLKDI();}
}

uint8_t I2C_GetFlagStatus(I2C_type *pI2Cx ,uint8_t FlagName){
	if(pI2Cx ->SR1 & FlagName){
		return SET;
	}
	return RESET;
}


void I2C_MasterSendData(I2C_Handle *pI2CHandle, uint8_t *pTxBuffer, uint8_t Len, uint8_t SlaveAddress){

	// 1. Generate the START condition
	I2C_GenerateStartCondition(pI2CHandle->pI2Cx);

	//2. confirm that start generation is completed by checking the SB flag in the SR1
	//   Note: Until SB is cleared SCL will be stretched (pulled to LOW)
	while( ! I2C_GetFlagStatus(pI2CHandle->pI2Cx,I2C_FLAG_SB));

	//3. Send the address of the slave with r/nw bit set to w(0) (total 8 bits )
	I2C_ExecuteAddressPhaseWrite(pI2CHandle->pI2Cx,SlaveAddress);

	//4. Confirm that address phase is completed by checking the ADDR flag in teh SR1
	while( !  I2C_GetFlagStatus(pI2CHandle->pI2Cx,I2C_FLAG_ADDR)   );

	//5. clear the ADDR flag according to its software sequence
	//   Note: Until ADDR is cleared SCL will be stretched (pulled to LOW)
	I2C_ClearADDRFlag(pI2CHandle);

	//6. send the data until len becomes 0
	  while(Len > 0){
	    /*clearing (EV8)*/
	    pI2CHandle->pI2Cx->DR = *pTxBuffer;
	    Len--;
	    pTxBuffer++;
	    /*waiting for (EV8)*/
	    while(! I2C_GetFlagStatus(pI2CHandle->pI2Cx, I2C_FLAG_TxE));
	  }
	/*generate stop condition*/
	  /*wait for (EV8_2) BTF and TxE to be set first*/
	  while(! I2C_GetFlagStatus(pI2CHandle->pI2Cx, I2C_FLAG_TxE));
	  while(! I2C_GetFlagStatus(pI2CHandle->pI2Cx, I2C_FLAG_BTF));

	/*clearing (EV8_2) by Setting the STOP bit in CR1 register*/
	  pI2CHandle->pI2Cx->CR1 |= (1 << I2C_CR1_STOP);
}

void I2C_MasterRecieveData(I2C_Handle *pI2CHandle, uint8_t *pRxBuffer, uint8_t Len, uint8_t SlaveAddress){
if(Len == 1){/*if single byte to be read*/
 /* Write the slave Address, and wait for the ADDR bit (bit 1 in SR1) to be set
  * the Acknowledge disable is made during EV6 (before ADDR flag is cleared) and the STOP condition generation is made after EV6
  * Wait for the RXNE (Receive Buffer not Empty) bit to set
  * Read the data from the DR
  */
  SlaveAddress = SlaveAddress << 1;
  SlaveAddress |= (1 << 0);
  pI2CHandle->pI2Cx->DR = SlaveAddress;
  while(! I2C_GetFlagStatus(pI2CHandle->pI2Cx, I2C_FLAG_ADDR));
  pI2CHandle->pI2Cx->CR1 &= ~(1 << I2C_CR1_ACK);
  uint8_t dummyRead = pI2CHandle->pI2Cx->SR1 | pI2CHandle->pI2Cx->SR2;
  dummyRead++;
  pI2CHandle->pI2Cx->CR1 &= ~(1 << I2C_CR1_STOP);
  while(!I2C_GetFlagStatus(pI2CHandle->pI2Cx, I2C_SR1_RxNE));
  *pRxBuffer = pI2CHandle->pI2Cx->DR;
}
else{/*if multible bytes to be read*/
/*Write the slave Address, and wait for the ADDR bit (bit 1 in SR1) to be set
* Clear the ADDR bit by reading the SR1 and SR2 Registers
* Wait for the RXNE (Receive buffer not empty) bit to set
* Read the data from the DR
* Generate the Acknowlegment by settint the ACK (bit 10 in SR1)
* To generate the nonacknowledge pulse after the last received data byte, the ACK bit must be cleared just after reading the
*   second last data byte (after second last RxNE event)
* In order to generate the Stop/Restart condition, software must set the STOP/START bit
* after reading the second last data byte (after the second last RxNE event)
*/
  SlaveAddress = SlaveAddress << 1;
  SlaveAddress |= (1 << 0);
  pI2CHandle->pI2Cx->DR = SlaveAddress;
  while(! I2C_GetFlagStatus(pI2CHandle->pI2Cx, I2C_FLAG_ADDR));
  uint8_t dummyRead = pI2CHandle->pI2Cx->SR1 | pI2CHandle->pI2Cx->SR2;
  dummyRead++;
  while(Len > 2){
	while(!I2C_GetFlagStatus(pI2CHandle->pI2Cx, I2C_SR1_RxNE));
	*pRxBuffer = pI2CHandle->pI2Cx->DR;
	pI2CHandle->pI2Cx->CR1 |= (1 << I2C_CR1_ACK);
	Len--;
	pRxBuffer++;
  }
  while(! I2C_GetFlagStatus(pI2CHandle->pI2Cx, I2C_SR1_RxNE));
  *pRxBuffer = pI2CHandle->pI2Cx->DR;
  Len--;
  pRxBuffer++;
  pI2CHandle->pI2Cx->CR1 &= ~(1 << I2C_CR1_ACK);
  pI2CHandle->pI2Cx->CR1 &= ~(1 << I2C_CR1_STOP);
  while(!I2C_GetFlagStatus(pI2CHandle->pI2Cx, I2C_SR1_RxNE));
  *pRxBuffer = pI2CHandle->pI2Cx->DR;
}
}

void I2C_SLaveSendData(I2C_Handle *pI2CHandle, uint8_t *pTxBuffer, uint8_t Len){

}
void I2C_SlaveRecieveData(I2C_Handle *pI2CHandle){
  /*1. waiting until the address is matched*/
/*not processing forward if the slave address is not matching ours*/
  while(! I2C_GetFlagStatus(pI2CHandle->pI2Cx, I2C_FLAG_ADDR));
  I2C_ClearADDRFlag(pI2CHandle);
/*2. reading the data*/
  while(! I2C_GetFlagStatus(pI2CHandle->pI2Cx, I2C_SR1_STOPF)){
    while(! I2C_GetFlagStatus(pI2CHandle->pI2Cx, I2C_SR1_RxNE));
    uint8_t pTxBuffer = I2C_GenerateDataReceiving(pI2CHandle->pI2Cx);
  }
  /*3. clearing the STOPF bit if stop condition is detected*/
  uint16_t dummyRead;
  if(pI2CHandle->pI2Cx->SR1 &= (1 << I2C_SR1_STOPF)){
  dummyRead = pI2CHandle->pI2Cx->SR1;
  pI2CHandle->pI2Cx->CR1 |= 0x0000;
  }
  /*stop the communication after the current byte transfer*/
  pI2CHandle->pI2Cx->CR1 |= (1 << I2C_CR1_STOP);
  //GPIO_ToggleOutputPin(GPIOA, GPIO_PIN_NO_5);
}

void I2C_IRQInterruptConfig(uint8_t IRQNumber, uint8_t ENorDI){

}

void I2C_IRQPriorityConfig(uint8_t IRQNumber, uint32_t IRQPriority){

}

static void  I2C_GenerateStartCondition(I2C_type *pI2Cx){
  pI2Cx->CR1 |= (1 << I2C_CR1_START);
}

static void I2C_ExecuteAddressPhaseWrite(I2C_type *pI2Cx, uint8_t SlaveAddress){
  uint16_t DummyRead;
  DummyRead = pI2Cx->SR1;
/*sending the address of the slave followed by the R/nW bit*/
  SlaveAddress = SlaveAddress << 1;  /*making room for the R/nW bit*/
  SlaveAddress &= ~(1);               /*clearing LSB so it's a write condition*/
  pI2Cx->DR = SlaveAddress;
}

static void I2C_ClearADDRFlag(I2C_Handle *pI2CHandle){
   uint16_t DummyRead;
/*wait for (EV6) ADDR bit in SR1 to sit*/
  while(! I2C_GetFlagStatus(pI2CHandle->pI2Cx, I2C_FLAG_ADDR));
  /*clearing (EV6) ADDR flag*/
  DummyRead = pI2CHandle->pI2Cx->SR1;
  DummyRead = pI2CHandle->pI2Cx->SR2;
  DummyRead++;  /*to stop compiler warning about set but not used*/
}


static uint8_t I2C_GenerateDataReceiving(I2C_type *pI2Cx){
  return pI2Cx->DR;
}
