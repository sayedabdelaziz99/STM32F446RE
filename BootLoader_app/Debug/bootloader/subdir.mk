################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../bootloader/bootloader.s 

C_SRCS += \
../bootloader/bootloader.c 

OBJS += \
./bootloader/bootloader.o 

S_DEPS += \
./bootloader/bootloader.d 

C_DEPS += \
./bootloader/bootloader.d 


# Each subdirectory must supply rules for building sources it contributes
bootloader/%.o bootloader/%.su: ../bootloader/%.c bootloader/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu18 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F446RETx -DNUCLEO_F446RE -c -I"E:/MCU1/006BootLoader/Drivers/GPIO_DRIVERS" -I"E:/MCU1/006BootLoader/bootloader" -I"E:/MCU1/006BootLoader/Drivers/USART_Driver" -I"E:/MCU1/006BootLoader/Drivers/I2C_Driver" -I"E:/MCU1/006BootLoader/Drivers/stm32f446re" -I"E:/MCU1/006BootLoader/Drivers/SPI_DRIVER" -I"E:/MCU1/006BootLoader/BSP" -I../Inc -I"E:/MCU1/006BootLoader/Drivers/RCC_Driver" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
bootloader/%.o: ../bootloader/%.s bootloader/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m4 -g3 -DDEBUG -c -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@" "$<"

clean: clean-bootloader

clean-bootloader:
	-$(RM) ./bootloader/bootloader.d ./bootloader/bootloader.o ./bootloader/bootloader.su

.PHONY: clean-bootloader

