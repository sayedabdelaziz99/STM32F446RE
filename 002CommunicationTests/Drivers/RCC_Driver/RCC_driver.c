/*
 * RCC_driver.c
 *
 *  Created on: Feb 4, 2024
 *      Author: Sayed
 */
#include "STMF446RE.h"
#include "RCC_driver.h"

uint16_t AHB_PRESCALERS[8] = {2, 4, 8, 16, 64, 128, 256, 512};
uint16_t APB_PRESCALERS[4] = {2, 4, 8, 16};

uint32_t getSystemClock(void){
uint8_t PLLP1 = ((RCC->PLLCFGR >> 16) & 0x3U);
uint8_t PLLP;
uint32_t fPLL,fPLLR;
switch(PLLP1){
  case(0):
		  PLLP = 2;
          break;
  case(1):
		  PLLP = 4;
          break;
  case(2):
		  PLLP = 6;
          break;
  case(3):
		  PLLP = 8;
          break;
}
uint16_t PLLN = ((RCC ->PLLCFGR >> 6) & 0x1FF);
uint16_t PLLM = (RCC ->PLLCFGR & 0x3FU);
uint16_t PLLR = (RCC ->PLLCFGR >> 28) & 0x7U;
uint32_t fVCO = HSI_CLOCK * (PLLN / PLLM); /*HSI is used as pll input*/
	switch (RCC ->CFGR >> 2){
		case(0) : /*HSI is used*/
			return HSI_CLOCK; /*HSI clock speed*/
		case(1) : /*HSE is used*/
			return HSE_CLOCK;
		case(2) : /*PLL is used*/
		   fPLL = fVCO * PLLP;
		  return fPLL;
		case(3) : /*PLL_R is used*/
			/*Clock frequancy = VCO / PLLR*/
			 fPLLR = fVCO / PLLR;
			return fPLLR;
	}
}

uint32_t getAHBClock(void){
	uint32_t SystemClock = getSystemClock();
	uint16_t AHB_PRESCALER;
	if(((RCC ->CFGR >> 4) & 0xFU) < 8){
	  AHB_PRESCALER = 1;
	}else{
	  AHB_PRESCALER = AHB_PRESCALERS[((RCC ->CFGR >> 4) & 0xFU) - 8];
	}
	uint32_t AHBClock = SystemClock / AHB_PRESCALER;
	return AHBClock;
}

uint32_t getAPBClock(uint32_t BusAddress){
	if(BusAddress == APB1PREF_BASEADDR){
		uint8_t APB1PRESCALER;
		if(((RCC ->CFGR >> 10) & 0x7U) < 4){
		  APB1PRESCALER = 1;
		}else{
		  APB1PRESCALER = APB_PRESCALERS[((RCC ->CFGR >> 10) & 0x7U) - 4];
		}
		return (getSystemClock() / APB1PRESCALER);
	}
	else{
		uint8_t APB2PRESCALER;
		if(((RCC ->CFGR >> 13) & 0x7U) < 4){
		  APB2PRESCALER = 1;
		}else{
		  APB2PRESCALER = APB_PRESCALERS[((RCC ->CFGR >> 10) & 0x7U) - 4];
		}
		return (getSystemClock() / APB2PRESCALER);
	}
}
