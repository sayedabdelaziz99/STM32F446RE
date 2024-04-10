################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Driver/GPIO_DRIVERS/GPIO_driver.c 

OBJS += \
./Driver/GPIO_DRIVERS/GPIO_driver.o 

C_DEPS += \
./Driver/GPIO_DRIVERS/GPIO_driver.d 


# Each subdirectory must supply rules for building sources it contributes
Driver/GPIO_DRIVERS/%.o Driver/GPIO_DRIVERS/%.su: ../Driver/GPIO_DRIVERS/%.c Driver/GPIO_DRIVERS/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu18 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F446RETx -DNUCLEO_F446RE -c -I"E:/MCU1/005GPIO_Driver/Driver/GPIO_DRIVERS" -I"E:/MCU1/005GPIO_Driver/Driver/inc" -I"E:/MCU1/005GPIO_Driver/Driver/SPI_DRIVER" -I"E:/MCU1/005GPIO_Driver/BSP" -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Driver-2f-GPIO_DRIVERS

clean-Driver-2f-GPIO_DRIVERS:
	-$(RM) ./Driver/GPIO_DRIVERS/GPIO_driver.d ./Driver/GPIO_DRIVERS/GPIO_driver.o ./Driver/GPIO_DRIVERS/GPIO_driver.su

.PHONY: clean-Driver-2f-GPIO_DRIVERS

