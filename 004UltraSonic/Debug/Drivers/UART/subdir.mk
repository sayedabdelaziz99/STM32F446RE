################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/UART/USART_driver.c 

OBJS += \
./Drivers/UART/USART_driver.o 

C_DEPS += \
./Drivers/UART/USART_driver.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/UART/%.o Drivers/UART/%.su: ../Drivers/UART/%.c Drivers/UART/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu18 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F446RETx -DNUCLEO_F446RE -c -I"E:/MCU1/005STM32_Drivers/Drivers/GPIO_DRIVERS" -I"E:/MCU1/005STM32_Drivers/Drivers/UART" -I"E:/MCU1/005STM32_Drivers/Drivers/I2C_Driver" -I"E:/MCU1/005STM32_Drivers/Drivers/stm32f446re" -I"E:/MCU1/005STM32_Drivers/Drivers/SPI_DRIVER" -I"E:/MCU1/005STM32_Drivers/BSP" -I../Inc -I"E:/MCU1/005STM32_Drivers/Drivers/RCC_Driver" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Drivers-2f-UART

clean-Drivers-2f-UART:
	-$(RM) ./Drivers/UART/USART_driver.d ./Drivers/UART/USART_driver.o ./Drivers/UART/USART_driver.su

.PHONY: clean-Drivers-2f-UART

