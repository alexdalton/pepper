CC=g++
CFLAGS=-g -Wall

sums: sums.o tree.o queue.o vector.o 
	$(CC) $(CFLAGS) sums.o tree.o queue.o vector.o -o sums

sums.o:
	$(CC) $(CLFAGS) -c sums.c

tree.o:
	$(CC) $(CFLAGS) -c tree.c

queue.o:
	$(CC) $(CFLAGS) -c queue.c

vector.o:
	$(CC) $(CFLAGS) -c vector.c

clean:
	rm -f *.o sums
