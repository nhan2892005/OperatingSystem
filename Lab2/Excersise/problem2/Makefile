CC = gcc
CFLAGS = -Wall -Wextra -pthread -g

all: sum_serial sum_multi-thread

sum_serial: sum_serial.c
	$(CC) $(CFLAGS) -o $@ $<

sum_multi-thread: sum_multi-thread.c
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -f sum_serial sum_multi-thread