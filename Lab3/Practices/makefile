# Makefile

CC = gcc
CFLAGS = -pthread -Wall
TARGETS = shrdmem.exe pc.exe

all: $(TARGETS)

shrdmem.exe: shrdmem.c
	$(CC) $(CFLAGS) -o shrdmem shrdmem.c

pc.exe: pc.c
	$(CC) $(CFLAGS) -o pc pc.c

clean:
	rm -f * *.o
