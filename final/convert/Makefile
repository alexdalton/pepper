CC=g++
CFLAGS=-g -Wall

convert: convert.o tree.o
	$(CC) $(CFLAGS) convert.o tree.o -o convert

convert.o:
	$(CC) $(CLFAGS) -c convert.c

tree.o:
	$(CC) $(CFLAGS) -c tree.c

clean:
	rm -f *.o convert
