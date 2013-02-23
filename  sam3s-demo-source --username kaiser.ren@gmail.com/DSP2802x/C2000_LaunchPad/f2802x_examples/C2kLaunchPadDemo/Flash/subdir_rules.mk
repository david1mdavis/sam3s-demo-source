################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
Example_F2802xLaunchPadDemo.obj: ../Example_F2802xLaunchPadDemo.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"F:/ti/ccsv5/tools/compiler/c2000_6.1.0/bin/cl2000" -v28 -ml -mt -O0 -g --include_path="F:/ti/ccsv5/tools/compiler/c2000_6.1.0/include" --include_path="F:/ Firmware/sam3s-demo-source/trunk/ sam3s-demo-source --username kaiser.ren@gmail.com/DSP2802x/C2000_LaunchPad" --include_path="/packages/ti/xdais" --define="_FLASH" --define=NDEBUG --define="_DEBUG" --define="LARGE_MODEL" --quiet --verbose_diagnostics --diag_warning=225 --gen_func_subsections=on --output_all_syms --cdebug_asm_data --preproc_with_compile --preproc_dependency="Example_F2802xLaunchPadDemo.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


