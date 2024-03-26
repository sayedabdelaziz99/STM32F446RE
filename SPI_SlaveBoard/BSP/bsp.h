/*
 * bsp.h
 *
 *  Created on: Jan 26, 2024
 *      Author: Sayed
 */

#ifndef INC_BSP_H_
#define INC_BSP_H_
#include "STMF446RE.h"
#include "GPIO_driver.h"

#define SysClock          16000000U       /*system clock of 16 MHz*/
#define Ticks_PerSecond   100U

/*enabling systick*/
void systic_init(void);
void SPI2_GPIOInit(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber, uint8_t ALTFN_Mode);
void delay(uint32_t ms);
#endif /* INC_BSP_H_ */
