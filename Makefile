CC=gcc

CFLAGS=-O0 -Wall -Wpedantic -g

COBJFILES=instruction_handlers.o main.o atmega328p.o ihex.o


all: main.o instruction_handlers.o atmega328p.o ihex.o
	$(CC) $(CFLAGS) $(COBJFILES) -o final

main.o: 
	echo "compiling main"
	$(CC) $(CFLAGS) -c src/main.c

atmega328p.o:
	$(CC) $(CFLAGS) -c src/atmega328p.c

instruction_handlers.o:
	$(CC) $(CFLAGS) -c src/instruction_handlers.c

ihex.o:
	$(CC) $(CFLAGS) -c src/ihex.c

clean:
	echo "clean"
	rm final *.o