################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/Slave_ReceiveData.c \
../Src/syscalls.c \
../Src/sysmem.c 

OBJS += \
./Src/Slave_ReceiveData.o \
./Src/syscalls.o \
./Src/sysmem.o 

C_DEPS += \
./Src/Slave_ReceiveData.d \
./Src/syscalls.d \
./Src/sysmem.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o Src/%.su: ../Src/%.c Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu18 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F446RETx -DNUCLEO_F446RE -c -I"E:/MCU1/I2C_SlaveBoard/Drivers/GPIO_DRIVERS" -I"E:/MCU1/I2C_SlaveBoard/Drivers/I2C_Driver" -I"E:/MCU1/I2C_SlaveBoard/Drivers/stm32f446re" -I"E:/MCU1/I2C_SlaveBoard/Drivers/SPI_DRIVER" -I"E:/MCU1/I2C_SlaveBoard/BSP" -I../Inc -I"E:/MCU1/I2C_SlaveBoard/Drivers/RCC_Driver" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Src

clean-Src:
	-$(RM) ./Src/Slave_ReceiveData.d ./Src/Slave_ReceiveData.o ./Src/Slave_ReceiveData.su ./Src/syscalls.d ./Src/syscalls.o ./Src/syscalls.su ./Src/sysmem.d ./Src/sysmem.o ./Src/sysmem.su

.PHONY: clean-Src

