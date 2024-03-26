################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/I2C_Driver/I2C_Driver.c 

OBJS += \
./Drivers/I2C_Driver/I2C_Driver.o 

C_DEPS += \
./Drivers/I2C_Driver/I2C_Driver.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/I2C_Driver/%.o Drivers/I2C_Driver/%.su: ../Drivers/I2C_Driver/%.c Drivers/I2C_Driver/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F446RETx -DNUCLEO_F446RE -c -I../Inc -I"E:/MCU1/USART_Board/BSP" -I"E:/MCU1/USART_Board/Drivers/GPIO_DRIVERS" -I"E:/MCU1/USART_Board/Drivers/I2C_Driver" -I"E:/MCU1/USART_Board/Drivers/RCC_Driver" -I"E:/MCU1/USART_Board/Drivers/SPI_DRIVER" -I"E:/MCU1/USART_Board/Drivers/stm32f446re" -I"E:/MCU1/USART_Board/Drivers/UART" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Drivers-2f-I2C_Driver

clean-Drivers-2f-I2C_Driver:
	-$(RM) ./Drivers/I2C_Driver/I2C_Driver.d ./Drivers/I2C_Driver/I2C_Driver.o ./Drivers/I2C_Driver/I2C_Driver.su

.PHONY: clean-Drivers-2f-I2C_Driver

