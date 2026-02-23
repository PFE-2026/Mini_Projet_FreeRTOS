################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../BSP/UART/uart.c 

OBJS += \
./BSP/UART/uart.o 

C_DEPS += \
./BSP/UART/uart.d 


# Each subdirectory must supply rules for building sources it contributes
BSP/UART/%.o BSP/UART/%.su BSP/UART/%.cyclo: ../BSP/UART/%.c BSP/UART/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I"D:/PFE2026/mini_projet/FreeRTOS_System/BSP/Led Control/inc" -I"D:/PFE2026/mini_projet/FreeRTOS_System/BSP/UART/inc" -I"D:/PFE2026/mini_projet/FreeRTOS_System/BSP/Signal_Generator/inc" -I"D:/PFE2026/mini_projet/FreeRTOS_System/BSP/Signal_Measure/inc" -I"D:/PFE2026/mini_projet/FreeRTOS_System/Third_Party/Freertos" -I"D:/PFE2026/mini_projet/FreeRTOS_System/Third_Party/Freertos/include" -I"D:/PFE2026/mini_projet/FreeRTOS_System/Third_Party/Freertos/portable/ARM_CM4F" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-BSP-2f-UART

clean-BSP-2f-UART:
	-$(RM) ./BSP/UART/uart.cyclo ./BSP/UART/uart.d ./BSP/UART/uart.o ./BSP/UART/uart.su

.PHONY: clean-BSP-2f-UART

