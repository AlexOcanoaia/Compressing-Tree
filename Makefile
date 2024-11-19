CFLAGS = -Wall -Werror -g

build: tree.o main.c
	gcc $(CFLAGS) tree.o main.c -o main

tree.o: tree.c tree.h
	gcc -c $(CFLAGS) tree.c -o tree.o

clean:
	rm -f tree.o main