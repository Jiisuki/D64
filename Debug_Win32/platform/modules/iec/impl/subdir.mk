################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../platform/modules/iec/impl/iec.c 

OBJS += \
./platform/modules/iec/impl/iec.o 

C_DEPS += \
./platform/modules/iec/impl/iec.d 


# Each subdirectory must supply rules for building sources it contributes
platform/modules/iec/impl/%.o: ../platform/modules/iec/impl/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


