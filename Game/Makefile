CC = gcc
CFLAGS = `pkg-config --cflags gtk+-3.0` -Wall -O3
LDFLAGS = `pkg-config --libs gtk+-3.0` -lm
LDLIBS=-lcriterion
TARGET = my2048
SRC = src/*.c tests/testBot.c
OBJ=$(SRC:.c=.o)

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS) $(LDFLAGS)

check: $(OBJ)
	$(CC) -o  $@ $^ $(LDLIBS)
	./check

clean:
	rm -f $(TARGET)

.PHONY: all clean

