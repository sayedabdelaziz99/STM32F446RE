/*
 * rtc.c
 *
 *  Created on: Mar 22, 2024
 *      Author: Sayed
 */

#include "GPIO_driver.h"
#include "I2C_driver.h"
#include "RTC_driver.h"
#include "bsp.h"


int main(void){
	I2C_init();
	uint8_t data[7];
	while(1){
		delay(50);
		RTC_ReadTime(data);
	}
}

