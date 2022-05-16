cmake_minimum_required(VERSION 3.8.2)
project(MIROS_interrupt)

#Toolchain file
include(tm4c123g.cmake)

#Tivaware files
set(TIVAWARE_PATH "$ENV{HOME}/tiva-projects/tivaware")

#include directories of the project
include_directories(${TIVAWARE_PATH}/)
include_directories(inc/)

#Source files
file(GLOB SOURCES "src/*.c")


add_executable(${CMAKE_PROJECT_NAME}.elf ${SOURCES})

target_link_libraries(${CMAKE_PROJECT_NAME}.elf 
    ${TIVAWARE_PATH}/usblib/gcc/libusb.a
    ${TIVAWARE_PATH}/driverlib/gcc/libdriver.a
)
