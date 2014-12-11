CC=g++
CFLAGS=-g -Wall

convert: convert.o tree.o queue.o
	$(CC) $(CFLAGS) convert.o tree.o queue.o -o convert

convert.o:
	$(CC) $(CLFAGS) -c convert.c

tree.o:
	$(CC) $(CFLAGS) -c tree.c

queue.o:
	$(CC) $(CFLAGS) -c queue.c

clean:
	rm -f *.o convert
