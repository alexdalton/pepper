CC=gcc
CFLAGS= -Wall -Werror -Wextra

mp4: main.o printBinary.o
	$(CC) $(CFLAGS) main.o printBinary.o -o mp4

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

clean:
	rm -f main.o mp4
