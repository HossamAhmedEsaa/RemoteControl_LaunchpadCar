################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := F:/MCUs_related/energia-0101E0015/hardware/tools/lm4f

ORDERED_OBJS += \
"./drv8833.o" \
"./NRF24_to_Motors.o" \
"./Speed_Control.o" \
$(GEN_CMDS__FLAG) \
-Wl,--start-group \
-Wl,-T"F:/MCUs_related/energia-0101E0015/hardware/lm4f/cores/lm4f/lm4fcpp_blizzard.ld" \
-l"lptm4c1230c3pm_Enrf24" \
-l"lptm4c1230c3pm_SPI" \
-l"lptm4c1230c3pm_core" \
-l"m" \
-l"c" \
-l"gcc" \
-Wl,--end-group \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(INO_DEPS)),)
-include $(INO_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(PDE_DEPS)),)
-include $(PDE_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXE_OUTPUTS += \
NRF24_to_Motors.out \

EXE_OUTPUTS__QUOTED += \
"NRF24_to_Motors.out" \

BIN_OUTPUTS += \
NRF24_to_Motors.bin \

BIN_OUTPUTS__QUOTED += \
"NRF24_to_Motors.bin" \


# All Target
all: NRF24_to_Motors.out secondary-outputs

dependents:
	-cd D:/GoogleDrive/Workspaces/Workspaces\ CCS/Maker_Fair/lptm4c1230c3pm_core/Debug && $(MAKE) clean all
	-cd D:/GoogleDrive/Workspaces/Workspaces\ CCS/Maker_Fair/lptm4c1230c3pm_SPI/Debug && $(MAKE) clean all
	-cd D:/GoogleDrive/Workspaces/Workspaces\ CCS/Maker_Fair/lptm4c1230c3pm_Enrf24/Debug && $(MAKE) clean all

# Tool invocations
NRF24_to_Motors.out: $(OBJS) $(GEN_CMDS) D:/GoogleDrive/Workspaces/Workspaces\ CCS/Maker_Fair/lptm4c1230c3pm_core/Debug/liblptm4c1230c3pm_core.a D:/GoogleDrive/Workspaces/Workspaces\ CCS/Maker_Fair/lptm4c1230c3pm_SPI/Debug/liblptm4c1230c3pm_SPI.a D:/GoogleDrive/Workspaces/Workspaces\ CCS/Maker_Fair/lptm4c1230c3pm_Enrf24/Debug/liblptm4c1230c3pm_Enrf24.a
	@echo 'Building target: $@'
	@echo 'Invoking: GNU Linker'
	"F:/MCUs_related/energia-0101E0015/hardware/tools/lm4f/bin/arm-none-eabi-gcc.exe" -march=armv7e-m -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -fno-exceptions -DF_CPU=80000000L -DPART_TM4C123GH6PM -DARDUINO=101 -DENERGIA=13 -O0 -ffunction-sections -fdata-sections -g -gdwarf-3 -gstrict-dwarf -Wall --entry ResetISR -nostartfiles -nostdlib -Wl,--gc-sections -L"D:/GoogleDrive/Workspaces/Workspaces CCS/Maker_Fair/lptm4c1230c3pm_core/Debug" -L"D:/GoogleDrive/Workspaces/Workspaces CCS/Maker_Fair/NRF24_to_Motors" -L"D:/GoogleDrive/Workspaces/Workspaces CCS/Maker_Fair/lptm4c1230c3pm_SPI/Debug" -L"D:/GoogleDrive/Workspaces/Workspaces CCS/Maker_Fair/lptm4c1230c3pm_Enrf24/Debug" -o"NRF24_to_Motors.out" $(ORDERED_OBJS)
	@echo 'Finished building target: $@'
	@echo ' '

NRF24_to_Motors.bin: $(EXE_OUTPUTS)
	@echo 'Invoking: GNU Objcopy Utility'
	"F:/MCUs_related/energia-0101E0015/hardware/tools/lm4f/bin/arm-none-eabi-objcopy.exe" -O binary $(EXE_OUTPUTS__QUOTED) "NRF24_to_Motors.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(EXE_OUTPUTS__QUOTED)$(BIN_OUTPUTS__QUOTED)
	-$(RM) "NRF24_to_Motors.d" "Speed_Control.d" "drv8833.d" 
	-$(RM) "NRF24_to_Motors.o" "Speed_Control.o" "drv8833.o" 
	-@echo 'Finished clean'
	-@echo ' '

secondary-outputs: $(BIN_OUTPUTS)

.PHONY: all clean dependents
.SECONDARY:
D:/GoogleDrive/Workspaces/Workspaces\ CCS/Maker_Fair/lptm4c1230c3pm_core/Debug/liblptm4c1230c3pm_core.a:
D:/GoogleDrive/Workspaces/Workspaces\ CCS/Maker_Fair/lptm4c1230c3pm_SPI/Debug/liblptm4c1230c3pm_SPI.a:
D:/GoogleDrive/Workspaces/Workspaces\ CCS/Maker_Fair/lptm4c1230c3pm_Enrf24/Debug/liblptm4c1230c3pm_Enrf24.a:

-include ../makefile.targets

