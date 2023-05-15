CC= gcc
CFLAGS= -Wall -ansi -Wfatal-errors

OBJETS= date.o individu.o turing.o
PROG= laureats

all: $(OBJETS)
	gcc $(OBJETS) -o $(PROG)

date.o: date.h date.c
	gcc -c $(CFLAGS) date.c

individu.o: individu.h individu.c
	gcc -c $(CFLAGS) individu.c

turing.o:turing.c
	gcc -c $(CFLAGS) turing.c
	
clear:
	rm $(PROG) $(OBJETS)