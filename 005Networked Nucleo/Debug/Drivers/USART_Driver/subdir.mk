################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/USART_Driver/USART_driver.c 

OBJS += \
./Drivers/USART_Driver/USART_driver.o 

C_DEPS += \
./Drivers/USART_Driver/USART_driver.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/USART_Driver/%.o Drivers/USART_Driver/%.su: ../Drivers/USART_Driver/%.c Drivers/USART_Driver/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu18 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F446RETx -DNUCLEO_F446RE -c -I"E:/MCU1/007CAN with UltraSonic/Drivers/GPIO_DRIVERS" -I"E:/MCU1/007CAN with UltraSonic/Drivers/RTC" -I"E:/MCU1/007CAN with UltraSonic/Drivers/Timer_Driver" -I"E:/MCU1/007CAN with UltraSonic/Drivers/USART_Driver" -I"E:/MCU1/007CAN with UltraSonic/Drivers/I2C_Driver" -I"E:/MCU1/007CAN with UltraSonic/Drivers/stm32f446re" -I"E:/MCU1/007CAN with UltraSonic/Drivers/SPI_DRIVER" -I"E:/MCU1/007CAN with UltraSonic/BSP" -I../Inc -I"E:/MCU1/007CAN with UltraSonic/Drivers/RCC_Driver" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-USART_Driver

clean-Drivers-2f-USART_Driver:
	-$(RM) ./Drivers/USART_Driver/USART_driver.d ./Drivers/USART_Driver/USART_driver.o ./Drivers/USART_Driver/USART_driver.su

.PHONY: clean-Drivers-2f-USART_Driver

