################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/RCC_Driver/RCC_driver.c 

OBJS += \
./Drivers/RCC_Driver/RCC_driver.o 

C_DEPS += \
./Drivers/RCC_Driver/RCC_driver.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/RCC_Driver/%.o Drivers/RCC_Driver/%.su: ../Drivers/RCC_Driver/%.c Drivers/RCC_Driver/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu18 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F446RETx -DNUCLEO_F446RE -c -I"E:/MCU1/006UltraSonic/Drivers/GPIO_DRIVERS" -I"E:/MCU1/006UltraSonic/Drivers/Timer_Driver" -I"E:/MCU1/006UltraSonic/Drivers/USART_Driver" -I"E:/MCU1/006UltraSonic/Drivers/I2C_Driver" -I"E:/MCU1/006UltraSonic/Drivers/stm32f446re" -I"E:/MCU1/006UltraSonic/Drivers/SPI_DRIVER" -I"E:/MCU1/006UltraSonic/BSP" -I../Inc -I"E:/MCU1/006UltraSonic/Drivers/RCC_Driver" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-RCC_Driver

clean-Drivers-2f-RCC_Driver:
	-$(RM) ./Drivers/RCC_Driver/RCC_driver.d ./Drivers/RCC_Driver/RCC_driver.o ./Drivers/RCC_Driver/RCC_driver.su

.PHONY: clean-Drivers-2f-RCC_Driver

