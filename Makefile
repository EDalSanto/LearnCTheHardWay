CC = cc
CFLAGS = -g -Wall
TARGET = ex
OBJECTS = ex.o

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) -o $(TARGET) $(OBJECTS) $(CFLAGS)

clean:
	$(RM) $(TARGET) $(OBJECTS)

re: clean all
