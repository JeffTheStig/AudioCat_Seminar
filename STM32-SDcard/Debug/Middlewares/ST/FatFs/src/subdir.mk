################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/ST/FatFs/src/diskio.c \
../Middlewares/ST/FatFs/src/ff.c \
../Middlewares/ST/FatFs/src/ff_gen_drv.c 

OBJS += \
./Middlewares/ST/FatFs/src/diskio.o \
./Middlewares/ST/FatFs/src/ff.o \
./Middlewares/ST/FatFs/src/ff_gen_drv.o 

C_DEPS += \
./Middlewares/ST/FatFs/src/diskio.d \
./Middlewares/ST/FatFs/src/ff.d \
./Middlewares/ST/FatFs/src/ff_gen_drv.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/ST/FatFs/src/%.o Middlewares/ST/FatFs/src/%.su Middlewares/ST/FatFs/src/%.cyclo: ../Middlewares/ST/FatFs/src/%.c Middlewares/ST/FatFs/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m33 -std=gnu11 -g3 -DDEBUG -DUSE_FULL_LL_DRIVER -DUSE_HAL_DRIVER -DSTM32U5A5xx -DFX_INCLUDE_USER_DEFINE_FILE -c -I../Core/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32U5xx/Include -I../Drivers/CMSIS/Include -I../FileX/App -I../Middlewares/ST/filex/common/inc -I../Middlewares/ST/filex/ports/generic/inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middlewares-2f-ST-2f-FatFs-2f-src

clean-Middlewares-2f-ST-2f-FatFs-2f-src:
	-$(RM) ./Middlewares/ST/FatFs/src/diskio.cyclo ./Middlewares/ST/FatFs/src/diskio.d ./Middlewares/ST/FatFs/src/diskio.o ./Middlewares/ST/FatFs/src/diskio.su ./Middlewares/ST/FatFs/src/ff.cyclo ./Middlewares/ST/FatFs/src/ff.d ./Middlewares/ST/FatFs/src/ff.o ./Middlewares/ST/FatFs/src/ff.su ./Middlewares/ST/FatFs/src/ff_gen_drv.cyclo ./Middlewares/ST/FatFs/src/ff_gen_drv.d ./Middlewares/ST/FatFs/src/ff_gen_drv.o ./Middlewares/ST/FatFs/src/ff_gen_drv.su

.PHONY: clean-Middlewares-2f-ST-2f-FatFs-2f-src

