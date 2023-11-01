CFLAGS = -Wall -Wextra

all:build/p3


build/p3: algorithms_p3_Paula_Siyuan.c build/heap.o
	gcc ${CFLAGS} algorithms_p3_Paula_Siyuan.c build/heap.o -lm -o build/p3

build/heap.o: heap.c heap.h build
	gcc ${CFLAGS} -c heap.c -o build/heap.o 


build:
	mkdir -p build

clean:
	rm build/*