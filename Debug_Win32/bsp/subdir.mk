################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../bsp/board.c \
../bsp/clock_config.c \
../bsp/peripherals.c \
../bsp/pin_mux.c 

S_UPPER_SRCS += \
../bsp/startup_MKE06Z4.S 

OBJS += \
./bsp/board.o \
./bsp/clock_config.o \
./bsp/peripherals.o \
./bsp/pin_mux.o \
./bsp/startup_MKE06Z4.o 

C_DEPS += \
./bsp/board.d \
./bsp/clock_config.d \
./bsp/peripherals.d \
./bsp/pin_mux.d 


# Each subdirectory must supply rules for building sources it contributes
bsp/%.o: ../bsp/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

bsp/%.o: ../bsp/%.S
	@echo 'Building file: $<'
	@echo 'Invoking: GCC Assembler'
	as  -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


