################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Program/Src/draw.c \
../Program/Src/game.c \
../Program/Src/io.c \
../Program/Src/ui.c \
../Program/Src/util.c 

C_DEPS += \
./Program/Src/draw.d \
./Program/Src/game.d \
./Program/Src/io.d \
./Program/Src/ui.d \
./Program/Src/util.d 

OBJS += \
./Program/Src/draw.o \
./Program/Src/game.o \
./Program/Src/io.o \
./Program/Src/ui.o \
./Program/Src/util.o 


# Each subdirectory must supply rules for building sources it contributes
Program/Src/%.o Program/Src/%.su: ../Program/Src/%.c Program/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -DUSE_HAL_DRIVER -DSTM32G474xx -DUSE_FULL_LL_DRIVER -c -I../Core/Inc -I../Drivers/STM32G4xx_HAL_Driver/Inc -I../Drivers/STM32G4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32G4xx/Include -I../Drivers/CMSIS/Include -I../USB_Device/App -I../USB_Device/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I../Program/Inc -I../Drivers/external -Ofast -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Program-2f-Src

clean-Program-2f-Src:
	-$(RM) ./Program/Src/draw.d ./Program/Src/draw.o ./Program/Src/draw.su ./Program/Src/game.d ./Program/Src/game.o ./Program/Src/game.su ./Program/Src/io.d ./Program/Src/io.o ./Program/Src/io.su ./Program/Src/ui.d ./Program/Src/ui.o ./Program/Src/ui.su ./Program/Src/util.d ./Program/Src/util.o ./Program/Src/util.su

.PHONY: clean-Program-2f-Src

