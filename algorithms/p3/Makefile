CFLAGS = -Wall -Wextra
#CFLAGS = -Wall -Wextra -g
all:build/p3


build/p3: algorithms_p3_Paula_Siyuan.c build/heap.o build/test.o build/time.o
	gcc ${CFLAGS} algorithms_p3_Paula_Siyuan.c build/heap.o build/test.o build/time.o -lm -o build/p3

build/heap.o: heap.c heap.h build
	gcc ${CFLAGS} -c heap.c -o build/heap.o

build/test.o: test.c test.h build
	gcc ${CFLAGS} -c test.c -o build/test.o

build/time.o: time.c time.h build
	gcc ${CFLAGS} -c time.c -o build/time.o

build:
	mkdir -p build

clean:
	rm build/*
