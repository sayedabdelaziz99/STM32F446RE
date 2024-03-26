################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/Timer_Driver/Timer_Driver.c 

OBJS += \
./Drivers/Timer_Driver/Timer_Driver.o 

C_DEPS += \
./Drivers/Timer_Driver/Timer_Driver.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/Timer_Driver/%.o Drivers/Timer_Driver/%.su: ../Drivers/Timer_Driver/%.c Drivers/Timer_Driver/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu18 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F446RETx -DNUCLEO_F446RE -c -I"E:/MCU1/006UltraSonic/Drivers/GPIO_DRIVERS" -I"E:/MCU1/006UltraSonic/Drivers/Timer_Driver" -I"E:/MCU1/006UltraSonic/Drivers/USART_Driver" -I"E:/MCU1/006UltraSonic/Drivers/I2C_Driver" -I"E:/MCU1/006UltraSonic/Drivers/stm32f446re" -I"E:/MCU1/006UltraSonic/Drivers/SPI_DRIVER" -I"E:/MCU1/006UltraSonic/BSP" -I../Inc -I"E:/MCU1/006UltraSonic/Drivers/RCC_Driver" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-Timer_Driver

clean-Drivers-2f-Timer_Driver:
	-$(RM) ./Drivers/Timer_Driver/Timer_Driver.d ./Drivers/Timer_Driver/Timer_Driver.o ./Drivers/Timer_Driver/Timer_Driver.su

.PHONY: clean-Drivers-2f-Timer_Driver

