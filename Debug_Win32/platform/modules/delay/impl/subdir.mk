################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../platform/modules/delay/impl/delay.c 

OBJS += \
./platform/modules/delay/impl/delay.o 

C_DEPS += \
./platform/modules/delay/impl/delay.d 


# Each subdirectory must supply rules for building sources it contributes
platform/modules/delay/impl/%.o: ../platform/modules/delay/impl/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


