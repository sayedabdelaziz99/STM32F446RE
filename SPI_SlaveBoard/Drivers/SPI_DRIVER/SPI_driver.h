/*
 * SPI_driver.h
 *
 *  Created on: Jan 29, 2024
 *      Author: Sayed
 */

#ifndef INC_SPI_DRIVER_H_
#define INC_SPI_DRIVER_H_
#include "STMF446RE.h"


typedef struct{
	uint8_t  SPI_ModeConfig;   /*@ModeConfig*/
	uint8_t  SPI_BusConfig;    /*@BusConfig*/
	uint8_t  SPI_SclkSpeed;    /*@SclkSPeed*/
	uint8_t  SPI_DFF;		   /*@DFF*/
	uint8_t  SPI_COPL;         /*@CPOL*/
	uint8_t  SPI_CPHA;         /*@CPHA*/
	uint8_t  SPI_SSM;          /*@SSM*/
}SPI_config;

typedef struct{
	SPI_type   *pSPIx;
	SPI_config config;
}SPI_Handle;

/*
 * @ModeConfig
 */
#define SPI_MODE_MASTER   1
#define SPI_MODE_SLAVE    0

/*
 * @BusConfig
 */
#define SPI_BUS_FD     1
#define SPI_BUS_HD     2
#define SPI_BUS_S_RX   3

/*
 * @SclkSPeed
 */
#define SPI_ClckSPeed_DIV2   0
#define SPI_ClckSPeed_DIV4   1
#define SPI_ClckSPeed_DIV6   2
#define SPI_ClckSPeed_DIV8   3
#define SPI_ClckSPeed_DIV16  4
#define SPI_ClckSPeed_DIV32  5
#define SPI_ClckSPeed_DIV64  6
#define SPI_ClckSPeed_DIV128 7
#define SPI_ClckSPeed_DIV256 8

/*
 * @DFF
 */
#define SPI_DFF_8  0
#define SPI_DFF_16 1

/*
 * @CPOL
 */
#define SPI_CPOL_HIGH  1
#define SPI_CPOL_LOW   0

/*
 * @CPHA
 */
#define SPI_CPHA_HIGH  1
#define SPI_CPHA_LOW   0

/*
 * @SSM
 */
#define SPI_SSM_EN   1
#define SPI_SSM_DI   0


/*
 * flags macros
 */
#define SPI_RXNE_FLAG    (1 << 0)
#define SPI_TXE_FLAG     (1 << 1)
#define SPI_CHSIDE_FLAG  (1 << 2)
#define SPI_CRCERR_FLAG  (1 << 3)
#define SPI_MODF_FLAG    (1 << 4)
#define SPI_OVR_FLAG     (1 << 5)
#define SPI_BSY_FLAG     (1 << 6)
#define SPI_FRE_FLAG     (1 << 7)

void SSI_Enable(SPI_type *pSPIx, uint8_t EnorDi);
void SPI_Enable(SPI_type *pSPIx, uint8_t EnorDi);
void SPI_CLKCNT(SPI_type *pSPIx, uint8_t EnorDi);
void SPI_Init(SPI_Handle *pSPIHandle);
void SPI_DeInit(SPI_config *pSPIx);
uint8_t GetFlagStatus(SPI_type *pSPIx ,uint8_t FlagName);
void SPI_SendData(SPI_type *pSPIx, uint8_t *pTXBuffer, uint32_t Len);
void SPI_ReceiveData(SPI_type *pSPIx, uint8_t *pRXBuffer, uint32_t Len);
void SPI_IRQInterruptConfig(uint8_t IRQNumber, uint8_t ENorDI);
void SPI_IRQPriorityConfig(uint8_t IRQNumber, uint32_t IRQPriority);
void SPI_IRQHandling(SPI_Handle *pSPI_Handle);


#endif /* INC_SPI_DRIVER_H_ */
