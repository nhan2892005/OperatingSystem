CPP = g++ # Flag for implicit rule
CC = gcc # Flag for implicit rule
LD = ld # Flag for implicit ruli
AR = ar
GFLAGS = -std=c++11 -g -pthread -I./ -L.#Flag for implicit rule. Turn on debug mode
CFLAGS = -g -lpthread -I./ -L.
LFLAGS = -g -I./ -L.
ARFLAGS = rcs

COBJECT = main 
CEXEC = aggsum
LIBS = utils

COBJECTO = $(addsuffix .o,$(COBJECT))
CLIBS = $(addprefix lib,$(addsuffix .a,$(LIBS)))

%.o: %.cpp
	$(CPP) $(GFLAGS)  -c $< -o $@

%.o: %.c
	$(CC) $(CFLAGS)  -c $< -o $@

lib%.a: %.o
	$(AR) $(ARFLAGS) $@ $^

all: $(COBJECTO) $(CLIBS)
	$(CC) $(GFLAGS) -l$(LIBS) $^ -o $(CEXEC) 

clean:
	rm *.o
	rm $(CEXEC) 

