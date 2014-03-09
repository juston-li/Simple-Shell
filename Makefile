
CFLAGS=-Wall -march=native

all : joker

joker: joker.o parse.o myatoi.o joker.h
	gcc joker.o parse.o myatoi.o $(CFLAGS) -o joker

joker.o: joker.c 
	gcc joker.c  $(CFLAGS) -c
parse.o: parse.c
	gcc parse.c $(CFLAGS) -c
atoi.o: myatoi.c
	gcc myatoi.c $(CFLAGS) -c


clean:
	rm -f *o joker parse

