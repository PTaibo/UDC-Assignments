cmake_minimum_required(VERSION 3.7)

project(main)

#set(CMAKE_C_FLAGS "-Wall -Wextra -O2 --std=c99")
set(CMAKE_C_FLAGS "-Wall -Wextra -g --std=c99")

#set(CMAKE_VERBOSE_MAKEFILE on)

set(SOURCES
    main.c
    #static_list.c
    dynamic_list.c
    mainFunctions.c
    )

add_executable(main ${SOURCES})
