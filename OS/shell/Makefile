# CFLAGS = -Wall -Wextra -O2
CFLAGS = -Wall -Wextra -g

# ADD NEW FILE HERE
MAIN_SOURCES = build/instructions.o build/help.o

all: build/shell

build/shell: main.c ${MAIN_SOURCES}
	gcc ${CFLAGS} main.c ${MAIN_SOURCES} -o build/shell

build/instructions.o: instructions.c instructions.h
	gcc ${CLFAGS} -c instructions.c -o build/instructions.o

build/help.o: help.c instructions.h
	gcc ${CFALGS} -c help.c -o build/help.o

# ADD NEW FILE COMPILATION INSTRUCTIONS HERE

clean:
	rm build/*
