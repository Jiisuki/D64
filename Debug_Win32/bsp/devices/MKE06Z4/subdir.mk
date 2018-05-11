################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../bsp/devices/MKE06Z4/system_MKE06Z4.c 

OBJS += \
./bsp/devices/MKE06Z4/system_MKE06Z4.o 

C_DEPS += \
./bsp/devices/MKE06Z4/system_MKE06Z4.d 


# Each subdirectory must supply rules for building sources it contributes
bsp/devices/MKE06Z4/%.o: ../bsp/devices/MKE06Z4/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


