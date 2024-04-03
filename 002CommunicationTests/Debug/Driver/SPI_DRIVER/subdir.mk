################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Driver/SPI_DRIVER/SPI_driver.c 

OBJS += \
./Driver/SPI_DRIVER/SPI_driver.o 

C_DEPS += \
./Driver/SPI_DRIVER/SPI_driver.d 


# Each subdirectory must supply rules for building sources it contributes
Driver/SPI_DRIVER/%.o Driver/SPI_DRIVER/%.su: ../Driver/SPI_DRIVER/%.c Driver/SPI_DRIVER/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu18 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F446RETx -DNUCLEO_F446RE -c -I"E:/MCU1/005GPIO_Driver/Driver/GPIO_DRIVERS" -I"E:/MCU1/005GPIO_Driver/Driver/inc" -I"E:/MCU1/005GPIO_Driver/Driver/SPI_DRIVER" -I"E:/MCU1/005GPIO_Driver/BSP" -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Driver-2f-SPI_DRIVER

clean-Driver-2f-SPI_DRIVER:
	-$(RM) ./Driver/SPI_DRIVER/SPI_driver.d ./Driver/SPI_DRIVER/SPI_driver.o ./Driver/SPI_DRIVER/SPI_driver.su

.PHONY: clean-Driver-2f-SPI_DRIVER

