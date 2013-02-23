################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
Communication.obj: ../Communication.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"F:/ti/ccsv5/tools/compiler/c2000_6.1.0/bin/cl2000" -v28 -ml -mt -O0 -g --include_path="F:/ti/ccsv5/tools/compiler/c2000_6.1.0/include" --include_path="F:/ Firmware/sam3s-demo-source/trunk/ sam3s-demo-source --username kaiser.ren@gmail.com/DSP2802x/C2000_LaunchPad" --include_path="/packages/ti/xdais" --define="_FLASH" --define=NDEBUG --define="_DEBUG" --define="LARGE_MODEL" --quiet --verbose_diagnostics --diag_warning=225 --gen_func_subsections=on --output_all_syms --cdebug_asm_data --preproc_with_compile --preproc_dependency="Communication.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

F2802x_CodeStartBranch.obj: F:/\ Firmware/sam3s-demo-source/trunk/\ sam3s-demo-source\ --username\ kaiser.ren@gmail.com/DSP2802x/C2000_LaunchPad/f2802x_common/source/F2802x_CodeStartBranch.asm $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"F:/ti/ccsv5/tools/compiler/c2000_6.1.0/bin/cl2000" -v28 -ml -mt -O0 -g --include_path="F:/ti/ccsv5/tools/compiler/c2000_6.1.0/include" --include_path="F:/ Firmware/sam3s-demo-source/trunk/ sam3s-demo-source --username kaiser.ren@gmail.com/DSP2802x/C2000_LaunchPad" --include_path="/packages/ti/xdais" --define="_FLASH" --define=NDEBUG --define="_DEBUG" --define="LARGE_MODEL" --quiet --verbose_diagnostics --diag_warning=225 --gen_func_subsections=on --output_all_syms --cdebug_asm_data --preproc_with_compile --preproc_dependency="F2802x_CodeStartBranch.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

F2802x_CpuTimers.obj: F:/\ Firmware/sam3s-demo-source/trunk/\ sam3s-demo-source\ --username\ kaiser.ren@gmail.com/DSP2802x/C2000_LaunchPad/f2802x_common/source/F2802x_CpuTimers.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"F:/ti/ccsv5/tools/compiler/c2000_6.1.0/bin/cl2000" -v28 -ml -mt -O0 -g --include_path="F:/ti/ccsv5/tools/compiler/c2000_6.1.0/include" --include_path="F:/ Firmware/sam3s-demo-source/trunk/ sam3s-demo-source --username kaiser.ren@gmail.com/DSP2802x/C2000_LaunchPad" --include_path="/packages/ti/xdais" --define="_FLASH" --define=NDEBUG --define="_DEBUG" --define="LARGE_MODEL" --quiet --verbose_diagnostics --diag_warning=225 --gen_func_subsections=on --output_all_syms --cdebug_asm_data --preproc_with_compile --preproc_dependency="F2802x_CpuTimers.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

F2802x_DefaultIsr.obj: F:/\ Firmware/sam3s-demo-source/trunk/\ sam3s-demo-source\ --username\ kaiser.ren@gmail.com/DSP2802x/C2000_LaunchPad/f2802x_common/source/F2802x_DefaultIsr.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"F:/ti/ccsv5/tools/compiler/c2000_6.1.0/bin/cl2000" -v28 -ml -mt -O0 -g --include_path="F:/ti/ccsv5/tools/compiler/c2000_6.1.0/include" --include_path="F:/ Firmware/sam3s-demo-source/trunk/ sam3s-demo-source --username kaiser.ren@gmail.com/DSP2802x/C2000_LaunchPad" --include_path="/packages/ti/xdais" --define="_FLASH" --define=NDEBUG --define="_DEBUG" --define="LARGE_MODEL" --quiet --verbose_diagnostics --diag_warning=225 --gen_func_subsections=on --output_all_syms --cdebug_asm_data --preproc_with_compile --preproc_dependency="F2802x_DefaultIsr.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

F2802x_GlobalVariableDefs.obj: F:/\ Firmware/sam3s-demo-source/trunk/\ sam3s-demo-source\ --username\ kaiser.ren@gmail.com/DSP2802x/C2000_LaunchPad/f2802x_headers/source/F2802x_GlobalVariableDefs.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"F:/ti/ccsv5/tools/compiler/c2000_6.1.0/bin/cl2000" -v28 -ml -mt -O0 -g --include_path="F:/ti/ccsv5/tools/compiler/c2000_6.1.0/include" --include_path="F:/ Firmware/sam3s-demo-source/trunk/ sam3s-demo-source --username kaiser.ren@gmail.com/DSP2802x/C2000_LaunchPad" --include_path="/packages/ti/xdais" --define="_FLASH" --define=NDEBUG --define="_DEBUG" --define="LARGE_MODEL" --quiet --verbose_diagnostics --diag_warning=225 --gen_func_subsections=on --output_all_syms --cdebug_asm_data --preproc_with_compile --preproc_dependency="F2802x_GlobalVariableDefs.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

F2802x_Gpio.obj: F:/\ Firmware/sam3s-demo-source/trunk/\ sam3s-demo-source\ --username\ kaiser.ren@gmail.com/DSP2802x/C2000_LaunchPad/f2802x_common/source/F2802x_Gpio.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"F:/ti/ccsv5/tools/compiler/c2000_6.1.0/bin/cl2000" -v28 -ml -mt -O0 -g --include_path="F:/ti/ccsv5/tools/compiler/c2000_6.1.0/include" --include_path="F:/ Firmware/sam3s-demo-source/trunk/ sam3s-demo-source --username kaiser.ren@gmail.com/DSP2802x/C2000_LaunchPad" --include_path="/packages/ti/xdais" --define="_FLASH" --define=NDEBUG --define="_DEBUG" --define="LARGE_MODEL" --quiet --verbose_diagnostics --diag_warning=225 --gen_func_subsections=on --output_all_syms --cdebug_asm_data --preproc_with_compile --preproc_dependency="F2802x_Gpio.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

F2802x_I2C.obj: F:/\ Firmware/sam3s-demo-source/trunk/\ sam3s-demo-source\ --username\ kaiser.ren@gmail.com/DSP2802x/C2000_LaunchPad/f2802x_common/source/F2802x_I2C.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"F:/ti/ccsv5/tools/compiler/c2000_6.1.0/bin/cl2000" -v28 -ml -mt -O0 -g --include_path="F:/ti/ccsv5/tools/compiler/c2000_6.1.0/include" --include_path="F:/ Firmware/sam3s-demo-source/trunk/ sam3s-demo-source --username kaiser.ren@gmail.com/DSP2802x/C2000_LaunchPad" --include_path="/packages/ti/xdais" --define="_FLASH" --define=NDEBUG --define="_DEBUG" --define="LARGE_MODEL" --quiet --verbose_diagnostics --diag_warning=225 --gen_func_subsections=on --output_all_syms --cdebug_asm_data --preproc_with_compile --preproc_dependency="F2802x_I2C.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

F2802x_PieCtrl.obj: F:/\ Firmware/sam3s-demo-source/trunk/\ sam3s-demo-source\ --username\ kaiser.ren@gmail.com/DSP2802x/C2000_LaunchPad/f2802x_common/source/F2802x_PieCtrl.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"F:/ti/ccsv5/tools/compiler/c2000_6.1.0/bin/cl2000" -v28 -ml -mt -O0 -g --include_path="F:/ti/ccsv5/tools/compiler/c2000_6.1.0/include" --include_path="F:/ Firmware/sam3s-demo-source/trunk/ sam3s-demo-source --username kaiser.ren@gmail.com/DSP2802x/C2000_LaunchPad" --include_path="/packages/ti/xdais" --define="_FLASH" --define=NDEBUG --define="_DEBUG" --define="LARGE_MODEL" --quiet --verbose_diagnostics --diag_warning=225 --gen_func_subsections=on --output_all_syms --cdebug_asm_data --preproc_with_compile --preproc_dependency="F2802x_PieCtrl.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

F2802x_PieVect.obj: F:/\ Firmware/sam3s-demo-source/trunk/\ sam3s-demo-source\ --username\ kaiser.ren@gmail.com/DSP2802x/C2000_LaunchPad/f2802x_common/source/F2802x_PieVect.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"F:/ti/ccsv5/tools/compiler/c2000_6.1.0/bin/cl2000" -v28 -ml -mt -O0 -g --include_path="F:/ti/ccsv5/tools/compiler/c2000_6.1.0/include" --include_path="F:/ Firmware/sam3s-demo-source/trunk/ sam3s-demo-source --username kaiser.ren@gmail.com/DSP2802x/C2000_LaunchPad" --include_path="/packages/ti/xdais" --define="_FLASH" --define=NDEBUG --define="_DEBUG" --define="LARGE_MODEL" --quiet --verbose_diagnostics --diag_warning=225 --gen_func_subsections=on --output_all_syms --cdebug_asm_data --preproc_with_compile --preproc_dependency="F2802x_PieVect.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

F2802x_Sci.obj: F:/\ Firmware/sam3s-demo-source/trunk/\ sam3s-demo-source\ --username\ kaiser.ren@gmail.com/DSP2802x/C2000_LaunchPad/f2802x_common/source/F2802x_Sci.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"F:/ti/ccsv5/tools/compiler/c2000_6.1.0/bin/cl2000" -v28 -ml -mt -O0 -g --include_path="F:/ti/ccsv5/tools/compiler/c2000_6.1.0/include" --include_path="F:/ Firmware/sam3s-demo-source/trunk/ sam3s-demo-source --username kaiser.ren@gmail.com/DSP2802x/C2000_LaunchPad" --include_path="/packages/ti/xdais" --define="_FLASH" --define=NDEBUG --define="_DEBUG" --define="LARGE_MODEL" --quiet --verbose_diagnostics --diag_warning=225 --gen_func_subsections=on --output_all_syms --cdebug_asm_data --preproc_with_compile --preproc_dependency="F2802x_Sci.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

F2802x_SysCtrl.obj: F:/\ Firmware/sam3s-demo-source/trunk/\ sam3s-demo-source\ --username\ kaiser.ren@gmail.com/DSP2802x/C2000_LaunchPad/f2802x_common/source/F2802x_SysCtrl.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"F:/ti/ccsv5/tools/compiler/c2000_6.1.0/bin/cl2000" -v28 -ml -mt -O0 -g --include_path="F:/ti/ccsv5/tools/compiler/c2000_6.1.0/include" --include_path="F:/ Firmware/sam3s-demo-source/trunk/ sam3s-demo-source --username kaiser.ren@gmail.com/DSP2802x/C2000_LaunchPad" --include_path="/packages/ti/xdais" --define="_FLASH" --define=NDEBUG --define="_DEBUG" --define="LARGE_MODEL" --quiet --verbose_diagnostics --diag_warning=225 --gen_func_subsections=on --output_all_syms --cdebug_asm_data --preproc_with_compile --preproc_dependency="F2802x_SysCtrl.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

F2802x_usDelay.obj: F:/\ Firmware/sam3s-demo-source/trunk/\ sam3s-demo-source\ --username\ kaiser.ren@gmail.com/DSP2802x/C2000_LaunchPad/f2802x_common/source/F2802x_usDelay.asm $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"F:/ti/ccsv5/tools/compiler/c2000_6.1.0/bin/cl2000" -v28 -ml -mt -O0 -g --include_path="F:/ti/ccsv5/tools/compiler/c2000_6.1.0/include" --include_path="F:/ Firmware/sam3s-demo-source/trunk/ sam3s-demo-source --username kaiser.ren@gmail.com/DSP2802x/C2000_LaunchPad" --include_path="/packages/ti/xdais" --define="_FLASH" --define=NDEBUG --define="_DEBUG" --define="LARGE_MODEL" --quiet --verbose_diagnostics --diag_warning=225 --gen_func_subsections=on --output_all_syms --cdebug_asm_data --preproc_with_compile --preproc_dependency="F2802x_usDelay.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

ad5933.obj: ../ad5933.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"F:/ti/ccsv5/tools/compiler/c2000_6.1.0/bin/cl2000" -v28 -ml -mt -O0 -g --include_path="F:/ti/ccsv5/tools/compiler/c2000_6.1.0/include" --include_path="F:/ Firmware/sam3s-demo-source/trunk/ sam3s-demo-source --username kaiser.ren@gmail.com/DSP2802x/C2000_LaunchPad" --include_path="/packages/ti/xdais" --define="_FLASH" --define=NDEBUG --define="_DEBUG" --define="LARGE_MODEL" --quiet --verbose_diagnostics --diag_warning=225 --gen_func_subsections=on --output_all_syms --cdebug_asm_data --preproc_with_compile --preproc_dependency="ad5933.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

calc.obj: ../calc.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"F:/ti/ccsv5/tools/compiler/c2000_6.1.0/bin/cl2000" -v28 -ml -mt -O0 -g --include_path="F:/ti/ccsv5/tools/compiler/c2000_6.1.0/include" --include_path="F:/ Firmware/sam3s-demo-source/trunk/ sam3s-demo-source --username kaiser.ren@gmail.com/DSP2802x/C2000_LaunchPad" --include_path="/packages/ti/xdais" --define="_FLASH" --define=NDEBUG --define="_DEBUG" --define="LARGE_MODEL" --quiet --verbose_diagnostics --diag_warning=225 --gen_func_subsections=on --output_all_syms --cdebug_asm_data --preproc_with_compile --preproc_dependency="calc.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

com.obj: ../com.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"F:/ti/ccsv5/tools/compiler/c2000_6.1.0/bin/cl2000" -v28 -ml -mt -O0 -g --include_path="F:/ti/ccsv5/tools/compiler/c2000_6.1.0/include" --include_path="F:/ Firmware/sam3s-demo-source/trunk/ sam3s-demo-source --username kaiser.ren@gmail.com/DSP2802x/C2000_LaunchPad" --include_path="/packages/ti/xdais" --define="_FLASH" --define=NDEBUG --define="_DEBUG" --define="LARGE_MODEL" --quiet --verbose_diagnostics --diag_warning=225 --gen_func_subsections=on --output_all_syms --cdebug_asm_data --preproc_with_compile --preproc_dependency="com.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

main.obj: ../main.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"F:/ti/ccsv5/tools/compiler/c2000_6.1.0/bin/cl2000" -v28 -ml -mt -O0 -g --include_path="F:/ti/ccsv5/tools/compiler/c2000_6.1.0/include" --include_path="F:/ Firmware/sam3s-demo-source/trunk/ sam3s-demo-source --username kaiser.ren@gmail.com/DSP2802x/C2000_LaunchPad" --include_path="/packages/ti/xdais" --define="_FLASH" --define=NDEBUG --define="_DEBUG" --define="LARGE_MODEL" --quiet --verbose_diagnostics --diag_warning=225 --gen_func_subsections=on --output_all_syms --cdebug_asm_data --preproc_with_compile --preproc_dependency="main.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


