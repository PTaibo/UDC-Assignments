#CFLAGS = -Wall -Wextra -O2
 CFLAGS = -Wall -Wextra -g

MAIN_OBJ = build/basic_commands.o build/help_pages.o build/file_commands.o build/list.o build/history_commands.o build/command_processor.o build/error_msgs.o build/stat_commands.o build/mem_commands.o

all: build/shell

build/shell: main.c ${MAIN_OBJ} build
	gcc ${CFLAGS} main.c ${MAIN_OBJ} -o build/shell

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

build/stat_commands.o: stat_commands.c stat_commands.h build
	gcc ${CFLAGS} -c stat_commands.c -o build/stat_commands.o    

build/mem_commands.o: mem_commands.c mem_commands.h build
	gcc ${CFLAGS} -c mem_commands.c -o build/mem_commands.o

build:
	mkdir -p build

clean:
	rm build/*
