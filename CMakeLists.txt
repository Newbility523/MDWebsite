cmake_minimum_required(VERSION 3.8)

# set(CMAKE_C_COMPLIER C:/MinGW/bin/gcc.exe)
# set(CMAKE_CXX_COMPLIER C:/MinGW/bin/g++.exe)

project(MDWebsite)

add_definitions(-std=c++17)

# set_property(TARGET tgt PROPERTY CXX_STANDARD 11)

include_directories(${PROJECT_SOURCE_DIR}/include)

add_executable(MDWebsite src/main.cpp)
