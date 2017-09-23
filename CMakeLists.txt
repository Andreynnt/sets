cmake_minimum_required(VERSION 3.7)
project(LogicTask1)

set(CMAKE_C_STANDARD 11)

set(SOURCE_FILES main.c src/hash.h src/hash.c ux/menu.h ux/menu.c)
add_executable(LogicTask1 ${SOURCE_FILES})