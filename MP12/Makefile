CC=g++
CFLAGS=-g -Wall

mp12: main.o stack.o calculate.o
	$(CC) $(CFLAGS) main.o stack.o calculate.o -o mp12

main.o:
	$(CC) $(CLFAGS) -c main.c

stack.o:
	$(CC) $(CFLAGS) -c stack.c

calculate.o:
	$(CC) $(CFLAGS) -c calculate.c

clean:
	rm -f *.o mp12