################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/ST/FatFs/src/option/syscall.c 

OBJS += \
./Middlewares/ST/FatFs/src/option/syscall.o 

C_DEPS += \
./Middlewares/ST/FatFs/src/option/syscall.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/ST/FatFs/src/option/%.o Middlewares/ST/FatFs/src/option/%.su Middlewares/ST/FatFs/src/option/%.cyclo: ../Middlewares/ST/FatFs/src/option/%.c Middlewares/ST/FatFs/src/option/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m33 -std=gnu11 -g3 -DDEBUG -DUSE_FULL_LL_DRIVER -DUSE_HAL_DRIVER -DSTM32U5A5xx -DFX_INCLUDE_USER_DEFINE_FILE -c -I../Core/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32U5xx/Include -I../Drivers/CMSIS/Include -I../FileX/App -I../Middlewares/ST/filex/common/inc -I../Middlewares/ST/filex/ports/generic/inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middlewares-2f-ST-2f-FatFs-2f-src-2f-option

clean-Middlewares-2f-ST-2f-FatFs-2f-src-2f-option:
	-$(RM) ./Middlewares/ST/FatFs/src/option/syscall.cyclo ./Middlewares/ST/FatFs/src/option/syscall.d ./Middlewares/ST/FatFs/src/option/syscall.o ./Middlewares/ST/FatFs/src/option/syscall.su

.PHONY: clean-Middlewares-2f-ST-2f-FatFs-2f-src-2f-option

