################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Core/Lib/dictator.cpp \
../Core/Lib/events.cpp \
../Core/Lib/joystick.cpp \
../Core/Lib/led.cpp \
../Core/Lib/max11616.cpp \
../Core/Lib/mcp23017.cpp \
../Core/Lib/pin_master.cpp \
../Core/Lib/potentiometer.cpp \
../Core/Lib/scheduler.cpp \
../Core/Lib/switch.cpp 

OBJS += \
./Core/Lib/dictator.o \
./Core/Lib/events.o \
./Core/Lib/joystick.o \
./Core/Lib/led.o \
./Core/Lib/max11616.o \
./Core/Lib/mcp23017.o \
./Core/Lib/pin_master.o \
./Core/Lib/potentiometer.o \
./Core/Lib/scheduler.o \
./Core/Lib/switch.o 

CPP_DEPS += \
./Core/Lib/dictator.d \
./Core/Lib/events.d \
./Core/Lib/joystick.d \
./Core/Lib/led.d \
./Core/Lib/max11616.d \
./Core/Lib/mcp23017.d \
./Core/Lib/pin_master.d \
./Core/Lib/potentiometer.d \
./Core/Lib/scheduler.d \
./Core/Lib/switch.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Lib/dictator.o: ../Core/Lib/dictator.cpp
	arm-none-eabi-g++ "$<" -mcpu=cortex-m7 -std=gnu++14 -g3 -DUSE_HAL_DRIVER -DSTM32H743xx -c -I../Core/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -Og -ffunction-sections -fdata-sections -fno-rtti -fno-threadsafe-statics -fno-use-cxa-atexit -Wall -fexceptions -fstack-usage -MMD -MP -MF"Core/Lib/dictator.d" -MT"$@"  -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Lib/events.o: ../Core/Lib/events.cpp
	arm-none-eabi-g++ "$<" -mcpu=cortex-m7 -std=gnu++14 -g3 -DUSE_HAL_DRIVER -DSTM32H743xx -c -I../Core/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -Og -ffunction-sections -fdata-sections -fno-rtti -fno-threadsafe-statics -fno-use-cxa-atexit -Wall -fexceptions -fstack-usage -MMD -MP -MF"Core/Lib/events.d" -MT"$@"  -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Lib/joystick.o: ../Core/Lib/joystick.cpp
	arm-none-eabi-g++ "$<" -mcpu=cortex-m7 -std=gnu++14 -g3 -DUSE_HAL_DRIVER -DSTM32H743xx -c -I../Core/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -Og -ffunction-sections -fdata-sections -fno-rtti -fno-threadsafe-statics -fno-use-cxa-atexit -Wall -fexceptions -fstack-usage -MMD -MP -MF"Core/Lib/joystick.d" -MT"$@"  -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Lib/led.o: ../Core/Lib/led.cpp
	arm-none-eabi-g++ "$<" -mcpu=cortex-m7 -std=gnu++14 -g3 -DUSE_HAL_DRIVER -DSTM32H743xx -c -I../Core/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -Og -ffunction-sections -fdata-sections -fno-rtti -fno-threadsafe-statics -fno-use-cxa-atexit -Wall -fexceptions -fstack-usage -MMD -MP -MF"Core/Lib/led.d" -MT"$@"  -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Lib/max11616.o: ../Core/Lib/max11616.cpp
	arm-none-eabi-g++ "$<" -mcpu=cortex-m7 -std=gnu++14 -g3 -DUSE_HAL_DRIVER -DSTM32H743xx -c -I../Core/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -Og -ffunction-sections -fdata-sections -fno-rtti -fno-threadsafe-statics -fno-use-cxa-atexit -Wall -fexceptions -fstack-usage -MMD -MP -MF"Core/Lib/max11616.d" -MT"$@"  -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Lib/mcp23017.o: ../Core/Lib/mcp23017.cpp
	arm-none-eabi-g++ "$<" -mcpu=cortex-m7 -std=gnu++14 -g3 -DUSE_HAL_DRIVER -DSTM32H743xx -c -I../Core/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -Og -ffunction-sections -fdata-sections -fno-rtti -fno-threadsafe-statics -fno-use-cxa-atexit -Wall -fexceptions -fstack-usage -MMD -MP -MF"Core/Lib/mcp23017.d" -MT"$@"  -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Lib/pin_master.o: ../Core/Lib/pin_master.cpp
	arm-none-eabi-g++ "$<" -mcpu=cortex-m7 -std=gnu++14 -g3 -DUSE_HAL_DRIVER -DSTM32H743xx -c -I../Core/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -Og -ffunction-sections -fdata-sections -fno-rtti -fno-threadsafe-statics -fno-use-cxa-atexit -Wall -fexceptions -fstack-usage -MMD -MP -MF"Core/Lib/pin_master.d" -MT"$@"  -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Lib/potentiometer.o: ../Core/Lib/potentiometer.cpp
	arm-none-eabi-g++ "$<" -mcpu=cortex-m7 -std=gnu++14 -g3 -DUSE_HAL_DRIVER -DSTM32H743xx -c -I../Core/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -Og -ffunction-sections -fdata-sections -fno-rtti -fno-threadsafe-statics -fno-use-cxa-atexit -Wall -fexceptions -fstack-usage -MMD -MP -MF"Core/Lib/potentiometer.d" -MT"$@"  -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Lib/scheduler.o: ../Core/Lib/scheduler.cpp
	arm-none-eabi-g++ "$<" -mcpu=cortex-m7 -std=gnu++14 -g3 -DUSE_HAL_DRIVER -DSTM32H743xx -c -I../Core/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -Og -ffunction-sections -fdata-sections -fno-rtti -fno-threadsafe-statics -fno-use-cxa-atexit -Wall -fexceptions -fstack-usage -MMD -MP -MF"Core/Lib/scheduler.d" -MT"$@"  -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Lib/switch.o: ../Core/Lib/switch.cpp
	arm-none-eabi-g++ "$<" -mcpu=cortex-m7 -std=gnu++14 -g3 -DUSE_HAL_DRIVER -DSTM32H743xx -c -I../Core/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -Og -ffunction-sections -fdata-sections -fno-rtti -fno-threadsafe-statics -fno-use-cxa-atexit -Wall -fexceptions -fstack-usage -MMD -MP -MF"Core/Lib/switch.d" -MT"$@"  -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

