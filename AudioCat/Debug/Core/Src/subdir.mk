################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/diskio.c \
../Core/Src/fatfs.c \
../Core/Src/ff.c \
../Core/Src/ff_gen_drv.c \
../Core/Src/main.c \
../Core/Src/stm32u5xx_hal_msp.c \
../Core/Src/stm32u5xx_it.c \
../Core/Src/syscall.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32u5xx.c \
../Core/Src/user_diskio.c \
../Core/Src/user_diskio_spi.c \
../Core/Src/wav_header.c 

C_DEPS += \
./Core/Src/diskio.d \
./Core/Src/fatfs.d \
./Core/Src/ff.d \
./Core/Src/ff_gen_drv.d \
./Core/Src/main.d \
./Core/Src/stm32u5xx_hal_msp.d \
./Core/Src/stm32u5xx_it.d \
./Core/Src/syscall.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32u5xx.d \
./Core/Src/user_diskio.d \
./Core/Src/user_diskio_spi.d \
./Core/Src/wav_header.d 

OBJS += \
./Core/Src/diskio.o \
./Core/Src/fatfs.o \
./Core/Src/ff.o \
./Core/Src/ff_gen_drv.o \
./Core/Src/main.o \
./Core/Src/stm32u5xx_hal_msp.o \
./Core/Src/stm32u5xx_it.o \
./Core/Src/syscall.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32u5xx.o \
./Core/Src/user_diskio.o \
./Core/Src/user_diskio_spi.o \
./Core/Src/wav_header.o 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o Core/Src/%.su Core/Src/%.cyclo: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m33 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32U5A9xx -c -I../Core/Inc -I/Users/jeffrey/STM32Cube/Repository/STM32CubeU5/Drivers/STM32U5xx_HAL_Driver/Inc -I/Users/jeffrey/STM32Cube/Repository/STM32CubeU5/Drivers/STM32U5xx_HAL_Driver/Inc/Legacy -I/Users/jeffrey/STM32Cube/Repository/STM32CubeU5/Drivers/CMSIS/Device/ST/STM32U5xx/Include -I/Users/jeffrey/STM32Cube/Repository/STM32CubeU5/Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src

clean-Core-2f-Src:
	-$(RM) ./Core/Src/diskio.cyclo ./Core/Src/diskio.d ./Core/Src/diskio.o ./Core/Src/diskio.su ./Core/Src/fatfs.cyclo ./Core/Src/fatfs.d ./Core/Src/fatfs.o ./Core/Src/fatfs.su ./Core/Src/ff.cyclo ./Core/Src/ff.d ./Core/Src/ff.o ./Core/Src/ff.su ./Core/Src/ff_gen_drv.cyclo ./Core/Src/ff_gen_drv.d ./Core/Src/ff_gen_drv.o ./Core/Src/ff_gen_drv.su ./Core/Src/main.cyclo ./Core/Src/main.d ./Core/Src/main.o ./Core/Src/main.su ./Core/Src/stm32u5xx_hal_msp.cyclo ./Core/Src/stm32u5xx_hal_msp.d ./Core/Src/stm32u5xx_hal_msp.o ./Core/Src/stm32u5xx_hal_msp.su ./Core/Src/stm32u5xx_it.cyclo ./Core/Src/stm32u5xx_it.d ./Core/Src/stm32u5xx_it.o ./Core/Src/stm32u5xx_it.su ./Core/Src/syscall.cyclo ./Core/Src/syscall.d ./Core/Src/syscall.o ./Core/Src/syscall.su ./Core/Src/syscalls.cyclo ./Core/Src/syscalls.d ./Core/Src/syscalls.o ./Core/Src/syscalls.su ./Core/Src/sysmem.cyclo ./Core/Src/sysmem.d ./Core/Src/sysmem.o ./Core/Src/sysmem.su ./Core/Src/system_stm32u5xx.cyclo ./Core/Src/system_stm32u5xx.d ./Core/Src/system_stm32u5xx.o ./Core/Src/system_stm32u5xx.su ./Core/Src/user_diskio.cyclo ./Core/Src/user_diskio.d ./Core/Src/user_diskio.o ./Core/Src/user_diskio.su ./Core/Src/user_diskio_spi.cyclo ./Core/Src/user_diskio_spi.d ./Core/Src/user_diskio_spi.o ./Core/Src/user_diskio_spi.su ./Core/Src/wav_header.cyclo ./Core/Src/wav_header.d ./Core/Src/wav_header.o ./Core/Src/wav_header.su

.PHONY: clean-Core-2f-Src

