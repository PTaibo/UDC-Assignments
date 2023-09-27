# CFLAGS = -Wall -Wextra -O2
CFLAGS = -Wall -Wextra -g

MAIN_SOURCES = instructions.o

all: build/shell

build/shell: main.c ${MAIN_SOURCES}
	gcc ${CFLAGS} main.c ${MAIN_SOURCES} -o shell
	rm *.o

build/instructions.o: instructions.c instructions.h
	gcc ${CLFAGS} -c instructions.c -o instructions.o

clean:
	rm build/*
