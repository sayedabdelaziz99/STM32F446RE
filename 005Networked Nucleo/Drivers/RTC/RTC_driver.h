/*
 * RTC.h
 *
 *  Created on: Mar 22, 2024
 *      Author: Sayed
 */

#ifndef RTC_RTC_DRIVER_H_
#define RTC_RTC_DRIVER_H_
#include "I2C_driver.h"

void RTC_SetTime(I2C_Handle *pI2CHandle);
void RTC_ReadTime(uint8_t *pRxBuffer, I2C_Handle *pI2CHandle);

#endif /* RTC_RTC_DRIVER_H_ */
