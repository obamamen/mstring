cmake_minimum_required(VERSION 4.0)
project(string C)

set(CMAKE_C_STANDARD 99)

add_executable(string main.c
        include/string.h
        include/string_extras.h)
