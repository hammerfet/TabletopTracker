################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/subdir.mk
-include emlib/subdir.mk
-include CMSIS/efm32zg/subdir.mk
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
all: TabletopTracker.axf

# Tool invocations
TabletopTracker.axf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: GNU ARM C Linker'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m0plus -mthumb -T "TabletopTracker.ld" -Xlinker --gc-sections -Xlinker -Map="TabletopTracker.map" --specs=nano.specs -o TabletopTracker.axf "./src/InitDevice.o" "./src/led_driver.o" "./src/main.o" "./src/random_values.o" "./src/state_machine.o" "./emlib/em_cmu.o" "./emlib/em_emu.o" "./emlib/em_gpio.o" "./emlib/em_system.o" "./emlib/em_timer.o" "./CMSIS/efm32zg/startup_gcc_efm32zg.o" "./CMSIS/efm32zg/system_efm32zg.o" -Wl,--start-group -lgcc -lc -lnosys -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

	@echo 'Building hex file: TabletopTracker.hex'
	arm-none-eabi-objcopy -O ihex "TabletopTracker.axf" "TabletopTracker.hex"
	@echo ' '

	@echo 'Building bin file: TabletopTracker.bin'
	arm-none-eabi-objcopy -O binary "TabletopTracker.axf" "TabletopTracker.bin"
	@echo ' '

	@echo 'Running size tool'
	arm-none-eabi-size "TabletopTracker.axf"
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(C_DEPS)$(EXECUTABLES) TabletopTracker.axf
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
