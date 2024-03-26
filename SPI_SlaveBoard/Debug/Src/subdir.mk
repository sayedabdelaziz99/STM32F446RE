################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/Slave_receiveData.c \
../Src/syscalls.c \
../Src/sysmem.c 

OBJS += \
./Src/Slave_receiveData.o \
./Src/syscalls.o \
./Src/sysmem.o 

C_DEPS += \
./Src/Slave_receiveData.d \
./Src/syscalls.d \
./Src/sysmem.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o Src/%.su: ../Src/%.c Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F446RETx -DNUCLEO_F446RE -c -I../Inc -I"E:/MCU1/SPI_SlaveBoard/BSP" -I"E:/MCU1/SPI_SlaveBoard/Drivers/GPIO_DRIVERS" -I"E:/MCU1/SPI_SlaveBoard/Drivers/inc" -I"E:/MCU1/SPI_SlaveBoard/Drivers/SPI_DRIVER" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Src

clean-Src:
	-$(RM) ./Src/Slave_receiveData.d ./Src/Slave_receiveData.o ./Src/Slave_receiveData.su ./Src/syscalls.d ./Src/syscalls.o ./Src/syscalls.su ./Src/sysmem.d ./Src/sysmem.o ./Src/sysmem.su

.PHONY: clean-Src

