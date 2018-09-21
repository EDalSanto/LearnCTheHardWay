CC = cc
CFLAGS = -g -Wall
SRC = $(wildcard src/*.c)
OBJ = $(SRC:.c=.o)

logfind: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)
	$(RM) $(OBJ)


.PHONY: clean

clean:
	$(RM) $(OBJ) logfind

re: clean logfind
