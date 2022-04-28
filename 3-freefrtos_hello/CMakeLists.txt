cmake_minimum_required(VERSION 3.8.2)
project(freertos_hello)

#Toolchain file
include(tm4c123g.cmake)

#Tivaware files
set(TIVAWARE_PATH "$ENV{HOME}/tiva-projects/tivaware")

#FreeRTOS
set(FREERTOS_PATH "$ENV{HOME}/tiva-projects/FreeRTOS")

#include directories of the project
include_directories(${TIVAWARE_PATH}/inc)
include_directories(inc/)
include_directories(${FREERTOS_PATH}/Source/include)
include_directories(${FREERTOS_PATH}/Source/portable/GCC/ARM_CM4F)

#FreeRTOS  sources 
file(GLOB FREERTOS_SOURCES1 "${FREERTOS_PATH}/Source/*.c")
file(GLOB FREERTOS_SOURCES2 "${FREERTOS_PATH}/Source/portable/GCC/ARM_CM4F/*.c")
file(GLOB FREERTOS_SOURCES3 "${FREERTOS_PATH}/Source/portable/MemMang/heap_2.c")

#Source files
file(GLOB SOURCES "src/*.c" )
add_executable(${CMAKE_PROJECT_NAME}.elf ${SOURCES} ${FREERTOS_SOURCES2} ${FREERTOS_SOURCES1} ${FREERTOS_SOURCES3} ) 

target_link_libraries(${CMAKE_PROJECT_NAME}.elf 
    ${TIVAWARE_PATH}/usblib/gcc/libusb.a
    ${TIVAWARE_PATH}/driverlib/gcc/libdriver.a
)
