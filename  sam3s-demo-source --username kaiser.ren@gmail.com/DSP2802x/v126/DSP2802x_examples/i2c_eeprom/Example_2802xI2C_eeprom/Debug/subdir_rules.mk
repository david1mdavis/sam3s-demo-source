################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
28027_RAM_lnk.exe: D:/Firmware/sam3s-demo-source/trunk/\ sam3s-demo-source\ --username\ kaiser.ren@gmail.com/DSP2802x/v126/DSP2802x_common/cmd/28027_RAM_lnk.cmd $(GEN_CMDS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Linker'
	"D:/Program Files/ti/ccs 5.2/ccsv5/tools/compiler/c2000_6.1.0/bin/cl2000" -v28 -ml -mt -g --define="_DEBUG" --define="LARGE_MODEL" --quiet --display_error_number --issue_remarks --asm_directory="C:/tidcs/c28/DSP2802x/v126/DSP2802x_examples/i2c_eeprom/Debug" --obj_directory="C:/tidcs/c28/DSP2802x/v126/DSP2802x_examples/i2c_eeprom/Debug" -z --stack_size=0x300 -m"D:/Firmware/sam3s-demo-source/trunk/ sam3s-demo-source --username kaiser.ren@gmail.com/DSP2802x/v126/DSP2802x_examples/i2c_eeprom/Debug/Example_2802xI2C_eeprom.map" --heap_size=0x400 --warn_sections -i"D:/Program Files/ti/ccs 5.2/ccsv5/tools/compiler/c2000_6.1.0/lib" -i"D:/Program Files/ti/ccs 5.2/ccsv5/tools/compiler/c2000_6.1.0/include" -i"D:/Firmware/sam3s-demo-source/trunk/ sam3s-demo-source --username kaiser.ren@gmail.com/DSP2802x/v126/DSP2802x_examples/i2c_eeprom/Example_2802xI2C_eeprom" -i"D:/Firmware/sam3s-demo-source/trunk/ sam3s-demo-source --username kaiser.ren@gmail.com/DSP2802x/v126/DSP2802x_examples/i2c_eeprom" -i"D:/Firmware/sam3s-demo-source/trunk/ sam3s-demo-source --username kaiser.ren@gmail.com/DSP2802x/v126/DSP2802x_headers/include" -i"D:/Firmware/sam3s-demo-source/trunk/ sam3s-demo-source --username kaiser.ren@gmail.com/DSP2802x/v126/DSP2802x_common/lib" --reread_libs --display_error_number --entry_point=code_start --rom_model -o "$@" "$<" "../28027_RAM_lnk.cmd" "../DSP2802x_Headers_nonBIOS.cmd" "../F28027.cmd"
	@echo 'Finished building: $<'
	@echo ' '

C:/tidcs/c28/DSP2802x/v126/DSP2802x_examples/i2c_eeprom/Debug/Communication.obj: D:/Firmware/sam3s-demo-source/trunk/\ sam3s-demo-source\ --username\ kaiser.ren@gmail.com/DSP2802x/v126/DSP2802x_examples/i2c_eeprom/Communication.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"D:/Program Files/ti/ccs 5.2/ccsv5/tools/compiler/c2000_6.1.0/bin/cl2000" -v28 -ml -mt -g --include_path="D:/Program Files/ti/ccs 5.2/ccsv5/tools/compiler/c2000_6.1.0/include" --include_path="/packages/ti/xdais" --include_path="D:/Firmware/sam3s-demo-source/trunk/ sam3s-demo-source --username kaiser.ren@gmail.com/DSP2802x/v126/DSP2802x_headers/include" --include_path="D:/Firmware/sam3s-demo-source/trunk/ sam3s-demo-source --username kaiser.ren@gmail.com/DSP2802x/v126/DSP2802x_common/include" --define="_DEBUG" --define="LARGE_MODEL" --quiet --display_error_number --issue_remarks --asm_directory="C:/tidcs/c28/DSP2802x/v126/DSP2802x_examples/i2c_eeprom/Debug" --obj_directory="C:/tidcs/c28/DSP2802x/v126/DSP2802x_examples/i2c_eeprom/Debug" --preproc_with_compile --preproc_dependency="Communication.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

C:/tidcs/c28/DSP2802x/v126/DSP2802x_examples/i2c_eeprom/Debug/DSP2802x_CSMPasswords.obj: D:/Firmware/sam3s-demo-source/trunk/\ sam3s-demo-source\ --username\ kaiser.ren@gmail.com/DSP2802x/v126/DSP2802x_common/source/DSP2802x_CSMPasswords.asm $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"D:/Program Files/ti/ccs 5.2/ccsv5/tools/compiler/c2000_6.1.0/bin/cl2000" -v28 -ml -mt -g --include_path="D:/Program Files/ti/ccs 5.2/ccsv5/tools/compiler/c2000_6.1.0/include" --include_path="/packages/ti/xdais" --include_path="D:/Firmware/sam3s-demo-source/trunk/ sam3s-demo-source --username kaiser.ren@gmail.com/DSP2802x/v126/DSP2802x_headers/include" --include_path="D:/Firmware/sam3s-demo-source/trunk/ sam3s-demo-source --username kaiser.ren@gmail.com/DSP2802x/v126/DSP2802x_common/include" --define="_DEBUG" --define="LARGE_MODEL" --quiet --display_error_number --issue_remarks --asm_directory="C:/tidcs/c28/DSP2802x/v126/DSP2802x_examples/i2c_eeprom/Debug" --obj_directory="C:/tidcs/c28/DSP2802x/v126/DSP2802x_examples/i2c_eeprom/Debug" --preproc_with_compile --preproc_dependency="DSP2802x_CSMPasswords.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

C:/tidcs/c28/DSP2802x/v126/DSP2802x_examples/i2c_eeprom/Debug/DSP2802x_CodeStartBranch.obj: D:/Firmware/sam3s-demo-source/trunk/\ sam3s-demo-source\ --username\ kaiser.ren@gmail.com/DSP2802x/v126/DSP2802x_common/source/DSP2802x_CodeStartBranch.asm $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"D:/Program Files/ti/ccs 5.2/ccsv5/tools/compiler/c2000_6.1.0/bin/cl2000" -v28 -ml -mt -g --include_path="D:/Program Files/ti/ccs 5.2/ccsv5/tools/compiler/c2000_6.1.0/include" --include_path="/packages/ti/xdais" --include_path="D:/Firmware/sam3s-demo-source/trunk/ sam3s-demo-source --username kaiser.ren@gmail.com/DSP2802x/v126/DSP2802x_headers/include" --include_path="D:/Firmware/sam3s-demo-source/trunk/ sam3s-demo-source --username kaiser.ren@gmail.com/DSP2802x/v126/DSP2802x_common/include" --define="_DEBUG" --define="LARGE_MODEL" --quiet --display_error_number --issue_remarks --asm_directory="C:/tidcs/c28/DSP2802x/v126/DSP2802x_examples/i2c_eeprom/Debug" --obj_directory="C:/tidcs/c28/DSP2802x/v126/DSP2802x_examples/i2c_eeprom/Debug" --preproc_with_compile --preproc_dependency="DSP2802x_CodeStartBranch.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

C:/tidcs/c28/DSP2802x/v126/DSP2802x_examples/i2c_eeprom/Debug/DSP2802x_CpuTimers.obj: D:/Firmware/sam3s-demo-source/trunk/\ sam3s-demo-source\ --username\ kaiser.ren@gmail.com/DSP2802x/v126/DSP2802x_common/source/DSP2802x_CpuTimers.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"D:/Program Files/ti/ccs 5.2/ccsv5/tools/compiler/c2000_6.1.0/bin/cl2000" -v28 -ml -mt -g --include_path="D:/Program Files/ti/ccs 5.2/ccsv5/tools/compiler/c2000_6.1.0/include" --include_path="/packages/ti/xdais" --include_path="D:/Firmware/sam3s-demo-source/trunk/ sam3s-demo-source --username kaiser.ren@gmail.com/DSP2802x/v126/DSP2802x_headers/include" --include_path="D:/Firmware/sam3s-demo-source/trunk/ sam3s-demo-source --username kaiser.ren@gmail.com/DSP2802x/v126/DSP2802x_common/include" --define="_DEBUG" --define="LARGE_MODEL" --quiet --display_error_number --issue_remarks --asm_directory="C:/tidcs/c28/DSP2802x/v126/DSP2802x_examples/i2c_eeprom/Debug" --obj_directory="C:/tidcs/c28/DSP2802x/v126/DSP2802x_examples/i2c_eeprom/Debug" --preproc_with_compile --preproc_dependency="DSP2802x_CpuTimers.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

C:/tidcs/c28/DSP2802x/v126/DSP2802x_examples/i2c_eeprom/Debug/DSP2802x_DefaultIsr.obj: D:/Firmware/sam3s-demo-source/trunk/\ sam3s-demo-source\ --username\ kaiser.ren@gmail.com/DSP2802x/v126/DSP2802x_common/source/DSP2802x_DefaultIsr.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"D:/Program Files/ti/ccs 5.2/ccsv5/tools/compiler/c2000_6.1.0/bin/cl2000" -v28 -ml -mt -g --include_path="D:/Program Files/ti/ccs 5.2/ccsv5/tools/compiler/c2000_6.1.0/include" --include_path="/packages/ti/xdais" --include_path="D:/Firmware/sam3s-demo-source/trunk/ sam3s-demo-source --username kaiser.ren@gmail.com/DSP2802x/v126/DSP2802x_headers/include" --include_path="D:/Firmware/sam3s-demo-source/trunk/ sam3s-demo-source --username kaiser.ren@gmail.com/DSP2802x/v126/DSP2802x_common/include" --define="_DEBUG" --define="LARGE_MODEL" --quiet --display_error_number --issue_remarks --asm_directory="C:/tidcs/c28/DSP2802x/v126/DSP2802x_examples/i2c_eeprom/Debug" --obj_directory="C:/tidcs/c28/DSP2802x/v126/DSP2802x_examples/i2c_eeprom/Debug" --preproc_with_compile --preproc_dependency="DSP2802x_DefaultIsr.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

C:/tidcs/c28/DSP2802x/v126/DSP2802x_examples/i2c_eeprom/Debug/DSP2802x_GlobalVariableDefs.obj: D:/Firmware/sam3s-demo-source/trunk/\ sam3s-demo-source\ --username\ kaiser.ren@gmail.com/DSP2802x/v126/DSP2802x_headers/source/DSP2802x_GlobalVariableDefs.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"D:/Program Files/ti/ccs 5.2/ccsv5/tools/compiler/c2000_6.1.0/bin/cl2000" -v28 -ml -mt -g --include_path="D:/Program Files/ti/ccs 5.2/ccsv5/tools/compiler/c2000_6.1.0/include" --include_path="/packages/ti/xdais" --include_path="D:/Firmware/sam3s-demo-source/trunk/ sam3s-demo-source --username kaiser.ren@gmail.com/DSP2802x/v126/DSP2802x_headers/include" --include_path="D:/Firmware/sam3s-demo-source/trunk/ sam3s-demo-source --username kaiser.ren@gmail.com/DSP2802x/v126/DSP2802x_common/include" --define="_DEBUG" --define="LARGE_MODEL" --quiet --display_error_number --issue_remarks --asm_directory="C:/tidcs/c28/DSP2802x/v126/DSP2802x_examples/i2c_eeprom/Debug" --obj_directory="C:/tidcs/c28/DSP2802x/v126/DSP2802x_examples/i2c_eeprom/Debug" --preproc_with_compile --preproc_dependency="DSP2802x_GlobalVariableDefs.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

C:/tidcs/c28/DSP2802x/v126/DSP2802x_examples/i2c_eeprom/Debug/DSP2802x_Gpio.obj: D:/Firmware/sam3s-demo-source/trunk/\ sam3s-demo-source\ --username\ kaiser.ren@gmail.com/DSP2802x/v126/DSP2802x_common/source/DSP2802x_Gpio.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"D:/Program Files/ti/ccs 5.2/ccsv5/tools/compiler/c2000_6.1.0/bin/cl2000" -v28 -ml -mt -g --include_path="D:/Program Files/ti/ccs 5.2/ccsv5/tools/compiler/c2000_6.1.0/include" --include_path="/packages/ti/xdais" --include_path="D:/Firmware/sam3s-demo-source/trunk/ sam3s-demo-source --username kaiser.ren@gmail.com/DSP2802x/v126/DSP2802x_headers/include" --include_path="D:/Firmware/sam3s-demo-source/trunk/ sam3s-demo-source --username kaiser.ren@gmail.com/DSP2802x/v126/DSP2802x_common/include" --define="_DEBUG" --define="LARGE_MODEL" --quiet --display_error_number --issue_remarks --asm_directory="C:/tidcs/c28/DSP2802x/v126/DSP2802x_examples/i2c_eeprom/Debug" --obj_directory="C:/tidcs/c28/DSP2802x/v126/DSP2802x_examples/i2c_eeprom/Debug" --preproc_with_compile --preproc_dependency="DSP2802x_Gpio.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

C:/tidcs/c28/DSP2802x/v126/DSP2802x_examples/i2c_eeprom/Debug/DSP2802x_I2C.obj: D:/Firmware/sam3s-demo-source/trunk/\ sam3s-demo-source\ --username\ kaiser.ren@gmail.com/DSP2802x/v126/DSP2802x_common/source/DSP2802x_I2C.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"D:/Program Files/ti/ccs 5.2/ccsv5/tools/compiler/c2000_6.1.0/bin/cl2000" -v28 -ml -mt -g --include_path="D:/Program Files/ti/ccs 5.2/ccsv5/tools/compiler/c2000_6.1.0/include" --include_path="/packages/ti/xdais" --include_path="D:/Firmware/sam3s-demo-source/trunk/ sam3s-demo-source --username kaiser.ren@gmail.com/DSP2802x/v126/DSP2802x_headers/include" --include_path="D:/Firmware/sam3s-demo-source/trunk/ sam3s-demo-source --username kaiser.ren@gmail.com/DSP2802x/v126/DSP2802x_common/include" --define="_DEBUG" --define="LARGE_MODEL" --quiet --display_error_number --issue_remarks --asm_directory="C:/tidcs/c28/DSP2802x/v126/DSP2802x_examples/i2c_eeprom/Debug" --obj_directory="C:/tidcs/c28/DSP2802x/v126/DSP2802x_examples/i2c_eeprom/Debug" --preproc_with_compile --preproc_dependency="DSP2802x_I2C.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

C:/tidcs/c28/DSP2802x/v126/DSP2802x_examples/i2c_eeprom/Debug/DSP2802x_PieCtrl.obj: D:/Firmware/sam3s-demo-source/trunk/\ sam3s-demo-source\ --username\ kaiser.ren@gmail.com/DSP2802x/v126/DSP2802x_common/source/DSP2802x_PieCtrl.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"D:/Program Files/ti/ccs 5.2/ccsv5/tools/compiler/c2000_6.1.0/bin/cl2000" -v28 -ml -mt -g --include_path="D:/Program Files/ti/ccs 5.2/ccsv5/tools/compiler/c2000_6.1.0/include" --include_path="/packages/ti/xdais" --include_path="D:/Firmware/sam3s-demo-source/trunk/ sam3s-demo-source --username kaiser.ren@gmail.com/DSP2802x/v126/DSP2802x_headers/include" --include_path="D:/Firmware/sam3s-demo-source/trunk/ sam3s-demo-source --username kaiser.ren@gmail.com/DSP2802x/v126/DSP2802x_common/include" --define="_DEBUG" --define="LARGE_MODEL" --quiet --display_error_number --issue_remarks --asm_directory="C:/tidcs/c28/DSP2802x/v126/DSP2802x_examples/i2c_eeprom/Debug" --obj_directory="C:/tidcs/c28/DSP2802x/v126/DSP2802x_examples/i2c_eeprom/Debug" --preproc_with_compile --preproc_dependency="DSP2802x_PieCtrl.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

C:/tidcs/c28/DSP2802x/v126/DSP2802x_examples/i2c_eeprom/Debug/DSP2802x_PieVect.obj: D:/Firmware/sam3s-demo-source/trunk/\ sam3s-demo-source\ --username\ kaiser.ren@gmail.com/DSP2802x/v126/DSP2802x_common/source/DSP2802x_PieVect.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"D:/Program Files/ti/ccs 5.2/ccsv5/tools/compiler/c2000_6.1.0/bin/cl2000" -v28 -ml -mt -g --include_path="D:/Program Files/ti/ccs 5.2/ccsv5/tools/compiler/c2000_6.1.0/include" --include_path="/packages/ti/xdais" --include_path="D:/Firmware/sam3s-demo-source/trunk/ sam3s-demo-source --username kaiser.ren@gmail.com/DSP2802x/v126/DSP2802x_headers/include" --include_path="D:/Firmware/sam3s-demo-source/trunk/ sam3s-demo-source --username kaiser.ren@gmail.com/DSP2802x/v126/DSP2802x_common/include" --define="_DEBUG" --define="LARGE_MODEL" --quiet --display_error_number --issue_remarks --asm_directory="C:/tidcs/c28/DSP2802x/v126/DSP2802x_examples/i2c_eeprom/Debug" --obj_directory="C:/tidcs/c28/DSP2802x/v126/DSP2802x_examples/i2c_eeprom/Debug" --preproc_with_compile --preproc_dependency="DSP2802x_PieVect.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

C:/tidcs/c28/DSP2802x/v126/DSP2802x_examples/i2c_eeprom/Debug/DSP2802x_Sci.obj: D:/Firmware/sam3s-demo-source/trunk/\ sam3s-demo-source\ --username\ kaiser.ren@gmail.com/DSP2802x/v126/DSP2802x_common/source/DSP2802x_Sci.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"D:/Program Files/ti/ccs 5.2/ccsv5/tools/compiler/c2000_6.1.0/bin/cl2000" -v28 -ml -mt -g --include_path="D:/Program Files/ti/ccs 5.2/ccsv5/tools/compiler/c2000_6.1.0/include" --include_path="/packages/ti/xdais" --include_path="D:/Firmware/sam3s-demo-source/trunk/ sam3s-demo-source --username kaiser.ren@gmail.com/DSP2802x/v126/DSP2802x_headers/include" --include_path="D:/Firmware/sam3s-demo-source/trunk/ sam3s-demo-source --username kaiser.ren@gmail.com/DSP2802x/v126/DSP2802x_common/include" --define="_DEBUG" --define="LARGE_MODEL" --quiet --display_error_number --issue_remarks --asm_directory="C:/tidcs/c28/DSP2802x/v126/DSP2802x_examples/i2c_eeprom/Debug" --obj_directory="C:/tidcs/c28/DSP2802x/v126/DSP2802x_examples/i2c_eeprom/Debug" --preproc_with_compile --preproc_dependency="DSP2802x_Sci.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

C:/tidcs/c28/DSP2802x/v126/DSP2802x_examples/i2c_eeprom/Debug/DSP2802x_SysCtrl.obj: D:/Firmware/sam3s-demo-source/trunk/\ sam3s-demo-source\ --username\ kaiser.ren@gmail.com/DSP2802x/v126/DSP2802x_common/source/DSP2802x_SysCtrl.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"D:/Program Files/ti/ccs 5.2/ccsv5/tools/compiler/c2000_6.1.0/bin/cl2000" -v28 -ml -mt -g --include_path="D:/Program Files/ti/ccs 5.2/ccsv5/tools/compiler/c2000_6.1.0/include" --include_path="/packages/ti/xdais" --include_path="D:/Firmware/sam3s-demo-source/trunk/ sam3s-demo-source --username kaiser.ren@gmail.com/DSP2802x/v126/DSP2802x_headers/include" --include_path="D:/Firmware/sam3s-demo-source/trunk/ sam3s-demo-source --username kaiser.ren@gmail.com/DSP2802x/v126/DSP2802x_common/include" --define="_DEBUG" --define="LARGE_MODEL" --quiet --display_error_number --issue_remarks --asm_directory="C:/tidcs/c28/DSP2802x/v126/DSP2802x_examples/i2c_eeprom/Debug" --obj_directory="C:/tidcs/c28/DSP2802x/v126/DSP2802x_examples/i2c_eeprom/Debug" --preproc_with_compile --preproc_dependency="DSP2802x_SysCtrl.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

C:/tidcs/c28/DSP2802x/v126/DSP2802x_examples/i2c_eeprom/Debug/DSP2802x_usDelay.obj: D:/Firmware/sam3s-demo-source/trunk/\ sam3s-demo-source\ --username\ kaiser.ren@gmail.com/DSP2802x/v126/DSP2802x_common/source/DSP2802x_usDelay.asm $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"D:/Program Files/ti/ccs 5.2/ccsv5/tools/compiler/c2000_6.1.0/bin/cl2000" -v28 -ml -mt -g --include_path="D:/Program Files/ti/ccs 5.2/ccsv5/tools/compiler/c2000_6.1.0/include" --include_path="/packages/ti/xdais" --include_path="D:/Firmware/sam3s-demo-source/trunk/ sam3s-demo-source --username kaiser.ren@gmail.com/DSP2802x/v126/DSP2802x_headers/include" --include_path="D:/Firmware/sam3s-demo-source/trunk/ sam3s-demo-source --username kaiser.ren@gmail.com/DSP2802x/v126/DSP2802x_common/include" --define="_DEBUG" --define="LARGE_MODEL" --quiet --display_error_number --issue_remarks --asm_directory="C:/tidcs/c28/DSP2802x/v126/DSP2802x_examples/i2c_eeprom/Debug" --obj_directory="C:/tidcs/c28/DSP2802x/v126/DSP2802x_examples/i2c_eeprom/Debug" --preproc_with_compile --preproc_dependency="DSP2802x_usDelay.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

C:/tidcs/c28/DSP2802x/v126/DSP2802x_examples/i2c_eeprom/Debug/ad5933.obj: D:/Firmware/sam3s-demo-source/trunk/\ sam3s-demo-source\ --username\ kaiser.ren@gmail.com/DSP2802x/v126/DSP2802x_examples/i2c_eeprom/ad5933.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"D:/Program Files/ti/ccs 5.2/ccsv5/tools/compiler/c2000_6.1.0/bin/cl2000" -v28 -ml -mt -g --include_path="D:/Program Files/ti/ccs 5.2/ccsv5/tools/compiler/c2000_6.1.0/include" --include_path="/packages/ti/xdais" --include_path="D:/Firmware/sam3s-demo-source/trunk/ sam3s-demo-source --username kaiser.ren@gmail.com/DSP2802x/v126/DSP2802x_headers/include" --include_path="D:/Firmware/sam3s-demo-source/trunk/ sam3s-demo-source --username kaiser.ren@gmail.com/DSP2802x/v126/DSP2802x_common/include" --define="_DEBUG" --define="LARGE_MODEL" --quiet --display_error_number --issue_remarks --asm_directory="C:/tidcs/c28/DSP2802x/v126/DSP2802x_examples/i2c_eeprom/Debug" --obj_directory="C:/tidcs/c28/DSP2802x/v126/DSP2802x_examples/i2c_eeprom/Debug" --preproc_with_compile --preproc_dependency="ad5933.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

C:/tidcs/c28/DSP2802x/v126/DSP2802x_examples/i2c_eeprom/Debug/calc.obj: ../calc.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"D:/Program Files/ti/ccs 5.2/ccsv5/tools/compiler/c2000_6.1.0/bin/cl2000" -v28 -ml -mt -g --include_path="D:/Program Files/ti/ccs 5.2/ccsv5/tools/compiler/c2000_6.1.0/include" --include_path="/packages/ti/xdais" --include_path="D:/Firmware/sam3s-demo-source/trunk/ sam3s-demo-source --username kaiser.ren@gmail.com/DSP2802x/v126/DSP2802x_headers/include" --include_path="D:/Firmware/sam3s-demo-source/trunk/ sam3s-demo-source --username kaiser.ren@gmail.com/DSP2802x/v126/DSP2802x_common/include" --define="_DEBUG" --define="LARGE_MODEL" --quiet --display_error_number --issue_remarks --asm_directory="C:/tidcs/c28/DSP2802x/v126/DSP2802x_examples/i2c_eeprom/Debug" --obj_directory="C:/tidcs/c28/DSP2802x/v126/DSP2802x_examples/i2c_eeprom/Debug" --preproc_with_compile --preproc_dependency="calc.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

C:/tidcs/c28/DSP2802x/v126/DSP2802x_examples/i2c_eeprom/Debug/com.obj: ../com.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"D:/Program Files/ti/ccs 5.2/ccsv5/tools/compiler/c2000_6.1.0/bin/cl2000" -v28 -ml -mt -g --include_path="D:/Program Files/ti/ccs 5.2/ccsv5/tools/compiler/c2000_6.1.0/include" --include_path="/packages/ti/xdais" --include_path="D:/Firmware/sam3s-demo-source/trunk/ sam3s-demo-source --username kaiser.ren@gmail.com/DSP2802x/v126/DSP2802x_headers/include" --include_path="D:/Firmware/sam3s-demo-source/trunk/ sam3s-demo-source --username kaiser.ren@gmail.com/DSP2802x/v126/DSP2802x_common/include" --define="_DEBUG" --define="LARGE_MODEL" --quiet --display_error_number --issue_remarks --asm_directory="C:/tidcs/c28/DSP2802x/v126/DSP2802x_examples/i2c_eeprom/Debug" --obj_directory="C:/tidcs/c28/DSP2802x/v126/DSP2802x_examples/i2c_eeprom/Debug" --preproc_with_compile --preproc_dependency="com.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

C:/tidcs/c28/DSP2802x/v126/DSP2802x_examples/i2c_eeprom/Debug/main.obj: D:/Firmware/sam3s-demo-source/trunk/\ sam3s-demo-source\ --username\ kaiser.ren@gmail.com/DSP2802x/v126/DSP2802x_examples/i2c_eeprom/main.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"D:/Program Files/ti/ccs 5.2/ccsv5/tools/compiler/c2000_6.1.0/bin/cl2000" -v28 -ml -mt -g --include_path="D:/Program Files/ti/ccs 5.2/ccsv5/tools/compiler/c2000_6.1.0/include" --include_path="/packages/ti/xdais" --include_path="D:/Firmware/sam3s-demo-source/trunk/ sam3s-demo-source --username kaiser.ren@gmail.com/DSP2802x/v126/DSP2802x_headers/include" --include_path="D:/Firmware/sam3s-demo-source/trunk/ sam3s-demo-source --username kaiser.ren@gmail.com/DSP2802x/v126/DSP2802x_common/include" --define="_DEBUG" --define="LARGE_MODEL" --quiet --display_error_number --issue_remarks --asm_directory="C:/tidcs/c28/DSP2802x/v126/DSP2802x_examples/i2c_eeprom/Debug" --obj_directory="C:/tidcs/c28/DSP2802x/v126/DSP2802x_examples/i2c_eeprom/Debug" --preproc_with_compile --preproc_dependency="main.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


