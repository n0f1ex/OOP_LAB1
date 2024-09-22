cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_COMPILER g++)
set(CMAKE_CXX_STANDART 20)

project(lab1 LANGUAGES CXX)

set(_EXE main.cpp)
set(_LIB arr_string.cpp)

add_library(arr_string STATIC ${_LIB})
add_executable(lab1 ${_EXE})

target_link_libraries(lab1 arr_string)



include(CTest)
enable_testing()

