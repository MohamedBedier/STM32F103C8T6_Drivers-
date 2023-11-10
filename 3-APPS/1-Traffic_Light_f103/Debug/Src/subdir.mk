################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/GPIO_Prog.c \
../Src/LED_Program.c \
../Src/RCC_Program.c \
../Src/SSD_Prog.c \
../Src/Systick_Prog.c \
../Src/main.c \
../Src/syscalls.c \
../Src/sysmem.c 

OBJS += \
./Src/GPIO_Prog.o \
./Src/LED_Program.o \
./Src/RCC_Program.o \
./Src/SSD_Prog.o \
./Src/Systick_Prog.o \
./Src/main.o \
./Src/syscalls.o \
./Src/sysmem.o 

C_DEPS += \
./Src/GPIO_Prog.d \
./Src/LED_Program.d \
./Src/RCC_Program.d \
./Src/SSD_Prog.d \
./Src/Systick_Prog.d \
./Src/main.d \
./Src/syscalls.d \
./Src/sysmem.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o Src/%.su Src/%.cyclo: ../Src/%.c Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -c -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Src

clean-Src:
	-$(RM) ./Src/GPIO_Prog.cyclo ./Src/GPIO_Prog.d ./Src/GPIO_Prog.o ./Src/GPIO_Prog.su ./Src/LED_Program.cyclo ./Src/LED_Program.d ./Src/LED_Program.o ./Src/LED_Program.su ./Src/RCC_Program.cyclo ./Src/RCC_Program.d ./Src/RCC_Program.o ./Src/RCC_Program.su ./Src/SSD_Prog.cyclo ./Src/SSD_Prog.d ./Src/SSD_Prog.o ./Src/SSD_Prog.su ./Src/Systick_Prog.cyclo ./Src/Systick_Prog.d ./Src/Systick_Prog.o ./Src/Systick_Prog.su ./Src/main.cyclo ./Src/main.d ./Src/main.o ./Src/main.su ./Src/syscalls.cyclo ./Src/syscalls.d ./Src/syscalls.o ./Src/syscalls.su ./Src/sysmem.cyclo ./Src/sysmem.d ./Src/sysmem.o ./Src/sysmem.su

.PHONY: clean-Src

