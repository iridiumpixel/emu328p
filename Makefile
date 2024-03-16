CC=gcc

CFLAGS=-O0 -Wall -Wpedantic -g

.PHONY: clean final

final: main.o 
	$(CC) $(CFLAGS) main.o -o final

main.o: 
	$(CC) $(CFLAGS) -c src/main.c

clean:
	echo "Cleaning..."
	rm final *.o