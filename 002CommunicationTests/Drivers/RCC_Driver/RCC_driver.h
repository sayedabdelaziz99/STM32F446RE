/*
 * RCC_driver.h
 *
 *  Created on: Feb 4, 2024
 *      Author: Sayed
 */

#ifndef RCC_DRIVER_RCC_DRIVER_H_
#define RCC_DRIVER_RCC_DRIVER_H_

#include "STMF446RE.h"

#define HSI_CLOCK 16000000U
#define HSE_CLOCK 8000000U

uint32_t getSystemClock(void);
uint32_t getAHBClock(void);
uint32_t getAPBClock(uint32_t BusAddress);

#endif /* RCC_DRIVER_RCC_DRIVER_H_ */
