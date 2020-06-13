CC = gcc

CFLAGS = -Wall

all: argus server

argus: argus.o clientParser.o

argus.o: clientParser.h argus.c

clientParser.o: clientParser.h clientParser.c

server: server.o requestHandler.o task.o

server.o: requestHandler.h server.c 

requestHandler.o: requestHandler.h requestHandler.c task.o 

task.o: task.h task.c

clean:
	rm -f argus server reply request log log.idx *.o
