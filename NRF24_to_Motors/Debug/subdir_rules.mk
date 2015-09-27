################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
NRF24_to_Motors.cpp: ../NRF24_to_Motors.ino
	@echo 'Building file: $<'
	@echo 'Invoking: Resource Custom Build Step'
	
	@echo 'Finished building: $<'
	@echo ' '

%.o: ./%.cpp $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: GNU Compiler'
	"F:/MCUs_related/energia-0101E0015/hardware/tools/lm4f/bin/arm-none-eabi-gcc.exe" -c -mcpu=cortex-m4 -march=armv7e-m -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -fno-exceptions -DF_CPU=80000000L -DPART_TM4C123GH6PM -DARDUINO=101 -DENERGIA=13 -I"F:/MCUs_related/energia-0101E0015/hardware/lm4f/cores/lm4f" -I"F:/MCUs_related/energia-0101E0015/hardware/lm4f/variants/stellarpad" -I"F:/MCUs_related/energia-0101E0015/hardware/tools/lm4f/arm-none-eabi/include" -I"D:/GoogleDrive/Workspaces/Workspaces CCS/Maker_Fair/NRF24_to_Motors" -I"F:/MCUs_related/energia-0101E0015/hardware/lm4f/libraries/SPI" -I"F:/MCUs_related/energia-0101E0015/hardware/lm4f/libraries/Enrf24" -O0 -ffunction-sections -fdata-sections -g -gdwarf-3 -gstrict-dwarf -Wall -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -fno-rtti -o"$@" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

%.o: ../%.cpp $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: GNU Compiler'
	"F:/MCUs_related/energia-0101E0015/hardware/tools/lm4f/bin/arm-none-eabi-gcc.exe" -c -mcpu=cortex-m4 -march=armv7e-m -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -fno-exceptions -DF_CPU=80000000L -DPART_TM4C123GH6PM -DARDUINO=101 -DENERGIA=13 -I"F:/MCUs_related/energia-0101E0015/hardware/lm4f/cores/lm4f" -I"F:/MCUs_related/energia-0101E0015/hardware/lm4f/variants/stellarpad" -I"F:/MCUs_related/energia-0101E0015/hardware/tools/lm4f/arm-none-eabi/include" -I"D:/GoogleDrive/Workspaces/Workspaces CCS/Maker_Fair/NRF24_to_Motors" -I"F:/MCUs_related/energia-0101E0015/hardware/lm4f/libraries/SPI" -I"F:/MCUs_related/energia-0101E0015/hardware/lm4f/libraries/Enrf24" -O0 -ffunction-sections -fdata-sections -g -gdwarf-3 -gstrict-dwarf -Wall -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -fno-rtti -o"$@" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


