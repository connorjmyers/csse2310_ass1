OPTS =	-std=c99 -pedantic -Wall -g

bark:	main.o fileio.o
	gcc $(OPTS) -o bark fileio.o main.o

main.o:	fileio.h data.h
	gcc $(OPTS) -c main.c

fileio.o:	fileio.h data.h
	gcc $(OPTS) -c fileio.c

