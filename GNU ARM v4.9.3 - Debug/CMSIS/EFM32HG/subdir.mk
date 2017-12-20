################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../CMSIS/EFM32HG/startup_gcc_efm32hg.s 

C_SRCS += \
../CMSIS/EFM32HG/system_efm32hg.c 

OBJS += \
./CMSIS/EFM32HG/startup_gcc_efm32hg.o \
./CMSIS/EFM32HG/system_efm32hg.o 

C_DEPS += \
./CMSIS/EFM32HG/system_efm32hg.d 


# Each subdirectory must supply rules for building sources it contributes
CMSIS/EFM32HG/%.o: ../CMSIS/EFM32HG/%.s
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM Assembler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m0plus -mthumb -c -x assembler-with-cpp -I"E:/simplicity_studio/developer/sdks/gecko_sdk_suite/v1.1//app/mcu_example/SLSTK3400A_EFM32HG/humitemp" -I"E:/simplicity_studio/developer/sdks/gecko_sdk_suite/v1.1//hardware/kit/SLSTK3400A_EFM32HG/config" -I"E:/simplicity_studio/developer/sdks/gecko_sdk_suite/v1.1//platform/CMSIS/Include" -I"E:/simplicity_studio/developer/sdks/gecko_sdk_suite/v1.1//platform/emlib/inc" -I"E:/simplicity_studio/developer/sdks/gecko_sdk_suite/v1.1//platform/emdrv/common/inc" -I"E:/simplicity_studio/developer/sdks/gecko_sdk_suite/v1.1//platform/emdrv/dmadrv/config" -I"E:/simplicity_studio/developer/sdks/gecko_sdk_suite/v1.1//platform/emdrv/ezradiodrv/config" -I"E:/simplicity_studio/developer/sdks/gecko_sdk_suite/v1.1//platform/emdrv/nvm/config" -I"E:/simplicity_studio/developer/sdks/gecko_sdk_suite/v1.1//platform/emdrv/rtcdrv/config" -I"E:/simplicity_studio/developer/sdks/gecko_sdk_suite/v1.1//platform/emdrv/spidrv/config" -I"E:/simplicity_studio/developer/sdks/gecko_sdk_suite/v1.1//platform/emdrv/tempdrv/config" -I"E:/simplicity_studio/developer/sdks/gecko_sdk_suite/v1.1//platform/emdrv/uartdrv/config" -I"E:/simplicity_studio/developer/sdks/gecko_sdk_suite/v1.1//platform/emdrv/ustimer/config" -I"E:/simplicity_studio/developer/sdks/gecko_sdk_suite/v1.1//platform/emdrv/dmadrv/inc" -I"E:/simplicity_studio/developer/sdks/gecko_sdk_suite/v1.1//platform/emdrv/gpiointerrupt/inc" -I"E:/simplicity_studio/developer/sdks/gecko_sdk_suite/v1.1//platform/emdrv/nvm/inc" -I"E:/simplicity_studio/developer/sdks/gecko_sdk_suite/v1.1//platform/emdrv/rtcdrv/inc" -I"E:/simplicity_studio/developer/sdks/gecko_sdk_suite/v1.1//platform/emdrv/sleep/inc" -I"E:/simplicity_studio/developer/sdks/gecko_sdk_suite/v1.1//platform/emdrv/spidrv/inc" -I"E:/simplicity_studio/developer/sdks/gecko_sdk_suite/v1.1//platform/emdrv/uartdrv/inc" -I"E:/simplicity_studio/developer/sdks/gecko_sdk_suite/v1.1//platform/emdrv/ustimer/inc" -I"E:/simplicity_studio/developer/sdks/gecko_sdk_suite/v1.1//platform/emdrv/tempdrv/inc" -I"E:/simplicity_studio/developer/sdks/gecko_sdk_suite/v1.1//hardware/kit/common/bsp" -I"E:/simplicity_studio/developer/sdks/gecko_sdk_suite/v1.1//hardware/kit/common/drivers" -I"E:/simplicity_studio/developer/sdks/gecko_sdk_suite/v1.1//platform/Device/SiliconLabs/EFM32HG/Include" -I"E:/simplicity_studio/developer/sdks/gecko_sdk_suite/v1.1//platform/middleware/glib" -I"E:/simplicity_studio/developer/sdks/gecko_sdk_suite/v1.1//platform/middleware/glib/glib" -I"E:/simplicity_studio/developer/sdks/gecko_sdk_suite/v1.1//platform/middleware/glib/dmd" -I"E:/simplicity_studio/developer/sdks/gecko_sdk_suite/v1.1//platform/middleware/glib/dmd/ssd2119" -I"C:\Users\evert.DESKTOP-6EE9RU8\SimplicityStudio\v4_workspace\sheep\inc" '-DEFM32HG322F64=1' -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

CMSIS/EFM32HG/system_efm32hg.o: ../CMSIS/EFM32HG/system_efm32hg.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m0plus -mthumb -std=c99 '-DEFM32HG322F64=1' '-DDEBUG=1' -I"E:/simplicity_studio/developer/sdks/gecko_sdk_suite/v1.1//app/mcu_example/SLSTK3400A_EFM32HG/humitemp" -I"E:/simplicity_studio/developer/sdks/gecko_sdk_suite/v1.1//hardware/kit/SLSTK3400A_EFM32HG/config" -I"E:/simplicity_studio/developer/sdks/gecko_sdk_suite/v1.1//platform/CMSIS/Include" -I"E:/simplicity_studio/developer/sdks/gecko_sdk_suite/v1.1//platform/emlib/inc" -I"E:/simplicity_studio/developer/sdks/gecko_sdk_suite/v1.1//platform/emdrv/common/inc" -I"E:/simplicity_studio/developer/sdks/gecko_sdk_suite/v1.1//platform/emdrv/dmadrv/config" -I"E:/simplicity_studio/developer/sdks/gecko_sdk_suite/v1.1//platform/emdrv/ezradiodrv/config" -I"E:/simplicity_studio/developer/sdks/gecko_sdk_suite/v1.1//platform/emdrv/nvm/config" -I"E:/simplicity_studio/developer/sdks/gecko_sdk_suite/v1.1//platform/emdrv/rtcdrv/config" -I"E:/simplicity_studio/developer/sdks/gecko_sdk_suite/v1.1//platform/emdrv/spidrv/config" -I"E:/simplicity_studio/developer/sdks/gecko_sdk_suite/v1.1//platform/emdrv/tempdrv/config" -I"E:/simplicity_studio/developer/sdks/gecko_sdk_suite/v1.1//platform/emdrv/uartdrv/config" -I"E:/simplicity_studio/developer/sdks/gecko_sdk_suite/v1.1//platform/emdrv/ustimer/config" -I"E:/simplicity_studio/developer/sdks/gecko_sdk_suite/v1.1//platform/emdrv/dmadrv/inc" -I"E:/simplicity_studio/developer/sdks/gecko_sdk_suite/v1.1//platform/emdrv/gpiointerrupt/inc" -I"E:/simplicity_studio/developer/sdks/gecko_sdk_suite/v1.1//platform/emdrv/nvm/inc" -I"E:/simplicity_studio/developer/sdks/gecko_sdk_suite/v1.1//platform/emdrv/rtcdrv/inc" -I"E:/simplicity_studio/developer/sdks/gecko_sdk_suite/v1.1//platform/emdrv/sleep/inc" -I"E:/simplicity_studio/developer/sdks/gecko_sdk_suite/v1.1//platform/emdrv/spidrv/inc" -I"E:/simplicity_studio/developer/sdks/gecko_sdk_suite/v1.1//platform/emdrv/uartdrv/inc" -I"E:/simplicity_studio/developer/sdks/gecko_sdk_suite/v1.1//platform/emdrv/ustimer/inc" -I"E:/simplicity_studio/developer/sdks/gecko_sdk_suite/v1.1//platform/emdrv/tempdrv/inc" -I"E:/simplicity_studio/developer/sdks/gecko_sdk_suite/v1.1//hardware/kit/common/bsp" -I"E:/simplicity_studio/developer/sdks/gecko_sdk_suite/v1.1//hardware/kit/common/drivers" -I"E:/simplicity_studio/developer/sdks/gecko_sdk_suite/v1.1//platform/Device/SiliconLabs/EFM32HG/Include" -I"E:/simplicity_studio/developer/sdks/gecko_sdk_suite/v1.1//platform/middleware/glib" -I"E:/simplicity_studio/developer/sdks/gecko_sdk_suite/v1.1//platform/middleware/glib/glib" -I"E:/simplicity_studio/developer/sdks/gecko_sdk_suite/v1.1//platform/middleware/glib/dmd" -I"E:/simplicity_studio/developer/sdks/gecko_sdk_suite/v1.1//platform/middleware/glib/dmd/ssd2119" -I"C:\Users\evert.DESKTOP-6EE9RU8\SimplicityStudio\v4_workspace\sheep\inc" -include"C:\Users\evert.DESKTOP-6EE9RU8\SimplicityStudio\v4_workspace\sheep\inc\lsm_9DS1.h" -Os -Wall -c -fmessage-length=0 -mno-sched-prolog -fno-builtin -ffunction-sections -fdata-sections -MMD -MP -MF"CMSIS/EFM32HG/system_efm32hg.d" -MT"CMSIS/EFM32HG/system_efm32hg.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


