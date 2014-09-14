CC=gcc
CFLAGS= -Wall -Werror -Wextra

mp4: main.o printBinary.o
	$(CC) $(CFLAGS) main.o printBinary.o -o mp4

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

printBinary.o:
	$(CC) $(CFLAGS) -c printBinary.c

clean:
	rm -f *.o mp4
