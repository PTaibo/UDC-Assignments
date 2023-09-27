# CFLAGS = -Wall -Wextra -O2
CFLAGS = -Wall -Wextra -g

# ADD NEW FILE HERE
MAIN_SOURCES = build/instructions.o build/help.o build/valid_commands.o

all: build/shell

build/shell: main.c ${MAIN_SOURCES}
	gcc ${CFLAGS} main.c ${MAIN_SOURCES} -o build/shell

build/instructions.o: instructions.c instructions.h
	gcc ${CLFAGS} -c instructions.c -o build/instructions.o

build/help.o: help.c help.h
	gcc ${CFALGS} -c help.c -o build/help.o

build/valid_commands.o: valid_commands.c valid_commands.h
	gcc ${CFLAGS} -c valid_commands.c -o build/valid_commands.o

# ADD NEW FILE COMPILATION INSTRUCTIONS HERE

clean:
	rm build/*
