################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../bsp/devices/MKE06Z4/drivers/fsl_acmp.c \
../bsp/devices/MKE06Z4/drivers/fsl_adc.c \
../bsp/devices/MKE06Z4/drivers/fsl_clock.c \
../bsp/devices/MKE06Z4/drivers/fsl_common.c \
../bsp/devices/MKE06Z4/drivers/fsl_flash.c \
../bsp/devices/MKE06Z4/drivers/fsl_ftm.c \
../bsp/devices/MKE06Z4/drivers/fsl_gpio.c \
../bsp/devices/MKE06Z4/drivers/fsl_i2c.c \
../bsp/devices/MKE06Z4/drivers/fsl_irq.c \
../bsp/devices/MKE06Z4/drivers/fsl_kbi.c \
../bsp/devices/MKE06Z4/drivers/fsl_mscan.c \
../bsp/devices/MKE06Z4/drivers/fsl_pit.c \
../bsp/devices/MKE06Z4/drivers/fsl_port.c \
../bsp/devices/MKE06Z4/drivers/fsl_pwt.c \
../bsp/devices/MKE06Z4/drivers/fsl_rtc.c \
../bsp/devices/MKE06Z4/drivers/fsl_spi.c \
../bsp/devices/MKE06Z4/drivers/fsl_tpm.c \
../bsp/devices/MKE06Z4/drivers/fsl_uart.c \
../bsp/devices/MKE06Z4/drivers/fsl_wdog8.c 

OBJS += \
./bsp/devices/MKE06Z4/drivers/fsl_acmp.o \
./bsp/devices/MKE06Z4/drivers/fsl_adc.o \
./bsp/devices/MKE06Z4/drivers/fsl_clock.o \
./bsp/devices/MKE06Z4/drivers/fsl_common.o \
./bsp/devices/MKE06Z4/drivers/fsl_flash.o \
./bsp/devices/MKE06Z4/drivers/fsl_ftm.o \
./bsp/devices/MKE06Z4/drivers/fsl_gpio.o \
./bsp/devices/MKE06Z4/drivers/fsl_i2c.o \
./bsp/devices/MKE06Z4/drivers/fsl_irq.o \
./bsp/devices/MKE06Z4/drivers/fsl_kbi.o \
./bsp/devices/MKE06Z4/drivers/fsl_mscan.o \
./bsp/devices/MKE06Z4/drivers/fsl_pit.o \
./bsp/devices/MKE06Z4/drivers/fsl_port.o \
./bsp/devices/MKE06Z4/drivers/fsl_pwt.o \
./bsp/devices/MKE06Z4/drivers/fsl_rtc.o \
./bsp/devices/MKE06Z4/drivers/fsl_spi.o \
./bsp/devices/MKE06Z4/drivers/fsl_tpm.o \
./bsp/devices/MKE06Z4/drivers/fsl_uart.o \
./bsp/devices/MKE06Z4/drivers/fsl_wdog8.o 

C_DEPS += \
./bsp/devices/MKE06Z4/drivers/fsl_acmp.d \
./bsp/devices/MKE06Z4/drivers/fsl_adc.d \
./bsp/devices/MKE06Z4/drivers/fsl_clock.d \
./bsp/devices/MKE06Z4/drivers/fsl_common.d \
./bsp/devices/MKE06Z4/drivers/fsl_flash.d \
./bsp/devices/MKE06Z4/drivers/fsl_ftm.d \
./bsp/devices/MKE06Z4/drivers/fsl_gpio.d \
./bsp/devices/MKE06Z4/drivers/fsl_i2c.d \
./bsp/devices/MKE06Z4/drivers/fsl_irq.d \
./bsp/devices/MKE06Z4/drivers/fsl_kbi.d \
./bsp/devices/MKE06Z4/drivers/fsl_mscan.d \
./bsp/devices/MKE06Z4/drivers/fsl_pit.d \
./bsp/devices/MKE06Z4/drivers/fsl_port.d \
./bsp/devices/MKE06Z4/drivers/fsl_pwt.d \
./bsp/devices/MKE06Z4/drivers/fsl_rtc.d \
./bsp/devices/MKE06Z4/drivers/fsl_spi.d \
./bsp/devices/MKE06Z4/drivers/fsl_tpm.d \
./bsp/devices/MKE06Z4/drivers/fsl_uart.d \
./bsp/devices/MKE06Z4/drivers/fsl_wdog8.d 


# Each subdirectory must supply rules for building sources it contributes
bsp/devices/MKE06Z4/drivers/%.o: ../bsp/devices/MKE06Z4/drivers/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


