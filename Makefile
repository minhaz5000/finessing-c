all: library main finessing_c
library: library.c library.h
	gcc -c library.c
main: main.c library.h
	gcc -c main.c
finessing_c: main.o library.o
	gcc main.o library.o -o finessing_c -lncurses
clean:
	rm -f library.o main.o