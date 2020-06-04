CC = gcc

CFLAGS = -Wall

client: client.o clientParser.o

client.o: clientParser.h client.c

clientParser.o: clientParser.h clientParser.c

clean:
	rm -f client *.o
