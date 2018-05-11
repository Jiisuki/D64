################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include platform/modules/iec/impl/subdir.mk
-include platform/modules/flash/impl/subdir.mk
-include platform/modules/fifo/impl/subdir.mk
-include platform/modules/delay/impl/subdir.mk
-include platform/modules/d64fat/impl/subdir.mk
-include bsp/devices/MKE06Z4/drivers/subdir.mk
-include bsp/devices/MKE06Z4/cmsis_drivers/subdir.mk
-include bsp/devices/MKE06Z4/subdir.mk
-include bsp/subdir.mk
-include application/modules/d64sm/impl/subdir.mk
-include application/main/impl/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: d64.exe

# Tool invocations
d64.exe: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: Cygwin C Linker'
	gcc  -o "d64.exe" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(EXECUTABLES)$(OBJS)$(C_DEPS) d64.exe
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
