/*
 * main.c
 *
 *  Created on: Mar 14, 2024
 *      Author: Sayed
 */
#include "GPIO_driver.h"
#include "RCC_driver.h"
#include "bsp.h"
#include "string.h"
#include "Timer_Driver.h"

#define PRESCALER (16)
#define ARR_VALUE (1000)

static void timer_set_mode(uint32_t clock_div,uint32_t alignment, uint32_t direction);
static void timer_set_oc_mode();
inline static void timer_enable_counter(void);
inline static void timer_enable_oc_output(void);
inline static void timer_set_period(uint32_t period);
inline static void timer_set_prescaler(uint32_t value);
static void SetDuty(float DutyCycle);
inline static void timer_set_oc_value(float value);
static void timer_setup(void);

uint32_t Ticks = 0U;
uint32_t TicksPerSecond = 1000U;

int main(void){
	//enable floating point full access
	SCB ->CPACR |= ((3UL << 20U)|(3UL << 22U));

	GPIO_TIM2Init(GPIOA, GPIO_PIN_NO_5, 1);
	timer_setup();
	/*initialize SysTick*/
	systick_init(TicksPerSecond);

/*Code starts here*/
	float DutyCycle = 0.0f;
	uint32_t StartTime = Ticks;
	SetDuty(DutyCycle);
	while(1){
		if((Ticks - StartTime) >= 10){
		DutyCycle += 1.0f;
			if(DutyCycle >= 100){
				DutyCycle = 0.0f;
			}
			SetDuty(DutyCycle);
			StartTime = Ticks;
		}
	}

/*Code ends here*/
}

void SysTick_Handler(void){
	Ticks++;
}

static void timer_setup(void){
	//enable clock for the timer
	TIM2_CLKEN();

	// Setup frequency and resolution
	timer_set_prescaler(PRESCALER - 1);
	timer_set_period(ARR_VALUE - 1);

	// High level timer configuration
	timer_set_mode(1, 0, 0);

	// Setup PWM mode
	timer_set_oc_mode();

	// Enable PWM output
	timer_enable_counter();
	timer_enable_oc_output();
}

static void timer_set_mode(uint32_t clock_div,uint32_t alignment, uint32_t direction){
	TIM2 ->CR1 &= ~(1);
	TIM2 ->CR1 |= clock_div | alignment | direction;
	TIM2->CR1  |= (0x1 << TIM_CR1_ARPE);
}

static void timer_set_oc_mode(){
	TIM2->CCMR1 &= ~(0x3U << 0);
	TIM2->CCMR1 |= (0x0U << 0); //output mode
	TIM2->CCMR1 &= ~(0x7U << 4);
	TIM2->CCMR1 |= (0x6U << 4); //PWM1 mode
	TIM2->CCMR1 |= (0x1U << 3); //PreLoad
	TIM2->BDTR |= (0x1 << 15); //MOE
}

inline static void timer_enable_counter(void){
	TIM2 ->CR1 |= TIM_CR1_CEN;
}


inline static void timer_enable_oc_output(void){
	TIM2->CCER |= (0x1U << 0);
}

inline static void timer_set_period(uint32_t period){
	TIM2 ->ARR = period;
}
inline static void timer_set_prescaler(uint32_t value){
	TIM2 ->PSC = value;
}

static void SetDuty(float DutyCycle){
	const float raw_value = (float)ARR_VALUE * (DutyCycle / 100.0f);
	timer_set_oc_value(raw_value);
}

inline static void timer_set_oc_value(float value){
	TIM2 ->CCR1 = (uint32_t)value;
}
