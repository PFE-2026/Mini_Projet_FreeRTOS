################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Third_Party/Freertos/croutine.c \
../Third_Party/Freertos/event_groups.c \
../Third_Party/Freertos/list.c \
../Third_Party/Freertos/queue.c \
../Third_Party/Freertos/stream_buffer.c \
../Third_Party/Freertos/tasks.c \
../Third_Party/Freertos/timers.c 

OBJS += \
./Third_Party/Freertos/croutine.o \
./Third_Party/Freertos/event_groups.o \
./Third_Party/Freertos/list.o \
./Third_Party/Freertos/queue.o \
./Third_Party/Freertos/stream_buffer.o \
./Third_Party/Freertos/tasks.o \
./Third_Party/Freertos/timers.o 

C_DEPS += \
./Third_Party/Freertos/croutine.d \
./Third_Party/Freertos/event_groups.d \
./Third_Party/Freertos/list.d \
./Third_Party/Freertos/queue.d \
./Third_Party/Freertos/stream_buffer.d \
./Third_Party/Freertos/tasks.d \
./Third_Party/Freertos/timers.d 


# Each subdirectory must supply rules for building sources it contributes
Third_Party/Freertos/%.o Third_Party/Freertos/%.su Third_Party/Freertos/%.cyclo: ../Third_Party/Freertos/%.c Third_Party/Freertos/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I"/home/esaadi@actia.local/Documents/Intergation Phase/Mini_Project_Workspace/FreeRTOS_System/BSP/UART/inc" -I"/home/esaadi@actia.local/Documents/Intergation Phase/Mini_Project_Workspace/FreeRTOS_System/BSP/Signal_Generator/inc" -I"/home/esaadi@actia.local/Documents/Intergation Phase/Mini_Project_Workspace/FreeRTOS_System/BSP/Signal_Measure/inc" -I"/home/esaadi@actia.local/Documents/Intergation Phase/Mini_Project_Workspace/FreeRTOS_System/Third_Party/Freertos" -I"/home/esaadi@actia.local/Documents/Intergation Phase/Mini_Project_Workspace/FreeRTOS_System/Third_Party/Freertos/include" -I"/home/esaadi@actia.local/Documents/Intergation Phase/Mini_Project_Workspace/FreeRTOS_System/Third_Party/Freertos/portable/ARM_CM4F" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Third_Party-2f-Freertos

clean-Third_Party-2f-Freertos:
	-$(RM) ./Third_Party/Freertos/croutine.cyclo ./Third_Party/Freertos/croutine.d ./Third_Party/Freertos/croutine.o ./Third_Party/Freertos/croutine.su ./Third_Party/Freertos/event_groups.cyclo ./Third_Party/Freertos/event_groups.d ./Third_Party/Freertos/event_groups.o ./Third_Party/Freertos/event_groups.su ./Third_Party/Freertos/list.cyclo ./Third_Party/Freertos/list.d ./Third_Party/Freertos/list.o ./Third_Party/Freertos/list.su ./Third_Party/Freertos/queue.cyclo ./Third_Party/Freertos/queue.d ./Third_Party/Freertos/queue.o ./Third_Party/Freertos/queue.su ./Third_Party/Freertos/stream_buffer.cyclo ./Third_Party/Freertos/stream_buffer.d ./Third_Party/Freertos/stream_buffer.o ./Third_Party/Freertos/stream_buffer.su ./Third_Party/Freertos/tasks.cyclo ./Third_Party/Freertos/tasks.d ./Third_Party/Freertos/tasks.o ./Third_Party/Freertos/tasks.su ./Third_Party/Freertos/timers.cyclo ./Third_Party/Freertos/timers.d ./Third_Party/Freertos/timers.o ./Third_Party/Freertos/timers.su

.PHONY: clean-Third_Party-2f-Freertos

