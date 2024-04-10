################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../Src/bootloader.s 

C_SRCS += \
../Src/firmware.c 

OBJS += \
./Src/bootloader.o \
./Src/firmware.o 

S_DEPS += \
./Src/bootloader.d 

C_DEPS += \
./Src/firmware.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o: ../Src/%.s Src/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m4 -g3 -DDEBUG -c -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@" "$<"
Src/%.o Src/%.su: ../Src/%.c Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu18 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F446RETx -DNUCLEO_F446RE -c -I"E:/MCU1/006BootLoader_firmware/Drivers/GPIO_DRIVERS" -I"E:/MCU1/BootLoader_app/Debug" -I"E:/MCU1/006BootLoader_firmware/Drivers/USART_Driver" -I"E:/MCU1/006BootLoader_firmware/Drivers/I2C_Driver" -I"E:/MCU1/006BootLoader_firmware/Drivers/stm32f446re" -I"E:/MCU1/006BootLoader_firmware/Drivers/SPI_DRIVER" -I"E:/MCU1/006BootLoader_firmware/BSP" -I../Inc -I"E:/MCU1/006BootLoader_firmware/Drivers/RCC_Driver" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Src

clean-Src:
	-$(RM) ./Src/bootloader.d ./Src/bootloader.o ./Src/firmware.d ./Src/firmware.o ./Src/firmware.su

.PHONY: clean-Src

