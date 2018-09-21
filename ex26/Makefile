CC = cc
CFLAGS = -g -Wall 
SRC = $(wildcard src/*.c)
OBJ = $(SRC:.c=.o)

bin: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)
	$(RM) $(OBJ)


.PHONY: clean

clean:
	$(RM) $(OBJ)

re: clean bin
