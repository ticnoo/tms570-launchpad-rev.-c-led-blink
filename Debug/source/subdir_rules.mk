################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
source/%.obj: ../source/%.asm $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ccs10/ccs/tools/compiler/ti-cgt-arm_20.2.1.LTS/bin/armcl" -mv7R4 --code_state=32 --include_path="C:/Users/ticno/Desktop/ccs10 workspace/570 led blink 1" --include_path="C:/Users/ticno/Desktop/ccs10 workspace/570 led blink 1/include" --include_path="C:/ccs10/ccs/tools/compiler/ti-cgt-arm_20.2.1.LTS/include" -g --diag_warning=225 --diag_wrap=off --display_error_number --enum_type=packed --abi=eabi --preproc_with_compile --preproc_dependency="source/$(basename $(<F)).d_raw" --obj_directory="source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

source/%.obj: ../source/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ccs10/ccs/tools/compiler/ti-cgt-arm_20.2.1.LTS/bin/armcl" -mv7R4 --code_state=32 --include_path="C:/Users/ticno/Desktop/ccs10 workspace/570 led blink 1" --include_path="C:/Users/ticno/Desktop/ccs10 workspace/570 led blink 1/include" --include_path="C:/ccs10/ccs/tools/compiler/ti-cgt-arm_20.2.1.LTS/include" -g --diag_warning=225 --diag_wrap=off --display_error_number --enum_type=packed --abi=eabi --preproc_with_compile --preproc_dependency="source/$(basename $(<F)).d_raw" --obj_directory="source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


