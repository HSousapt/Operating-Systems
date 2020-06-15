CC = gcc

CFLAGS = -Wall

all: argus argusd

argus: argus.o clientParser.o

argus.o: clientParser.h argus.c

clientParser.o: clientParser.h clientParser.c

argusd: argusd.o requestHandler.o task.o

argusd.o: requestHandler.h argusd.c 

requestHandler.o: requestHandler.h requestHandler.c task.o 

task.o: task.h task.c

clean:
	rm -f argus argusd reply request log log.idx *.o
