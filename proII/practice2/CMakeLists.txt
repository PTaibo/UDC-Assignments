cmake_minimum_required(VERSION 3.7)

project(main)

set(CMAKE_C_FLAGS "-Wall -Wextra -O2 --std=c99")
#set(CMAKE_C_FLAGS "-Wall -Wextra -g --std=c99")

#set(CMAKE_VERBOSE_MAKEFILE on)

set(SOURCES
    main.c
    jury_list.c
    participant_list.c
    )

add_executable(main ${SOURCES})
