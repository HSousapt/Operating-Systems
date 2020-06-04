CC = gcc

CFLAGS = -Wall

all: client server

client: client.o clientParser.o

client.o: clientParser.h client.c

clientParser.o: clientParser.h clientParser.c

server: server.c

clean:
	rm -f client server *.o
