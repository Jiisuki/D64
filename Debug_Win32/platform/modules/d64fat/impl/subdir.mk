################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../platform/modules/d64fat/impl/d64reader.c \
../platform/modules/d64fat/impl/d64sect.c 

OBJS += \
./platform/modules/d64fat/impl/d64reader.o \
./platform/modules/d64fat/impl/d64sect.o 

C_DEPS += \
./platform/modules/d64fat/impl/d64reader.d \
./platform/modules/d64fat/impl/d64sect.d 


# Each subdirectory must supply rules for building sources it contributes
platform/modules/d64fat/impl/%.o: ../platform/modules/d64fat/impl/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


