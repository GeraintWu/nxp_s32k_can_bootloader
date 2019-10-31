################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/can_user_if.c" \
"../Sources/fsl_flash_driver_c90tfs.c" \
"../Sources/lpit_user_if.c" \
"../Sources/main.c" \
"../Sources/update.c" \

C_SRCS += \
../Sources/can_user_if.c \
../Sources/fsl_flash_driver_c90tfs.c \
../Sources/lpit_user_if.c \
../Sources/main.c \
../Sources/update.c \

OBJS_OS_FORMAT += \
./Sources/can_user_if.o \
./Sources/fsl_flash_driver_c90tfs.o \
./Sources/lpit_user_if.o \
./Sources/main.o \
./Sources/update.o \

C_DEPS_QUOTED += \
"./Sources/can_user_if.d" \
"./Sources/fsl_flash_driver_c90tfs.d" \
"./Sources/lpit_user_if.d" \
"./Sources/main.d" \
"./Sources/update.d" \

OBJS += \
./Sources/can_user_if.o \
./Sources/fsl_flash_driver_c90tfs.o \
./Sources/lpit_user_if.o \
./Sources/main.o \
./Sources/update.o \

OBJS_QUOTED += \
"./Sources/can_user_if.o" \
"./Sources/fsl_flash_driver_c90tfs.o" \
"./Sources/lpit_user_if.o" \
"./Sources/main.o" \
"./Sources/update.o" \

C_DEPS += \
./Sources/can_user_if.d \
./Sources/fsl_flash_driver_c90tfs.d \
./Sources/lpit_user_if.d \
./Sources/main.d \
./Sources/update.d \


# Each subdirectory must supply rules for building sources it contributes
Sources/can_user_if.o: ../Sources/can_user_if.c
	@echo 'Building file: $<'
	@echo 'Executing target #27 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/can_user_if.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Sources/can_user_if.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Sources/fsl_flash_driver_c90tfs.o: ../Sources/fsl_flash_driver_c90tfs.c
	@echo 'Building file: $<'
	@echo 'Executing target #28 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/fsl_flash_driver_c90tfs.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Sources/fsl_flash_driver_c90tfs.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Sources/lpit_user_if.o: ../Sources/lpit_user_if.c
	@echo 'Building file: $<'
	@echo 'Executing target #29 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/lpit_user_if.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Sources/lpit_user_if.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Sources/main.o: ../Sources/main.c
	@echo 'Building file: $<'
	@echo 'Executing target #30 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/main.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Sources/main.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Sources/update.o: ../Sources/update.c
	@echo 'Building file: $<'
	@echo 'Executing target #31 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/update.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Sources/update.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '


