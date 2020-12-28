################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Core/Lib/Events/flash_light.cpp 

OBJS += \
./Core/Lib/Events/flash_light.o 

CPP_DEPS += \
./Core/Lib/Events/flash_light.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Lib/Events/flash_light.o: ../Core/Lib/Events/flash_light.cpp
	arm-none-eabi-g++ "$<" -mcpu=cortex-m7 -std=gnu++14 -g3 -DUSE_HAL_DRIVER -DSTM32H743xx -c -I../Core/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -Og -ffunction-sections -fdata-sections -fno-rtti -fno-threadsafe-statics -fno-use-cxa-atexit -Wall -fexceptions -fstack-usage -MMD -MP -MF"Core/Lib/Events/flash_light.d" -MT"$@"  -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

