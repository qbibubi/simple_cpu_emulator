cmake_minimum_required(VERSION 4.2)

project(simple_cpu_emulator VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_COMPILER /usr/bin/clang++)

set(SOURCES
    ${CMAKE_SOURCE_DIR}/src/main.cc
    ${CMAKE_SOURCE_DIR}/src/cpu.cc
    ${CMAKE_SOURCE_DIR}/src/compiler.cc
)

add_executable(cpu_emulator
    ${SOURCES}
)

target_include_directories(cpu_emulator PRIVATE 
    ${CMAKE_SOURCE_DIR}/include
)
