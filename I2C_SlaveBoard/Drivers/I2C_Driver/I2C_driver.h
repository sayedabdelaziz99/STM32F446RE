/*
 * I2C_driver.h
 *
 *  Created on: Feb 2, 2024
 *      Author: Sayed
 */

#ifndef I2C_DRIVER_I2C_DRIVER_H_
#define I2C_DRIVER_I2C_DRIVER_H_

typedef struct{
  uint32_t I2C_SCLSpeed;     /*@SCL Speed*/
  uint8_t I2C_DeviceAddress; /*user specific*/
  uint8_t I2C_ACKControl;   /*@ACK control*/
  uint8_t I2C_FMDutyCycle;  /*@FM Duty Cycle*/
  uint8_t I2C_AddressMode;  /*@address modes*/
}I2C_config;

typedef struct{
  I2C_type  *pI2Cx;
  I2C_config I2C_Config;
}I2C_Handle;


/*
 * @SCL speed
 * possible speeds of the clock
 */
#define I2C_SCL_SM 100000       /*standered mode*/
#define I2C_SCL_FM 400000		/*fast mode*/

/*
 * @ACK control
 * ack conrtol macros
 */
#define I2C_ACK_ENABLE    1
#define I2C_ACK_DISABLE   0

/*
 * @FM Duty Cycle
 * duty cycle values
 */
#define I2C_FM_DUTY_2     0
#define I2C_FM_DUTY_16_9  1

/*
 * @address modes
 * possible addressing modes in i2c
 */
#define I2C_AddressMode_7bit   0
#define I2C_AddressMode_10bit  1

/*
 * flags macros
 */
#define I2C_FLAG_SB       (1 << 0)
#define I2C_FLAG_ADDR     (1 << 1)
#define I2C_FLAG_BTF      (1 << 2)
#define I2C_FLAG_ADD10    (1 << 3)
#define I2C_FLAG_STOPF    (1 << 4)
#define I2C_FLAG_RXNE     (1 << 6)
#define I2C_FLAG_TxE      (1 << 7)
#define I2C_BERR_FLAG     (1 << 8)
#define I2C_ARLO_FLAG     (1 << 9)
#define I2C_AF_FLAG       (1 << 10)
#define I2C_OVR_FLAG      (1 << 11)
#define I2C_PECERR_FLAG   (1 << 12)
#define I2C_TIMEOUT_FLAG  (1 << 14)
#define I2C_SMBALERT_FLAG (1 << 15)





void I2C_Enable(I2C_type *pI2Cx, uint8_t EnorDi);
void I2C_CLKCNT(I2C_type *pI2Cx, uint8_t EnorDi);
void I2C_Init(I2C_Handle *pI2CHandle);
void I2C_DeInit(I2C_type *pI2Cx);
uint8_t I2C_GetFlagStatus(I2C_type *pI2Cx ,uint8_t FlagName);
void I2C_MasterSendData(I2C_Handle *pI2CHandle, uint8_t *pTxBuffer, uint8_t len, uint8_t SlaveAddress);
void I2C_MasterRecieveData(I2C_Handle *pI2CHandle, uint8_t *pRxBuffer, uint8_t Len, uint8_t SlaveAddress);
void I2C_SlaveSendData(I2C_Handle *pI2CHandle, uint8_t *pTxBuffer, uint8_t Len);
void I2C_SlaveRecieveData(I2C_Handle *pI2CHandle);
void I2C_IRQInterruptConfig(uint8_t IRQNumber, uint8_t ENorDI);
void I2C_IRQPriorityConfig(uint8_t IRQNumber, uint32_t IRQPriority);

#endif /* I2C_DRIVER_I2C_DRIVER_H_ */
