cmake_minimum_required(VERSION 3.10)

project(Semu VERSION 1.0)

add_executable(semu main.cpp)

add_library(State OBJECT State.cpp)

target_link_libraries(semu State)
