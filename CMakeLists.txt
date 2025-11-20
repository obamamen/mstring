cmake_minimum_required(VERSION 4.0)
project(mstring C)

set(CMAKE_C_STANDARD 99)

add_executable(mstring main.c
        include/mstring.h
        include/mstring_extras.h
        src/mstring.c
)
