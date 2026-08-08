################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../application/sensor/sensor.c 

OBJS += \
./application/sensor/sensor.o 

C_DEPS += \
./application/sensor/sensor.d 


# Each subdirectory must supply rules for building sources it contributes
application/sensor/%.o application/sensor/%.su application/sensor/%.cyclo: ../application/sensor/%.c application/sensor/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_NUCLEO_64 -DUSE_HAL_DRIVER -DSTM32F446xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/BSP/STM32F4xx-Nucleo -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../application -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-application-2f-sensor

clean-application-2f-sensor:
	-$(RM) ./application/sensor/sensor.cyclo ./application/sensor/sensor.d ./application/sensor/sensor.o ./application/sensor/sensor.su

.PHONY: clean-application-2f-sensor

