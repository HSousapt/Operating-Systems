CC = gcc

CFLAGS = -Wall

all: client server

client: client.o clientParser.o

client.o: clientParser.h client.c

clientParser.o: clientParser.h clientParser.c

server: server.o requestHandler.o task.o

server.o: requestHandler.h server.c 

requestHandler.o: requestHandler.h requestHandler.c task.o 

task.o: task.h task.c

clean:
	rm -f client server *.o
