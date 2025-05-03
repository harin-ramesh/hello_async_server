CC = gcc
CFLAGS = -g
OBJ = common.o

all: main

main: main.c $(OBJ)
	$(CC) $(CFLAGS) -o server main.c $(OBJ)

common.o: common.c
	$(CC) $(CFLAGS) -c common.c

clean:
	rm -rf *.o *.dSYM main

