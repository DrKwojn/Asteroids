################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/external/XPT2046_touch.c \
../Drivers/external/lcd_ili9341.c 

C_DEPS += \
./Drivers/external/XPT2046_touch.d \
./Drivers/external/lcd_ili9341.d 

OBJS += \
./Drivers/external/XPT2046_touch.o \
./Drivers/external/lcd_ili9341.o 


# Each subdirectory must supply rules for building sources it contributes
Drivers/external/%.o Drivers/external/%.su: ../Drivers/external/%.c Drivers/external/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -DUSE_HAL_DRIVER -DSTM32G474xx -DUSE_FULL_LL_DRIVER -c -I../Core/Inc -I../Drivers/STM32G4xx_HAL_Driver/Inc -I../Drivers/STM32G4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32G4xx/Include -I../Drivers/CMSIS/Include -I../USB_Device/App -I../USB_Device/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I../Program/Inc -I../Drivers/external -Ofast -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-external

clean-Drivers-2f-external:
	-$(RM) ./Drivers/external/XPT2046_touch.d ./Drivers/external/XPT2046_touch.o ./Drivers/external/XPT2046_touch.su ./Drivers/external/lcd_ili9341.d ./Drivers/external/lcd_ili9341.o ./Drivers/external/lcd_ili9341.su

.PHONY: clean-Drivers-2f-external

