cmake_minimum_required(VERSION 3.8.2)
project(SortedQueue)

set(CMAKE_C_COMPILER gcc)
set(CMAKE_C_FLAGS "-g -std=gnu99 -Os -ffunction-sections -fdata-sections -MD -Wall -pedantic ")

set(DYNAMIC_MEMORY_PATH "../DynamicMemory")

#include directories of the project
include_directories(./)
include_directories(${DYNAMIC_MEMORY_PATH})



add_executable(${CMAKE_PROJECT_NAME}.out main.c)


add_library(sQueue STATIC SortedQueue.c)
target_link_libraries(${CMAKE_PROJECT_NAME}.out sQueue)

add_library(dyMemory STATIC ${DYNAMIC_MEMORY_PATH}/DynamicMemory.c)
target_link_libraries(${CMAKE_PROJECT_NAME}.out dyMemory)



ADD_CUSTOM_TARGET("run" DEPENDS ${CMAKE_PROJECT_NAME}.out
  COMMAND  ./${CMAKE_PROJECT_NAME}.out
)
