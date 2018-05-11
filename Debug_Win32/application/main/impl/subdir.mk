################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../application/main/impl/application_main.c 

OBJS += \
./application/main/impl/application_main.o 

C_DEPS += \
./application/main/impl/application_main.d 


# Each subdirectory must supply rules for building sources it contributes
application/main/impl/%.o: ../application/main/impl/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


