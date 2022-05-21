cmake_minimum_required(VERSION 3.8.2)
project(MIROS_ThreadYield2)

#Toolchain file
include(tm4c123g.cmake)

#Tivaware files
set(TIVAWARE_PATH "$ENV{HOME}/tiva-projects/tivaware")


#------------------------------------------------------------------------
# Paths for the the SortedQueue Data Structure
#------------------------------------------------------------------------
#Dynamic Memory Files
set(DYNAMIC_MEMORY_PATH "DynamicMemory")
#SortedQueue
set(SORTED_QUEUE_PATH "SortedQueue")


#include directories of the project
include_directories(${TIVAWARE_PATH}/)
include_directories(inc/)
include_directories(${DYNAMIC_MEMORY_PATH})
include_directories(${SORTED_QUEUE_PATH})

#Source files
file(GLOB SOURCES "src/*.c")


add_executable(${CMAKE_PROJECT_NAME}.elf ${SOURCES})

#------------------------------------------------------------------------
# Linking SortedQueue
#------------------------------------------------------------------------
add_library(sQueue STATIC ${SORTED_QUEUE_PATH}/SortedQueue.c)
target_link_libraries(${CMAKE_PROJECT_NAME}.elf sQueue)

add_library(dyMemory STATIC ${DYNAMIC_MEMORY_PATH}/DynamicMemory.c)
target_link_libraries(${CMAKE_PROJECT_NAME}.elf dyMemory)




add_library(uart_printf STATIC ${TIVAWARE_PATH}/utils/uartstdio.c)
target_link_libraries(${CMAKE_PROJECT_NAME}.elf uart_printf)

target_link_libraries(${CMAKE_PROJECT_NAME}.elf 
    ${TIVAWARE_PATH}/usblib/gcc/libusb.a
    ${TIVAWARE_PATH}/driverlib/gcc/libdriver.a
)
