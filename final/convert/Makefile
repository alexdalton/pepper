CC=g++
CFLAGS=-g -Wall

convert: convert.o tree.o vector.o
	$(CC) $(CFLAGS) convert.o tree.o vector.o -o convert

convert.o:
	$(CC) $(CLFAGS) -c convert.c

tree.o:
	$(CC) $(CFLAGS) -c tree.c

vector.o:
	$(CC) $(CFLAGS) -c vector.c

clean:
	rm -f *.o convert
