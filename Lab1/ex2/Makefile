CC = gcc
CFLAGS = -Wall -O2 -g

OBJS = calc.o calc_logic.o

all: calc

calc: $(OBJS)
	$(CC) $(CFLAGS) -o calc $(OBJS)

calc.o: calc.c calc_logic.h
	$(CC) $(CFLAGS) -c calc.c

calc_logic.o: calc_logic.c calc_logic.h
	$(CC) $(CFLAGS) -c calc_logic.c

clean:
	rm -f calc $(OBJS)
