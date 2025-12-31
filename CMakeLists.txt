cmake_minimum_required(VERSION 4.1)
project(vm C)

set(CMAKE_C_STANDARD 23)

add_executable(vm main.c
        common.h
        chunk.c
        chunk.h
        memory.c
        memory.h
        debug.c
        debug.h
        value.c
        value.h
        value.c)
