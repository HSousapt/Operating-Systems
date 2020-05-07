CC = gcc
CFLAGS = -Wall

person: person.o api.o

person.o: person.c api.h

api.o: api.h api.c

clean:
	rm -f person *.o
