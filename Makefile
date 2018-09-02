CC = cc
CFLAGS = -g -Wall
PROGRAMS = ex1 ex3

.PHONY: all clean

all: $(PROGRAMS)

ex1: ex1.c
	$(CC) -o $@ $^ $(CFLAGS)

ex3: ex3.c
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	$(RM) $(PROGRAMS)

re: clean all
