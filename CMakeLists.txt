cmake_minimum_required(VERSION 3.10)

project(Semu VERSION 1.0)

add_executable(semu main.cpp)

add_library(Utils OBJECT Utils.cpp)
add_library(State OBJECT State.cpp)
add_library(Ram OBJECT Ram.cpp)
add_library(Port OBJECT Port.cpp)
add_library(Peripheral OBJECT Peripheral.cpp)
add_library(MemoryMap OBJECT MemoryMap.cpp)

target_link_libraries(semu Utils State Ram Port Peripheral MemoryMap)
