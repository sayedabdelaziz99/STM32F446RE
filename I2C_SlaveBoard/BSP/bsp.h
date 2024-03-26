/*
 * bsp.h
 *
 *  Created on: Jan 26, 2024
 *      Author: Sayed
 */

#ifndef INC_BSP_H_
#define INC_BSP_H_
#include "GPIO_driver.h"
#include "../Drivers/stm32f446re/STMF446RE.h"

#define SysClock          16000000U       /*system clock of 16 MHz*/
#define Ticks_PerSecond   10U

/*enabling systick*/
void systic_init(void);
void SPI2_GPIOInit(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber, uint8_t ALTFN_Mode);
void I2C1_GPIOInit(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber, uint8_t ALTFN_Mode);
void delay(uint32_t ms);
void EXTI15_10_IRQHandler(void);
#endif /* INC_BSP_H_ */
