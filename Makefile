CC=gcc
CFLAGS=-O4 -Wall -Wpedantic

final: main.o 
	$(CC) $(CFLAGS) main.o -o final

main.o: 
	$(CC) $(CFLAGS) -c src/main.c