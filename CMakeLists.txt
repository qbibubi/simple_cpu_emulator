cmake_minimum_required(VERSION 4.2)

project(simple_cpu_emulator VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_COMPILER clang++)

add_executable(cpu_emulator
    src/main.cc
    src/cpu.cc
    src/parser.cc
)
