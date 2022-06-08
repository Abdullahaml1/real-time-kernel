cmake_minimum_required(VERSION 3.8.2)
project(freertos_block_on_write_queue)

#Toolchain file
include(tm4c123g.cmake)

#Tivaware files
set(TIVAWARE_PATH "$ENV{HOME}/tiva-projects/tivaware")

#FreeRTOS
set(FREERTOS_PATH "$ENV{HOME}/tiva-projects/FreeRTOS")

#include directories of the project
include_directories($
  ${TIVAWARE_PATH}/
  inc/
  ${FREERTOS_PATH}/Source/include
  ${FREERTOS_PATH}/Source/portable/GCC/ARM_CM4F

  # ${FREERTOS_DIR}/Source/portable/ThirdParty/GCC/Posix
  # ${FREERTOS_DIR}/Source/portable/ThirdParty/GCC/Posix/utils
  ${FREERTOS_DIR}/Demo/Common/include
  # ${FREERTOS_DIR}/Demo/Posix_GCC
)





#FreeRTOS  sources 
file(GLOB FREERTOS_SOURCES "${FREERTOS_PATH}/Source/*.c")
list(APPEND FREERTOS_SOURCES "${FREERTOS_PATH}/Source/portable/GCC/ARM_CM4F/port.c")

list(APPEND FREERTOS_SOURCES "${FREERTOS_PATH}/Source/portable/MemMang/heap_3.c")
# Posix port
# -> SOURCE_FILES += ${FREERTOS_DIR}/Source/portable/ThirdParty/GCC/Posix/utils/wait_for_event.c
# -> SOURCE_FILES += ${FREERTOS_DIR}/Source/portable/ThirdParty/GCC/Posix/port.c
# list(APPEND FREERTOS_SOURCES "${FREERTOS_PATH}/Source/portable/ThirdParty/GCC/Posix/utils/wait_for_event.c")
# list(APPEND FREERTOS_SOURCES "${FREERTOS_PATH}/Source/portable/ThirdParty/GCC/Posix/port.c")




# project Source files
file(GLOB SOURCES "src/*.c" )



# adding executable
add_executable(${CMAKE_PROJECT_NAME}.elf ${SOURCES}) 


# Link FreeRTOS as a static library
add_library(freertos STATIC ${FREERTOS_SOURCES})
target_link_libraries(${CMAKE_PROJECT_NAME}.elf freertos)

add_library(uart_printf STATIC ${TIVAWARE_PATH}/utils/uartstdio.c)
target_link_libraries(${CMAKE_PROJECT_NAME}.elf uart_printf)

target_link_libraries(${CMAKE_PROJECT_NAME}.elf 
    ${TIVAWARE_PATH}/usblib/gcc/libusb.a
    ${TIVAWARE_PATH}/driverlib/gcc/libdriver.a
)


