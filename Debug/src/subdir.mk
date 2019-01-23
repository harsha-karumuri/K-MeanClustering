################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Final\ Project.cpp 

OBJS += \
./src/Final\ Project.o 

CPP_DEPS += \
./src/Final\ Project.d 


# Each subdirectory must supply rules for building sources it contributes
src/Final\ Project.o: ../src/Final\ Project.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/Final Project.d" -MT"src/Final\ Project.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


