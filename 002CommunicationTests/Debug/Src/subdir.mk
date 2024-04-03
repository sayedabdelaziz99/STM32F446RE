################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/009SPI_InterruptSendData.c \
../Src/syscalls.c \
../Src/sysmem.c 

OBJS += \
./Src/009SPI_InterruptSendData.o \
./Src/syscalls.o \
./Src/sysmem.o 

C_DEPS += \
./Src/009SPI_InterruptSendData.d \
./Src/syscalls.d \
./Src/sysmem.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o Src/%.su: ../Src/%.c Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu18 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F446RETx -DNUCLEO_F446RE -c -I"E:/MCU1/005STM32_Drivers/Drivers/GPIO_DRIVERS" -I"E:/MCU1/005STM32_Drivers/Drivers/USART_Driver" -I"E:/MCU1/005STM32_Drivers/Drivers/I2C_Driver" -I"E:/MCU1/005STM32_Drivers/Drivers/stm32f446re" -I"E:/MCU1/005STM32_Drivers/Drivers/SPI_DRIVER" -I"E:/MCU1/005STM32_Drivers/BSP" -I../Inc -I"E:/MCU1/005STM32_Drivers/Drivers/RCC_Driver" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Src

clean-Src:
	-$(RM) ./Src/009SPI_InterruptSendData.d ./Src/009SPI_InterruptSendData.o ./Src/009SPI_InterruptSendData.su ./Src/syscalls.d ./Src/syscalls.o ./Src/syscalls.su ./Src/sysmem.d ./Src/sysmem.o ./Src/sysmem.su

.PHONY: clean-Src

