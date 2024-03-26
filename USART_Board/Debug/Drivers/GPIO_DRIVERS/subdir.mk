################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/GPIO_DRIVERS/GPIO_driver.c 

OBJS += \
./Drivers/GPIO_DRIVERS/GPIO_driver.o 

C_DEPS += \
./Drivers/GPIO_DRIVERS/GPIO_driver.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/GPIO_DRIVERS/%.o Drivers/GPIO_DRIVERS/%.su: ../Drivers/GPIO_DRIVERS/%.c Drivers/GPIO_DRIVERS/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F446RETx -DNUCLEO_F446RE -c -I../Inc -I"E:/MCU1/USART_Board/BSP" -I"E:/MCU1/USART_Board/Drivers/GPIO_DRIVERS" -I"E:/MCU1/USART_Board/Drivers/I2C_Driver" -I"E:/MCU1/USART_Board/Drivers/RCC_Driver" -I"E:/MCU1/USART_Board/Drivers/SPI_DRIVER" -I"E:/MCU1/USART_Board/Drivers/stm32f446re" -I"E:/MCU1/USART_Board/Drivers/UART" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Drivers-2f-GPIO_DRIVERS

clean-Drivers-2f-GPIO_DRIVERS:
	-$(RM) ./Drivers/GPIO_DRIVERS/GPIO_driver.d ./Drivers/GPIO_DRIVERS/GPIO_driver.o ./Drivers/GPIO_DRIVERS/GPIO_driver.su

.PHONY: clean-Drivers-2f-GPIO_DRIVERS

