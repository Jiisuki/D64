################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../bsp/devices/MKE06Z4/cmsis_drivers/fsl_i2c_cmsis.c \
../bsp/devices/MKE06Z4/cmsis_drivers/fsl_spi_cmsis.c \
../bsp/devices/MKE06Z4/cmsis_drivers/fsl_uart_cmsis.c 

OBJS += \
./bsp/devices/MKE06Z4/cmsis_drivers/fsl_i2c_cmsis.o \
./bsp/devices/MKE06Z4/cmsis_drivers/fsl_spi_cmsis.o \
./bsp/devices/MKE06Z4/cmsis_drivers/fsl_uart_cmsis.o 

C_DEPS += \
./bsp/devices/MKE06Z4/cmsis_drivers/fsl_i2c_cmsis.d \
./bsp/devices/MKE06Z4/cmsis_drivers/fsl_spi_cmsis.d \
./bsp/devices/MKE06Z4/cmsis_drivers/fsl_uart_cmsis.d 


# Each subdirectory must supply rules for building sources it contributes
bsp/devices/MKE06Z4/cmsis_drivers/%.o: ../bsp/devices/MKE06Z4/cmsis_drivers/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


