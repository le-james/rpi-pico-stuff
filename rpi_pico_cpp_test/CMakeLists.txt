cmake_minimum_required(VERSION 3.16.3)
include(pico_sdk_import.cmake)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

project(cpptest C CXX ASM)
pico_sdk_init()

# ${PROJECT_NAME} = tutorial
add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} pico_stdlib)

# create map/bin/hex file etc.
pico_add_extra_outputs(${PROJECT_NAME})

# enable usb output, disable uart output
pico_enable_stdio_usb(${PROJECT_NAME} 1)
pico_enable_stdio_uart(${PROJECT_NAME} 0)