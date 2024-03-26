################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../BSP/bsp.c 

OBJS += \
./BSP/bsp.o 

C_DEPS += \
./BSP/bsp.d 


# Each subdirectory must supply rules for building sources it contributes
BSP/%.o BSP/%.su: ../BSP/%.c BSP/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu18 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F446RETx -DNUCLEO_F446RE -c -I"E:/MCU1/I2C_SlaveBoard/Drivers/GPIO_DRIVERS" -I"E:/MCU1/I2C_SlaveBoard/Drivers/I2C_Driver" -I"E:/MCU1/I2C_SlaveBoard/Drivers/stm32f446re" -I"E:/MCU1/I2C_SlaveBoard/Drivers/SPI_DRIVER" -I"E:/MCU1/I2C_SlaveBoard/BSP" -I../Inc -I"E:/MCU1/I2C_SlaveBoard/Drivers/RCC_Driver" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-BSP

clean-BSP:
	-$(RM) ./BSP/bsp.d ./BSP/bsp.o ./BSP/bsp.su

.PHONY: clean-BSP

