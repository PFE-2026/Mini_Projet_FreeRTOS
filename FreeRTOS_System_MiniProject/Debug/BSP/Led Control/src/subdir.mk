################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../BSP/Led\ Control/src/led_control.c 

OBJS += \
./BSP/Led\ Control/src/led_control.o 

C_DEPS += \
./BSP/Led\ Control/src/led_control.d 


# Each subdirectory must supply rules for building sources it contributes
BSP/Led\ Control/src/led_control.o: ../BSP/Led\ Control/src/led_control.c BSP/Led\ Control/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I"/home/esaadi@actia.local/Documents/Intergation Phase/FreeRTOS_mini_project/FreeRTOS_System_MiniProject/BSP/Led Control/inc" -I"/home/esaadi@actia.local/Documents/Intergation Phase/FreeRTOS_mini_project/FreeRTOS_System_MiniProject/BSP/UART/inc" -I"/home/esaadi@actia.local/Documents/Intergation Phase/FreeRTOS_mini_project/FreeRTOS_System_MiniProject/BSP/Signal_Generator/inc" -I"/home/esaadi@actia.local/Documents/Intergation Phase/FreeRTOS_mini_project/FreeRTOS_System_MiniProject/BSP/Signal_Measure/inc" -I"/home/esaadi@actia.local/Documents/Intergation Phase/FreeRTOS_mini_project/FreeRTOS_System_MiniProject/Third_Party/Freertos" -I"/home/esaadi@actia.local/Documents/Intergation Phase/FreeRTOS_mini_project/FreeRTOS_System_MiniProject/Third_Party/Freertos/include" -I"/home/esaadi@actia.local/Documents/Intergation Phase/FreeRTOS_mini_project/FreeRTOS_System_MiniProject/Third_Party/Freertos/portable/ARM_CM4F" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"BSP/Led Control/src/led_control.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-BSP-2f-Led-20-Control-2f-src

clean-BSP-2f-Led-20-Control-2f-src:
	-$(RM) ./BSP/Led\ Control/src/led_control.cyclo ./BSP/Led\ Control/src/led_control.d ./BSP/Led\ Control/src/led_control.o ./BSP/Led\ Control/src/led_control.su

.PHONY: clean-BSP-2f-Led-20-Control-2f-src

