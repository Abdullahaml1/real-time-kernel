cmake_minimum_required(VERSION 3.8.2)
project(DynamicMemroy)

set(CMAKE_C_COMPILER gcc)
set(CMAKE_C_FLAGS "-g -std=gnu99 -Os -ffunction-sections -fdata-sections -MD -Wall -pedantic ")

#include directories of the project
include_directories(./)



add_executable(${CMAKE_PROJECT_NAME}.out main.c)


add_library(dyMemory STATIC DynamicMemory.c)
target_link_libraries(${CMAKE_PROJECT_NAME}.out dyMemory)


ADD_CUSTOM_TARGET("run" DEPENDS ${CMAKE_PROJECT_NAME}.out
  COMMAND  ./${CMAKE_PROJECT_NAME}.out
)
