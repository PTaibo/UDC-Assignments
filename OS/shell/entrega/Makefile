#CFLAGS = -Wall -Wextra -O2
 CFLAGS = -Wall -Wextra -g

MAIN_OBJ = build/basic_commands.o build/help_pages.o build/file_commands.o build/list.o build/history_commands.o build/command_processor.o build/error_msgs.o

all: build/p1

build/p1: p1.c ${MAIN_OBJ} build
	gcc ${CFLAGS} p1.c ${MAIN_OBJ} -o build/p1

build/basic_commands.o: basic_commands.c basic_commands.h build
	gcc ${CFLAGS} -c basic_commands.c -o build/basic_commands.o

build/help_pages.o: help_pages.c help_pages.h build
	gcc ${CFLAGS} -c help_pages.c -o build/help_pages.o

build/file_commands.o: file_commands.c file_commands.h build
	gcc ${CFLAGS} -c file_commands.c -o build/file_commands.o

build/history_commands.o: history_commands.c history_commands.h build
	gcc ${CFLAGS} -c history_commands.c -o build/history_commands.o

build/list.o: list.c list.h build
	gcc ${CFLAGS} -c list.c -o build/list.o

build/command_processor.o: command_processor.c command_processor.h build
	gcc ${CFLAGS} -c command_processor.c -o build/command_processor.o

build/error_msgs.o: error_msgs.c error_msgs.h build
	gcc ${CFLAGS} -c error_msgs.c -o build/error_msgs.o

build:
	mkdir -p build

clean:
	rm build/*
