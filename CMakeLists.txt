cmake_minimum_required(VERSION 3.15)
project(calculator)

set(CMAKE_CXX_STANDARD 11)
set(APP_EXE main)

add_library(calc_lib STATIC calculator.cpp Calculator.h)

add_executable(${APP_EXE} main.cpp)

target_link_libraries(${APP_EXE} calc_lib)