/*
 * RTC.c
 *
 *  Created on: Mar 22, 2024
 *      Author: Sayed
 */
#include "STMF446RE.h"
#include "RTC_driver.h"
#include "I2C_driver.h"

uint8_t SlaveAddress = 0x68U;
uint8_t StartAdress = 0x00U;

void RTC_ReadTime(uint8_t *pRxBuffer, I2C_Handle *pI2CHandle){

	I2C_MasterSendData(pI2CHandle, &StartAdress, sizeof(StartAdress), SlaveAddress);

	I2C_MasterRecieveData(pI2CHandle, pRxBuffer, 7, SlaveAddress);
}

void RTC_SetTime(I2C_Handle *pI2CHandle){
	uint8_t time[5] = {0x56, 0x9, 0x26,0x3, 0x24};
	uint8_t addresses[7] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06};
	//halt the clock
	I2C_MasterSendData(pI2CHandle, &addresses[0], sizeof(StartAdress), SlaveAddress);
	I2C_ProdCastData(pI2CHandle, (uint8_t *)(0x1 << 7), 1);
	//set the minute
	I2C_MasterSendData(pI2CHandle, &addresses[1], sizeof(StartAdress), SlaveAddress);
	I2C_ProdCastData(pI2CHandle, &time[0], 1);
	//set the hour
	I2C_MasterSendData(pI2CHandle, &addresses[2], sizeof(StartAdress), SlaveAddress);
	I2C_ProdCastData(pI2CHandle, &time[1], 1);
	//set the day
	I2C_MasterSendData(pI2CHandle, &addresses[3], sizeof(StartAdress), SlaveAddress);
	I2C_ProdCastData(pI2CHandle, &time[2], 1);
	//set the month
	I2C_MasterSendData(pI2CHandle, &addresses[5], sizeof(StartAdress), SlaveAddress);
	I2C_ProdCastData(pI2CHandle, &time[3], 1);
	//set the year
	I2C_MasterSendData(pI2CHandle, &addresses[6], sizeof(StartAdress), SlaveAddress);
	I2C_ProdCastData(pI2CHandle, &time[4], 1);
	//release the clock
	I2C_MasterSendData(pI2CHandle, &addresses[0], sizeof(StartAdress), SlaveAddress);
	I2C_ProdCastData(pI2CHandle, (uint8_t *)(0x0 << 7), 1);
}


