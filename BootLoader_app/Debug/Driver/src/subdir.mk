################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Driver/src/GPIO_driver.c \
../Driver/src/SPI_driver.c \
../Driver/src/bsp.c 

OBJS += \
./Driver/src/GPIO_driver.o \
./Driver/src/SPI_driver.o \
./Driver/src/bsp.o 

C_DEPS += \
./Driver/src/GPIO_driver.d \
./Driver/src/SPI_driver.d \
./Driver/src/bsp.d 


# Each subdirectory must supply rules for building sources it contributes
Driver/src/%.o Driver/src/%.su: ../Driver/src/%.c Driver/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu18 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F446RETx -DNUCLEO_F446RE -c -I"E:/MCU1/005GPIO_Driver/Driver/inc" -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Driver-2f-src

clean-Driver-2f-src:
	-$(RM) ./Driver/src/GPIO_driver.d ./Driver/src/GPIO_driver.o ./Driver/src/GPIO_driver.su ./Driver/src/SPI_driver.d ./Driver/src/SPI_driver.o ./Driver/src/SPI_driver.su ./Driver/src/bsp.d ./Driver/src/bsp.o ./Driver/src/bsp.su

.PHONY: clean-Driver-2f-src

