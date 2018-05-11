################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../platform/modules/flash/impl/flash.c 

OBJS += \
./platform/modules/flash/impl/flash.o 

C_DEPS += \
./platform/modules/flash/impl/flash.d 


# Each subdirectory must supply rules for building sources it contributes
platform/modules/flash/impl/%.o: ../platform/modules/flash/impl/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


