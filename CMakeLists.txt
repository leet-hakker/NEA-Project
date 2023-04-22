# Configure with [fxsdk build-fx] or [fxsdk build-cg], which provide the
# toolchain file and module path of the fxSDK
set(CMAKE_C_COMPILER_WORKS 1)
set(CMAKE_CXX_COMPILER_WORKS 1)
cmake_minimum_required(VERSION 3.15)

project(SimplexSolver)

# set(CURRENT_COMPILER sh-elf-gcc)
# set(HOST_C_COMPILER sh-elf-gcc)
# set(HOST_C_FLAGS "-Wall -Werror -O3 -m4-nofpu -mb -ffreestanding -nostdlib -Wa,--dsp")


add_subdirectory(src)
# enable_testing()
# add_subdirectory(tests)
