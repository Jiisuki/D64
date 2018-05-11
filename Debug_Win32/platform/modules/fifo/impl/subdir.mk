################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../platform/modules/fifo/impl/fifo.c 

OBJS += \
./platform/modules/fifo/impl/fifo.o 

C_DEPS += \
./platform/modules/fifo/impl/fifo.d 


# Each subdirectory must supply rules for building sources it contributes
platform/modules/fifo/impl/%.o: ../platform/modules/fifo/impl/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


