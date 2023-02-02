cmake_minimum_required(VERSION 3.7)

project(rational)

set(CMAKE_C_FLAGS "-Wall -Wextra -O2 --std=c99")

#set(CMAKE_VERBOSE_MAKEFILE on)

set(SOURCES
    main.c
    #rational_pointer.c
    rational_struct.c
    )

add_executable(rational ${SOURCES})
