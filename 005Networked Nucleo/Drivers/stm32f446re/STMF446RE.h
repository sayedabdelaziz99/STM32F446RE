/*
 * bsp.h
 *	@brief: this is a Board Supported Package for stm32F446RF
 *  Created on: Jan 22, 2024
 *      Author: Sayed
 */

#ifndef STM32F446RE_STMF446RE_H_
#define STM32F446RE_STMF446RE_H_

#include <stdint.h>
#include <stddef.h>
#define __vo volatile



#define SCB    ((SCB_Type *)SCB_BASEADDR)

/*ARM NVIC control registers*/
#define ISER0  ((__vo uint32_t *)0xE000E100)
#define ISER1  ((__vo uint32_t *)0xE000E104)
#define ISER2  ((__vo uint32_t *)0xE000E108)
#define ISER3  ((__vo uint32_t *)0xE000E10C)
#define ISER4  ((__vo uint32_t *)0xE000E10E)
#define ISER5  ((__vo uint32_t *)0xE000E110)
#define ISER6  ((__vo uint32_t *)0xE000E114)
#define ISER7  ((__vo uint32_t *)0xE000E118)

#define ICER0  ((__vo uint32_t *)0XE000E180)
#define ICER1  ((__vo uint32_t *)0XE000E184)
#define ICER2  ((__vo uint32_t *)0XE000E188)
#define ICER3  ((__vo uint32_t *)0XE000E18C)
#define ICER4  ((__vo uint32_t *)0XE000E190)
#define ICER5  ((__vo uint32_t *)0XE000E194)
#define ICER6  ((__vo uint32_t *)0XE000E198)
#define ICER7  ((__vo uint32_t *)0XE000E19C)

#define ICPR0  ((__vo uint32_t *)0XE000E280)
#define ICPR1  ((__vo uint32_t *)0XE000E284)
#define ICPR2  ((__vo uint32_t *)0XE000E288)
#define ICPR3  ((__vo uint32_t *)0XE000E28C)
#define ICPR4  ((__vo uint32_t *)0XE000E290)
#define ICPR5  ((__vo uint32_t *)0XE000E294)
#define ICPR6  ((__vo uint32_t *)0XE000E298)
#define ICPR7  ((__vo uint32_t *)0XE000E29C)

#define IPR_BASEADDR    ((__vo uint32_t *)0xE000E400)
#define SCB_BASEADDR	((__vo uint32_t *)0xE000ED00)

/*BASE addresses of flash and ram memory*/
#define FLASH_BASEADRR			( 0x08000000U)
#define SRAM1_BASEADDR			( 0x20000000U)
#define SRAM2_BASEADDR			( 0x2001C000U)
#define ROM_BASEADDR			( 0x1FFF0000U)
#define RAM_BASEADDR   			SRAM1_BASEADDR

/*Base addresses of the different BUSEs in the MCU*/
#define BUSPREF_BASEADDR   		( 0x40000000U)
#define APB1PREF_BASEADDR  		BUSPREF_BASEADDR
#define APB2PREF_BASEADDR  		( 0x40010000U)
#define AHB1PREF_BASEADDR  		( 0x40020000U)
#define AHB2PREF_BASEADDR  		( 0x50000000U)
#define AHB3PREF_BASEADDR  		( 0xA0001000U)

/*Peripherals connected to the ABP1 BUS*/
#define TIM2_BASEADDR			( 0x40000000U)
#define TIM3_BASEADDR   		( 0x40000400U)
#define TIM4_BASEADDR			( 0x40000800U)
#define TIM5_BASEADDR   		( 0x40000C00U)
#define TIM6_BASEADDR   		( 0x40001000U)
#define TIM7_BASEADDR   		( 0x40001400U)
#define TIM12_BASEADDR  		( 0x40001800U)
#define TIM13_BASEADDR  		( 0x40001C00U)
#define TIM14_BASEADDR  		( 0x40002000U)
#define RTCBKP_BASEADDR 		( 0x40002800U)
#define WWDG_BASEADDR			( 0x40002C00U)
#define IWDG_BASEADDR   		( 0x40003000U)
#define SPI2I2S2_BASEADDR 		( 0x40003800U)
#define SPI3I2S3_BASEADDR 		( 0x40003C00U)
#define SPDIFRX_BASEADDR 		( 0x40004000U)
#define USART2_BASEADDR  		( 0x40004400U)
#define USART3_BASEADDR  		( 0x40004800U)
#define UART4_BASEADDR  		( 0x40004C00U)
#define UART5_BASEADDR  		( 0x40005000U)
#define I2C1_BASEADDR 			( 0x40005400U)
#define I2C2_BASEADDR  			( 0x40005800U)
#define I2C3_BASEADDR  			( 0x40005C00U)
#define FMPI2C1_BASEADDR 		( 0x40006000u)
#define CAN1_BASEADDR 			( 0x40006400U)
#define CAN2_BASEADDR 			( 0x40006800U)
#define HDMICEC_BASEADDR 		( 0x40006C00U)
#define PWE_BASEADDR 			( 0x40007000U)
#define DAC_BASEADDR  			( 0x40007400U)

/*Peripherals connected to the ABP2 BUS*/
#define TIM1_BASEADDR 			( 0x40010000U)
#define TIM8_BASEADDR  			( 0x40010400U)
#define USART1_BASEADDR 		( 0x40011000U)
#define USART6_BASEADDR 		( 0x40011400U)
#define ADC123_BASEADDR 		( 0x40012000U)
#define SDI0_BASEADDR 			( 0x40012C00U)
#define SPI1_BASEADDR 			( 0x40013000U)
#define SPI4_BASEADDR 			( 0x40013400U)
#define SYSCFG_BASEADDR 		( 0x40013800U)
#define EXTI_BASEADDR 			( 0x40013C00U)
#define TIM9_BASEADDR 			( 0x40014000U)
#define TIM10_BASEADDR 			( 0x40014400U)
#define TIM11_BASEADDR 			( 0x40014800U)
#define SAI1_BASEADDR 			( 0x40015800U)
#define SAI2_BASEADDR 			( 0x40015C00U)

/*Peripherals connected to the AHP1 BUS*/
#define GPIOA_BASEADDR 			( 0x40020000U)
#define GPIOB_BASEADDR 			( 0x40020400U)
#define GPIOC_BASEADDR 			( 0x40020800U)
#define GPIOD_BASEADDR 			( 0x40020C00U)
#define GPIOE_BASEADDR 			( 0x40021000U)
#define GPIOF_BASEADDR 			( 0x40021400U)
#define GPIOG_BASEADDR 			( 0x40021800U)
#define GPIOH_BASEADDR 			( 0x40021C00U)
#define CRC_BASEADDR 			( 0x40023000U)
#define RCC_BASEADDR 			( 0x40023800U)
#define FLASHINTRE_BASEADDR 	( 0x40023C00U)
#define BKPSRAM_BASEADDR 		( 0x40024000U)
#define DMA1_BASEADDR 			( 0x40026000U)
#define DMA2_BASEADDR 			( 0x40026400U)
#define USBOTGHS_BASEARRD 		( 0x40040000U)

/*Peripherals connected to the AHP2 BUS*/
#define USBOTGFS_BASEADDR 		( 0x50000000U)
#define DCMI_BASEADDR 			( 0x50050000U)

/*Peripherals connected to the AHP3 BUS*/
#define FMCBANK1_BASEADDR 		( 0x60000000U)
#define FMCBANK3_BASEADDR 		( 0x80000000U)
#define QUADSPI_BASEADDR  		( 0x90000000U)
#define FMCCNTRE_BASEADDR 		( 0xA0000000U)
#define QUADSPICNTRE_BASEADDR 	( 0xA0001000U)
#define FMCBANK5_BASEADDR 		( 0xC0000000U)
#define FMC6BANK_BASEADDR 		( 0xD0000000U)
#define M4INTPREF_BASEADDR 		( 0xE0000000U)

/*SysTick*/
#define SysTick_BASEADDR        (0xE000E010)


/*structures for various peripherals*/

typedef struct
{
  __vo const  uint32_t CPUID;                  /*!< Offset: 0x000 (R/ )  CPUID Base Register */
  __vo uint32_t ICSR;                   /*!< Offset: 0x004 (R/W)  Interrupt Control and State Register */
  __vo uint32_t VTOR;                   /*!< Offset: 0x008 (R/W)  Vector Table Offset Register */
  __vo uint32_t AIRCR;                  /*!< Offset: 0x00C (R/W)  Application Interrupt and Reset Control Register */
  __vo uint32_t SCR;                    /*!< Offset: 0x010 (R/W)  System Control Register */
  __vo uint32_t CCR;                    /*!< Offset: 0x014 (R/W)  Configuration Control Register */
  __vo uint8_t  SHP[12U];               /*!< Offset: 0x018 (R/W)  System Handlers Priority Registers (4-7, 8-11, 12-15) */
  __vo uint32_t SHCSR;                  /*!< Offset: 0x024 (R/W)  System Handler Control and State Register */
  __vo uint32_t CFSR;                   /*!< Offset: 0x028 (R/W)  Configurable Fault Status Register */
  __vo uint32_t HFSR;                   /*!< Offset: 0x02C (R/W)  HardFault Status Register */
  __vo uint32_t DFSR;                   /*!< Offset: 0x030 (R/W)  Debug Fault Status Register */
  __vo uint32_t MMFAR;                  /*!< Offset: 0x034 (R/W)  MemManage Fault Address Register */
  __vo uint32_t BFAR;                   /*!< Offset: 0x038 (R/W)  BusFault Address Register */
  __vo uint32_t AFSR;                   /*!< Offset: 0x03C (R/W)  Auxiliary Fault Status Register */
  __vo const  uint32_t PFR[2U];                /*!< Offset: 0x040 (R/ )  Processor Feature Register */
  __vo const  uint32_t DFR;                    /*!< Offset: 0x048 (R/ )  Debug Feature Register */
  __vo const  uint32_t ADR;                    /*!< Offset: 0x04C (R/ )  Auxiliary Feature Register */
  __vo const  uint32_t MMFR[4U];               /*!< Offset: 0x050 (R/ )  Memory Model Feature Register */
  __vo const  uint32_t ISAR[5U];               /*!< Offset: 0x060 (R/ )  Instruction Set Attributes Register */
        uint32_t RESERVED0[5U];
  __vo uint32_t CPACR;                  /*!< Offset: 0x088 (R/W)  Coprocessor Access Control Register */
} SCB_Type;

typedef struct {
	uint32_t __vo MODER;
	uint32_t __vo OTYPER;
	uint32_t __vo OSPEEDER;
	uint32_t __vo PUPDR;
	uint32_t __vo IDR;
	uint32_t __vo ODR;
	uint32_t __vo BSRR;
	uint32_t __vo LCKR;
	uint32_t __vo AFR[2];
}GPIO_RegDef_t;

typedef struct {
	uint32_t __vo CR;
	uint32_t __vo PLLCFGR;
	uint32_t __vo CFGR;
	uint32_t __vo CIR;
	uint32_t __vo AHB1RSTR;
	uint32_t __vo AHB2RSTR;
	uint32_t __vo AHB3RSTR;
	uint32_t      RESERVED0;
	uint32_t __vo APB1RSTR;
	uint32_t __vo APB2RSTR;
	uint32_t      RESERVED1[2];
	uint32_t __vo AHB1ENR;
	uint32_t __vo AHB2ENR;
	uint32_t __vo AHB3ENR;
	uint32_t      RESERVED2;
	uint32_t __vo APB1ENR;
	uint32_t __vo APB2ENR;
	uint32_t      RESERVED3[2];
	uint32_t __vo AHB1LPENR;
	uint32_t __vo AHB2LPENR;
	uint32_t __vo AHB3LPENR;
	uint32_t      RESERVED4;
	uint32_t __vo APB1LPENR;
	uint32_t __vo APB2LPENR;
	uint32_t      RESERVED5[2];
	uint32_t __vo BDCR;
	uint32_t __vo CSR;
	uint32_t      RESERVED6[2];
	uint32_t __vo SSCGR;
	uint32_t __vo PLLI2SCFGR;
	uint32_t __vo PLLSAICFGR;
	uint32_t __vo DCKCFGR;
	uint32_t __vo CKGATENR;
	uint32_t __vo DCKCFGR2;

}RCC_type;

typedef struct{
	uint32_t __vo IMR;
	uint32_t __vo EMR;
	uint32_t __vo RTSR;
	uint32_t __vo FTSR;
	uint32_t __vo SWIER;
	uint32_t __vo PR;
}EXTI_type;

typedef struct{

}NVIC_type;
typedef struct{
	uint32_t __vo MEMRMP;
	uint32_t __vo PMC;
	uint32_t __vo EXTICR[4];
	uint32_t __vo CMPCR;
	uint32_t __vo CFGR;
}SYSCFG_type;

typedef struct{
	uint32_t  __vo CSR;
	uint32_t  __vo RVR;
	uint32_t  __vo CVR;
	uint32_t  __vo CALIB;
}SysTick_type;

typedef struct{
	uint32_t __vo  CR1;
	uint32_t __vo  CR2;
	uint32_t __vo  SR;
	uint32_t __vo  DR;
	uint32_t __vo  CRCPR;
	uint32_t __vo  RXCRCR;
	uint32_t __vo  TXCRCR;
	uint32_t __vo  I2SCFGR;
	uint32_t __vo  I2SPR;
}SPI_type;

typedef struct{
	uint32_t __vo CR1;
	uint32_t __vo CR2;
	uint32_t __vo OAR1;
	uint32_t __vo OAR2;
	uint32_t __vo DR;
	uint32_t __vo SR1;
	uint32_t __vo SR2;
	uint32_t __vo CCR;
	uint32_t __vo TRISE;
	uint32_t __vo FLTR;
}I2C_type;

typedef struct{
	uint32_t __vo SR;
	uint32_t __vo DR;
	uint32_t __vo BRR;
	uint32_t __vo CR1;
	uint32_t __vo CR2;
	uint32_t __vo CR3;
	uint32_t __vo GTPR;
}USART_type;

typedef struct{
	uint32_t __vo TIR;
	uint32_t __vo TDTR;
	uint32_t __vo TDLR;
	uint32_t __vo TDHR;
}CAN_TxMailBox_type;

typedef struct{
	uint32_t __vo RIR;
	uint32_t __vo RDTR;
	uint32_t __vo RDLR;
	uint32_t __vo RDHR;
}CAN_FIFOMailBox_type;

typedef struct{
	uint32_t __vo FR1;
	uint32_t __vo FR2;
}CAN_FilterRegister_type;

typedef struct {
	uint32_t __vo MCR;
	uint32_t __vo MSR;
	uint32_t __vo TSR;
	uint32_t __vo RF0R;
	uint32_t __vo RF1R;
	uint32_t __vo IER;
	uint32_t __vo ESR;
	uint32_t __vo BTR;
	uint32_t __vo RESERVED0[88];
	CAN_TxMailBox_type	sTxMailBox[3];
	CAN_FIFOMailBox_type sFIFOMailBox[2];
	uint32_t __vo RESERVED1[12];
	uint32_t __vo FMR;
	uint32_t __vo FM1R;
	uint32_t __vo RESERVED2;
	uint32_t __vo FS1R;
	uint32_t __vo RESERVED3;
	uint32_t __vo FFA1R;
	uint32_t __vo RESERVED4;
	uint32_t __vo FA1R;
	uint32_t RESERVED5[8];
	CAN_FilterRegister_type sFilterRegister[28];
}CAN_type;

typedef struct{
	uint32_t __vo CR1;
	uint32_t __vo CR2;
	uint32_t RESERVED1;
	uint32_t __vo DIER;
	uint32_t __vo SR;
	uint32_t __vo EGR;
	uint32_t RESERVED2[3];
	uint32_t __vo CNT;
	uint32_t __vo PSC;
	uint32_t __vo ARR;
}BasicTimer_type;

/*Peripherals definitions */

#define GPIOA 	((GPIO_RegDef_t *)GPIOA_BASEADDR)
#define GPIOB 	((GPIO_RegDef_t *)GPIOB_BASEADDR)
#define GPIOC 	((GPIO_RegDef_t *)GPIOC_BASEADDR)
#define GPIOD 	((GPIO_RegDef_t *)GPIOD_BASEADDR)
#define GPIOE 	((GPIO_RegDef_t *)GPIOE_BASEADDR)
#define GPIOF 	((GPIO_RegDef_t *)GPIOF_BASEADDR)
#define GPIOG 	((GPIO_RegDef_t *)GPIOG_BASEADDR)
#define GPIOH 	((GPIO_RegDef_t *)GPIOH_BASEADDR)
#define RCC     ((RCC_type  *)RCC_BASEADDR)
#define EXTI    ((EXTI_type  *)EXTI_BASEADDR)
#define SYSCFG  ((SYSCFG_type  *)SYSCFG_BASEADDR)
#define SysTick ((SysTick_type *)SysTick_BASEADDR)
#define SPI1	((SPI_type *)SPI1_BASEADDR)
#define SPI2	((SPI_type *)SPI2I2S2_BASEADDR)
#define SPI3	((SPI_type *)SPI3I2S3_BASEADDR)
#define SPI4	((SPI_type *)SPI4_BASEADDR)
#define I2C1    ((I2C_type *)I2C1_BASEADDR)
#define I2C3    ((I2C_type *)I2C2_BASEADDR)
#define I2C2    ((I2C_type *)I2C3_BASEADDR)
#define USART1  ((USART_type *)USART1_BASEADDR)
#define USART2	((USART_type *)USART2_BASEADDR)
#define USART3	((USART_type *)USART3_BASEADDR)
#define UART4  	((USART_type *)UART4_BASEADDR)
#define UART5	((USART_type *)UART5_BASEADDR)
#define USART6	((USART_type *)USART6_BASEADDR)
#define TIM6	((BasicTimer_type *)TIM6_BASEADDR)
#define TIM7	((BasicTimer_type *)TIM7_BASEADDR)
#define CAN1	((CAN_type *)CAN1_BASEADDR)
#define CAN2	((CAN_type *)CAN2_BASEADDR)

/*clock enable macros for GPIOs*/
#define GPIOA_CLKEN   (RCC -> AHB1ENR |= (1 << 0))
#define GPIOB_CLKEN   (RCC -> AHB1ENR |= (1 << 1))
#define GPIOC_CLKEN   (RCC -> AHB1ENR |= (1 << 2))
#define GPIOD_CLKEN   (RCC -> AHB1ENR |= (1 << 3))
#define GPIOE_CLKEN   (RCC -> AHB1ENR |= (1 << 4))
#define GPIOF_CLKEN   (RCC -> AHB1ENR |= (1 << 5))
#define GPIOG_CLKEN   (RCC -> AHB1ENR |= (1 << 6))
#define GPIOH_CLKEN   (RCC -> AHB1ENR |= (1 << 7))


/*clock enable macros for I2Cs*/
#define I2C1_CLKEN()    (RCC -> APB1ENR |= (1 << 21))
#define I2C2_CLKEN()   (RCC -> APB1ENR  |= (1 << 22))
#define I2C3_CLKEN()    (RCC -> APB1ENR |= (1 << 23))


/*clock enable macros for SPIs*/
#define SPI1_CLKEN()    (RCC -> APB2ENR |= (1 << 12))
#define SPI2_CLKEN()    (RCC -> APB1ENR |= (1 << 14))
#define SPI3_CLKEN()    (RCC -> APB1ENR |= (1 << 15))
#define SPI4_CLKEN()    (RCC -> APB2ENR |= (1 << 13))


/*clock enable macros for USARTs*/
#define USART1_CLKEN()    (RCC -> APB2ENR  |= (1 << 4))
#define USART2_CLKEN()     (RCC -> APB1ENR |= (1 << 17))
#define USART3_CLKEN()     (RCC -> APB1ENR |= (1 << 18))
#define UART4_CLKEN()     (RCC -> APB1ENR  |= (1 << 19))
#define UART5_CLKEN()     (RCC -> APB1ENR  |= (1 << 20))
#define USART6_CLKEN()    (RCC -> APB2ENR  |= (1 << 5))

/*clock enable macros for SYSCFGs*/
#define SYSCFG_CLKEN()    (RCC -> APB2ENR |= (1 << 14))
/*clock enable macros for EXTI*/
#define EXTI_CLKEN()    (RCC -> APB2ENR |= (1 << 14))


/*clock enable macros for Timers*/
#define TIM6_CLKEN()		(RCC-> APB1ENR |= (1 << 4))
#define TIM7_CLKEN()		(RCC-> APB1ENR |= (1 << 5))


/*clock disable macros for GPIOs*/
#define GPIOA_CLKDI   (RCC -> AHB1ENR &= ~(1 << 0))
#define GPIOB_CLKDI   (RCC -> AHB1ENR &= ~(1 << 1))
#define GPIOC_CLKDI   (RCC -> AHB1ENR &= ~(1 << 2))
#define GPIOD_CLKDI   (RCC -> AHB1ENR &= ~(1 << 3))
#define GPIOE_CLKDI   (RCC -> AHB1ENR &= ~(1 << 4))
#define GPIOF_CLKDI   (RCC -> AHB1ENR &= ~(1 << 5))
#define GPIOG_CLKDI   (RCC -> AHB1ENR &= ~(1 << 6))
#define GPIOH_CLKDI   (RCC -> AHB1ENR &= ~(1 << 7))


/*clock disable macros for I2Cs*/
#define I2C1_CLKDI()    (RCC -> APB1ENR &= ~(1 << 21))
#define I2C2_CLKDI()    (RCC -> APB1ENR &= ~(1 << 22))
#define I2C3_CLKDI()    (RCC -> APB1ENR &= ~(1 << 23))


/*clock disable macros for SPIs*/
#define SPI1_CLKDI()    (RCC -> APB2ENR &= ~(1 << 12))
#define SPI2_CLKDI()    (RCC -> APB1ENR &= ~(1 << 14))
#define SPI3_CLKDI()    (RCC -> APB1ENR &= ~(1 << 15))
#define SPI4_CLKDI()    (RCC -> APB2ENR &= ~(1 << 13))


/*clock disable macros for USARTs*/
#define USART1_CLKDI()    (RCC -> APB2ENR |= (1 << 4))
#define USART2_CLKDI()     (RCC -> APB1ENR |= (1 << 17))
#define USART3_CLKDI()     (RCC -> APB1ENR |= (1 << 18))
#define UART4_CLKDI()     (RCC -> APB1ENR |= (1 << 19))
#define UART5_CLKDI()     (RCC -> APB1ENR |= (1 << 20))
#define USART6_CLKDI()    (RCC -> APB2ENR |= (1 << 5))


/*clock disable macros for SYSCFGs*/
#define SYSCFG1_CLKDI    (RCC -> APB2ENR &= ~(1 << 14))

/*clock disable macros for Timers*/
#define TIM6_CLKDI()		(RCC-> APB1ENR &= ~(1 << 4))
#define TIM7_CLKDI()		(RCC-> APB1ENR &= ~(1 << 5))

/*macros for resetting of GPIO PORTS*/
#define GPIOA_RESET       do{RCC->AHB1RSTR |= (1 << 0); RCC->AHB1RSTR &= ~(1 << 0);}while(0)
#define GPIOB_RESET       do{RCC->AHB1RSTR |= (1 << 1); RCC->AHB1RSTR &= ~(1 << 1);}while(0)
#define GPIOC_RESET       do{RCC->AHB1RSTR |= (1 << 2); RCC->AHB1RSTR &= ~(1 << 2);}while(0)
#define GPIOD_RESET       do{RCC->AHB1RSTR |= (1 << 3); RCC->AHB1RSTR &= ~(1 << 3);}while(0)
#define GPIOE_RESET       do{RCC->AHB1RSTR |= (1 << 4); RCC->AHB1RSTR &= ~(1 << 4);}while(0)
#define GPIOF_RESET       do{RCC->AHB1RSTR |= (1 << 5); RCC->AHB1RSTR &= ~(1 << 5);}while(0)
#define GPIOG_RESET       do{RCC->AHB1RSTR |= (1 << 6); RCC->AHB1RSTR &= ~(1 << 6);}while(0)
#define GPIOH_RESET       do{RCC->AHB1RSTR |= (1 << 7); RCC->AHB1RSTR &= ~(1 << 7);}while(0)

/***********************************************************************************************
*              bit position definition macros for RCC
************************************************************************************************/
/*CR register*/
#define RCC_CR_HSION		0
#define RCC_CR_HSRDY		1
#define RCC_CR_HSITRIM		3
#define RCC_CR_HSICAL		8
#define RCC_CR_HSEON		16
#define RCC_CR_HSERDY		17
#define RCC_CR_HSEVYP		18
#define RCC_CR_CSSON		19
#define RCC_CR_PLLON		24
#define RCC_CR_PLLRDY		25
#define RCC_CR_PLLI2SON		26
#define RCC_CR_PLLI2SRDY	27
#define RCC_CR_PLLSAION		28
#define RCC_CR_PLLSAIRDY	29

/*PLLCFGR*/
#define RCC_PLLCFGR_PLLM	0
#define RCC_PLLCFGR_PLLN	6
#define RCC_PLLCFGR_PLLP	16
#define RCC_PLLCFGR_PLLSRC	22
#define RCC_PLLCFGR_PLLQ	24
#define RCC_PLLCFGR_PLLR	28

/*CFGR*/
#define RCC_CFGR_SW			0
#define RCC_CFGR_SWS		2
#define RCC_CFGR_HPRE		4
#define RCC_CFGR_PPRE1		10
#define RCC_CFGR_PPRE2		13
#define RCC_CFGR_RTCPRE		16
#define RCC_CFGR_MCO1		21
#define RCC_CFGR_MCO1PRE	24
#define RCC_CFGR_MCO2PRE	27
#define RCC_CFGR_MCO2		30

/*CIR*/
#define RCC_CIR_LSIRDYF		0
#define RCC_CIR_LSERDYF		1
#define RCC_CIR_HSIRDYF		2
#define RCC_CIR_HSERDYF		3
#define RCC_CIR_PLLRDYF		4
#define RCC_CIR_PLLI2SRDYF	5
#define RCC_CIR_PLLSAIRDYF	6
#define RCC_CIR_CSSF		7
#define RCC_CIR_LSIRDYIE	8
#define RCC_CIR_LSERDYIE	9
#define RCC_CIR_HSIRDYIE	10
#define RCC_CIR_HSERDYIE	11
#define RCC_CIR_PLLRDYIE	12
#define RCC_CIR_PLLI2SDGYIE	13
#define RCC_CIR_PLLSAIRDYIE	14
#define RCC_CIR_LSIRDYC		16
#define RCC_CIR_LSERDYC		17
#define RCC_CIR_HSIRDYC		18
#define RCC_CIR_HSERDYC		19
#define RCC_CIR_PLLRDYC		20
#define RCC_CIR_PLLI2SRDYC	21
#define RCC_CIR_PLLSIARDYC	22
#define RCC_CIR_CSSC		23

/*AHB1RSTR*/
#define RCC_AHB1RSTR_GPIOARST	0
#define RCC_AHB1RSTR_GPIOBRST	1
#define RCC_AHB1RSTR_GPIOCRST	2
#define RCC_AHB1RSTR_GPIODRST	3
#define RCC_AHB1RSTR_GPIOERST	4
#define RCC_AHB1RSTR_GPIOFRST	5
#define RCC_AHB1RSTR_GPIOGRST	6
#define RCC_AHB1RSTR_GPIOHRST	7
#define RCC_AHB1RSTR_CRCRST		12
#define RCC_AHB1RSTR_DMA1OARST	21
#define RCC_AHB1RSTR_DMA2ARST	22
#define RCC_AHB1RSTR_OTGHSRST	29

/*AHB2RSTR*/
#define RCC_AHB2RSTR_DCMIRST	0
#define RCC_AHB2RSTR_OTGFSRST	7

/*AHB3RSTR*/
#define RCC_AHB3RSTR_FMCRST		0
#define RCC_AHB3RSTR_QSPIRST	1

/*APB1RSTR*/
#define RCC_APB1RSTR_TIM2RST	0
#define RCC_APB1RSTR_TIM3RST	1
#define RCC_APB1RSTR_TIM4RST	2
#define RCC_APB1RSTR_TIM5RST	3
#define RCC_APB1RSTR_TIM6RST	4
#define RCC_APB1RSTR_TIM7RST	5
#define RCC_APB1RSTR_TIM12RST	6
#define RCC_APB1RSTR_TIM13RST	7
#define RCC_APB1RSTR_TIM14RST	8
#define RCC_APB1RSTR_WWDGRST	11
#define RCC_APB1RSTR_SPI2RST	14
#define RCC_APB1RSTR_SPI3RST	15
#define RCC_APB1RSTR_SPDIFRXRST	16
#define RCC_APB1RSTR_UART2RST	17
#define RCC_APB1RSTR_USART3RST	18
#define RCC_APB1RSTR_UART4RST	19
#define RCC_APB1RSTR_UART5RST	20
#define RCC_APB1RSTR_I2C1RST	21
#define RCC_APB1RSTR_I2C2RST	22
#define RCC_APB1RSTR_I2C3RST	23
#define RCC_APB1RSTR_FMPI2C1RST	24
#define RCC_APB1RSTR_CAN1RST	25
#define RCC_APB1RSTR_CAN2RST	26
#define RCC_APB1RSTR_CECRST		27
#define RCC_APB1RSTR_PWRRST		28
#define RCC_APB1RSTR_DACRST		29

/*APB2RSTR*/
#define RCC_APB2RSTR_TIM1RST	0
#define RCC_APB2RSTR_TIM8RST	1
#define RCC_APB2RSTR_USART1RST	4
#define RCC_APB2RSTR_USART6RST	5
#define RCC_APB2RSTR_ADCRST		8
#define RCC_APB2RSTR_SDIORST	11
#define RCC_APB2RSTR_SPI1RST	12
#define RCC_APB2RSTR_SPI4RST	13
#define RCC_APB2RSTR_SYSCFGRST	14
#define RCC_APB2RSTR_TIM9RST	16
#define RCC_APB2RSTR_TIM10RST	17
#define RCC_APB2RSTR_TIM11RST	18
#define RCC_APB2RSTR_SAI1RST	22
#define RCC_APB2RSTR_SAI2RST	23

/*AHB1ENR*/
#define RCC_AHB1ENR_GPIOAEN		0
#define RCC_AHB1ENR_GPIOBEN		1
#define RCC_AHB1ENR_GPIOCEN		2
#define RCC_AHB1ENR_GPIODEN		3
#define RCC_AHB1ENR_GPIOEEN		4
#define RCC_AHB1ENR_GPIOFEN		5
#define RCC_AHB1ENR_GPIOGEN		6
#define RCC_AHB1ENR_GPIOHEN		7
#define RCC_AHB1ENR_CRCEN		12
#define RCC_AHB1ENR_BKPSRAMEN	18
#define RCC_AHB1ENR_DMA1OAEN	21
#define RCC_AHB1ENR_DMA2AEN		22
#define RCC_AHB1ENR_OTGHSEN		29
#define RCC_AHB1ENR_OTGHSULPIEN 30

/*AHB2ENR*/
#define RCC_AHB2ENR_DCMIEN	0
#define RCC_AHB2ENR_OTGFSEN	7

/*AHB3ENR*/
#define RCC_AHB2ENR_FMCEN	0
#define RCC_AHB2ENR_QSPIEN	1

/*APB1ENR*/
#define RCC_APB1ENR_TIM2EN		0
#define RCC_APB1ENR_TIM3EN		1
#define RCC_APB1ENR_TIM4EN		2
#define RCC_APB1ENR_TIM5EN		3
#define RCC_APB1ENR_TIM6EN		4
#define RCC_APB1ENR_TIM7EN		5
#define RCC_APB1ENR_TIM12EN		6
#define RCC_APB1ENR_TIM13EN		7
#define RCC_APB1ENR_TIM14EN		8
#define RCC_APB1ENR_WWDGEN		11
#define RCC_APB1ENR_SPI2EN		14
#define RCC_APB1ENR_SPI3EN		15
#define RCC_APB1ENR_SPDIFRXEN	16
#define RCC_APB1ENR_UART2EN		17
#define RCC_APB1ENR_USART3EN	18
#define RCC_APB1ENR_UART4EN		19
#define RCC_APB1ENR_UART5EN		20
#define RCC_APB1ENR_I2C1EN		21
#define RCC_APB1ENR_I2C2EN		22
#define RCC_APB1ENR_I2C3EN		23
#define RCC_APB1ENR_FMPI2C1EN	24
#define RCC_APB1ENR_CAN1EN		25
#define RCC_APB1ENR_CAN2EN		26
#define RCC_APB1ENR_CECEN		27
#define RCC_APB1ENR_PWREN		28
#define RCC_APB1ENR_DACEN		29

/*APB2ENR*/
#define RCC_APB2ENR_TIM1EN		0
#define RCC_APB2ENR_TIM8EN		1
#define RCC_APB2ENR_USART1EN	4
#define RCC_APB2ENR_USART6EN	5
#define RCC_APB2ENR_ADC1EN		8
#define RCC_APB2ENR_ADC2EN		9
#define RCC_APB2ENR_ADC3EN		10
#define RCC_APB2ENR_SDIOEN		11
#define RCC_APB2ENR_SPI1EN		12
#define RCC_APB2ENR_SPI4EN		13
#define RCC_APB2ENR_SYSCFGEN	14
#define RCC_APB2ENR_TIM9EN		16
#define RCC_APB2ENR_TIM10EN		17
#define RCC_APB2ENR_TIM11EN		18
#define RCC_APB2ENR_SAI1EN		22
#define RCC_APB2ENR_SAI2EN		23


/*CSR*/
#define RCC_CSR_LSION		0
#define RCC_CSR_LSIRDY		1
#define RCC_CSR_RMVF		24
#define RCC_CSR_BORRSTF		25
#define RCC_CSR_PINRSTF		26
#define RCC_CSR_PORRSTF		27
#define RCC_CSR_SFTRSTF		28
#define RCC_CSR_IWDGRSTF	29
#define RCC_CSR_WWDGRSTF	30
#define RCC_CSR_LPWRRSTF	31

/*PLLSAICFGR*/
#define RCC_PLLSAICFGR_PLLI2SMI		0
#define RCC_PLLSAICFGR_PLLI2SN		6
#define RCC_PLLSAICFGR_PLLI2SP		16
#define RCC_PLLSAICFGR_PLLI2SQ		24
#define RCC_PLLSAICFGR_PLLI2SR		28

/*PLLSAICFGR*/
#define RCC_PLLSAICFGR_PLLSAIMI		0
#define RCC_PLLSAICFGR_PLLSAIN		6
#define RCC_PLLSAICFGR_PLLSAIP		16
#define RCC_PLLSAICFGR_PLLSAIQ		24
#define RCC_PLLSAICFGR_PLLSAIR		28

/*DCKCFGR*/
#define RCC_DCKCFGR_PLLI2SDIVQ		0
#define RCC_DCKCFGR_PLLSAIDIVQ		8
#define RCC_DCKCFGR_PLLSAISRC		20
#define RCC_DCKCFGR_PLLI2CSRC		22
#define RCC_DCKCFGR_TIMPRE			24
#define RCC_DCKCFGR_I2S1SRC			25
#define RCC_DCKCFGR_I2S2SRC			27

/*CKGATENR*/
#define RCC_CKGATENR_AHB2APB1_CKEN	0
#define RCC_CKGATENR_AHB2APB2_CKEN	1
#define RCC_CKGATENR_CM4DBG_CKEN	2
#define RCC_CKGATENR_SPARE_CKEN		3
#define RCC_CKGATENR_SRAM_CKEN		4
#define RCC_CKGATENR_FLITF_CKEN		5
#define RCC_CKGATENR_RCC_CKEN		6

/*DCKCFGR2*/
#define RCC_DCKCFGR2_FMPI2C1SEL		22
#define RCC_DCKCFGR2_CECSEL			26
#define RCC_DCKCFGR2_CK59MSEL		27
#define RCC_DCKCFGR2_SDIOSEL		28
#define RCC_DCKCFGR2_SPDIFRX		29
/***********************************************************************************************
*              bit position definition macros for SPI
************************************************************************************************/
/*CR1 register*/
#define SPI_CR1_CPHA     0
#define SPI_CR1_CPOL     1
#define SPI_CR1_MSTR     2
#define SPI_CR1_BR       3
#define SPI_CR1_SPE      6
#define SPI_CR1_LSBFIRST 7
#define SPI_CR1_SSI      8
#define SPI_CR1_SSM      9
#define SPI_CR1_RXONLY   10
#define SPI_CR1_DFF      11
#define SPI_CR1_CRCNEXT  12
#define SPI_CR1_CRCEN    13
#define SPI_CR1_BIDIOE   14
#define SPI_CR1_BIDIMODE 15

/*CR2 register*/
#define SPI_CR2_RXDMAEN   0
#define SPI_CR2_TXDMAEN   1
#define SPI_CR2_SSOE      2
#define SPI_CR2_FRF       4
#define SPI_CR2_ERRIE     5
#define SPI_CR2_RXNEIE    6
#define SPI_CR2_TXEIE     7

/*SR register*/
#define SPI_SR_RXNE       0
#define SPI_SR_TXE        1
#define SPI_SR_CHSIDE     2
#define SPI_SR_UDR        3
#define SPI_SR_CRCERR     4
#define SPI_SR_MODF       5
#define SPI_SR_OVR        6
#define SPI_SR_BSY        7
#define SPI_SR_FRE        8

/***********************************************************************************************
*              bit position definition macros for I2C
************************************************************************************************/
/*CR1 register*/
#define I2C_CR1_PE        0
#define I2C_CR1_SMBUS     1
#define I2C_CR1_SMBTYPE   3
#define I2C_CR1_ENARP     4
#define I2C_CR1_ENPEC     5
#define I2C_CR1_ENGC      6
#define I2C_CR1_NOSTRETCH 7
#define I2C_CR1_START     8
#define I2C_CR1_STOP      9
#define I2C_CR1_ACK       10
#define I2C_CR1_POS       11
#define I2C_CR1_PEC       12
#define I2C_CR1_ALERT     13
#define I2C_CR1_SWRST     15


/*CR2 Register*/
#define I2C_CR2_FREQ      0
#define I2C_CR2_INTERREN  8
#define I2C_CR2_ITEVTEN   9
#define I2C_CR2_ITBUFEN   10
#define I2C_CR2_DMAEN     11
#define I2C_CR2_LAST      12

/*SR1 Register*/
#define I2C_SR1_SB        0
#define I2C_SR1_ADDR      1
#define I2C_SR1_BTF       2
#define I2C_SR1_ADD10     3
#define I2C_SR1_STOPF     4
#define I2C_SR1_RxNE      6
#define I2C_SR1_TxE       7
#define I2C_SR1_BERR      8
#define I2C_SR1_ARLO      9
#define I2C_SR1_AF        10
#define I2C_SR1_OVR       11
#define I2C_SR1_PECERR    12
#define I2C_SR1_TIMEOUT   14
#define I2C_SR1_SMBALERT  15

/*OAR1 Registers*/
#define I2C_OAR1_ADD0     0
#define I2C_OAR1_ADD      1
#define I2C_OAR1_ADDMODE  15
/*SR2 Registers*/
#define I2C_SR2_MSL       0
#define I2C_SR2_BUSY      1
#define I2C_SR2_TRA       2
#define I2C_SR2_GENCALL   3
#define I2C_SR2_SSMBDEF   4
#define I2C_SR2_DUALF     6
#define I2C_SR2_TxE       7
#define I2C_SR2_PEC       8

/*CCR register*/
#define I2C_CCR_CCR       0
#define I2C_CCR_DUTY      14
#define I2C_CCR_F_S       15

/***********************************************************************************************
*              bit position definition macros for UASRT
************************************************************************************************/

/*SR register*/
#define USART_SR_PE       0
#define USART_SR_FE       1
#define USART_SR_NF       2
#define USART_SR_ORE      3
#define USART_SR_IDLE     4
#define USART_SR_RXNE     5
#define USART_SR_TC       6
#define USART_SR_TXE      7
#define USART_SR_LBD      8
#define USART_SR_CTS      9

/*DR register*/
#define USART_DR_DR       0

/*BRR register*/
#define USART_BRR_DIV_Fraction    0
#define USART_BRR_DIV_Mantissa    4

/*CR1 register*/
#define USART_CR1_SBK     0
#define USART_CR1_RWU     1
#define USART_CR1_RE      2
#define USART_CR1_TE      3
#define USART_CR1_IDLEIE  4
#define USART_CR1_RXNEIE  5
#define USART_CR1_TCIE    6
#define USART_CR1_TXEIE   7
#define USART_CR1_PEIE    8
#define USART_CR1_PS      9
#define USART_CR1_PCE     10
#define USART_CR1_WAKE    11
#define USART_CR1_M       12
#define USART_CR1_UE      13
#define USART_CR1_OVER8   15

/*CR2 register*/
#define USART_CR2_ADD     0
#define USART_CR2_LBDL    5
#define USART_CR2_LBDIE   6
#define USART_CR2_RES     7
#define USART_CR2_LBCL    8
#define USART_CR2_CPHA    9
#define USART_CR2_CPOL    10
#define USART_CR2_CLKEN   11
#define USART_CR2_STOP    12
#define USART_CR2_LINEN   14

/*CR3 register*/
#define USART_CR3_EIE     0
#define USART_CR3_IREN    1
#define USART_CR3_IRLP    1
#define USART_CR3_HDSEL   3
#define USART_CR3_NACK    4
#define USART_CR3_SCEN    5
#define USART_CR3_DMAR    6
#define USART_CR3_DMAT    7
#define USART_CR3_RTSE    8
#define USART_CR3_CTSE    9
#define USART_CR3_CTSIE   10
#define USART_CR3_ONEBIT  11

/*GTPR register*/
#define USART_GTPR_PSC     0
#define USART_GTPR_GT      8


/***********************************************************************************************
*              bit position definition macros for Basic TIMER
************************************************************************************************/

/*CR1*/
#define TIM_CR1_CEN		0
#define TIM_CR1_UDIS	1
#define TIM_CR1_URS		2
#define TIM_CR1_OPM		3
#define TIM_CR1_ARPE	7

/*CR2*/
#define TIM_CR2_MSM		4

/*DIER*/
#define TIM_DIER_UIE	0
#define TIM_DIER_UDE	8

/*SR*/
#define TIM_SR_UIF		0

/*EGR*/
#define TIM_EGR_UG		0

/*CNT*/
#define TIM_CNT_CNT		0

/*PSC*/
#define TIM_PSC_PSC		0

/*ARR*/
#define TIM_ARR_ARR		0

/***********************************************************************************************
*              bit position definition macros for CAN
************************************************************************************************/
#define CAN_MCR_
/***********************************************************************************************
*                                     IRQ numbers
************************************************************************************************/
#define IRQ_EXTI0      			6
#define IRQ_EXTI1      			7
#define IRQ_EXTI2      			8
#define IRQ_EXTI3      			9
#define IRQ_EXTI4      			10
#define IRQ_DMA1_Stream0 		11
#define IRQ_DMA1_Stream1 		12
#define IRQ_DMA1_Stream2 		13
#define IRQ_DMA1_Stream3 		14
#define IRQ_DMA1_Stream4 		15
#define IRQ_DMA1_Stream5 		16
#define IRQ_DMA1_Stream6 		17
#define IRQ_ADC          		18
#define IRQ_CAN1_TX      		19
#define IRQ_CAN1_RX0      		20
#define IRQ_CAN1_RX1      		21
#define IRQ_CAN1_SCE      		22
#define IRQ_EXTI5_9       		23
#define IRQ_TIM1_BRK_TIM9  		24
#define IRQ_TIM1_UP_TIM10  		25
#define IRQ_TIM1_TRG_COM_TIM11  26
#define IRQ_TIM1_CC  			27
#define IRQ_TIM2     			28
#define IRQ_TIM3     			29
#define IRQ_TIM4     			30
#define IRQ_I2C1_EV  			31
#define IRQ_I2C1_ER  			32
#define IRQ_I2C2_EV  			33
#define IRQ_I2C2_ER  			34
#define IRQ_SPI1  				35
#define IRQ_SPI2  				36
#define IRQ_USART1  			37
#define IRQ_USART2  			38
#define IRQ_USART3  			39
#define IRQ_EXTI10_15  			40
#define IRQ_RTC_Alarm  			41
#define IRQ_OTG_FS_WKUP  		42
#define IRQ_TIM8_BRK_TIM12  	43
#define IRQ_TIM8_UP_TIM13  		44
#define IRQ_TIM8_TRG_COM_TIM14  45
#define IRQ_TIM8_CC  			46
#define IRQ_DMA1_Stream7  		47
#define IRQ_FMC     			48
#define IRQ_SDIO    			49
#define IRQ_TIM5    			50
#define IRQ_SPI3    			51
#define IRQ_UART4   			52
#define IRQ_UART5   			53
#define IRQ_TIM6_DAC 			54
#define IRQ_TIM7   				55
#define IRQ_DMA2_Stream0 		56
#define IRQ_DMA2_Stream1 		57
#define IRQ_DMA2_Stream2 		58
#define IRQ_DMA2_Stream3 		59
#define IRQ_DMA2_Stream4 		60
#define IRQ_CAN2_TX    			63
#define IRQ_CAN2_RX0    		64
#define IRQ_CAN2_RX1    		65
#define IRQ_CAN2_CSE    		66
#define IRQ_OTG_FS       		67
#define IRQ_DMA2_Stream5  		68
#define IRQ_DMA2_Stream6  		69
#define IRQ_DMA2_Stream7  		70
#define IRQ_USART6       		71
#define IRQ_I2C3_EV  			72
#define IRQ_I2C3_ER  			73
#define IRQ_OTG_HS_EP1_OUT   	74
#define IRQ_OTG_HS_EP1_IN   	75
#define IRQ_OTG_HS_WKUP    		76
#define IRQ_OTG_HS   			77
#define IRQ_DCMI   				78
#define IRQ_FPU    				81
#define IRQ_SPI4    			84
#define IRQ_SAI1   				87
#define IRQ_SAI2   				91
#define IRQ_QUADSPI    			92
#define IRQ_HDMI_CEC   			93
#define IRQ_SPDIF_RX   			94
#define IRQ_FMPI2C1    			95
#define IRQ_FMPI2C1_ERROR  		96

/*some private macros*/
#define ENABLE     1
#define DISABLE    0
#define SET        ENABLE
#define RESET      DISABLE
#define NO_PI_BITS_IMPLEMENTED   4    /*higher four bits of the byte are accessible*/
#endif /* STM32F446RE_STMF446RE_H_ */
