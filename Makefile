CC = gcc
CFLAGS = `pkg-config --cflags gtk+-3.0` -Wall -O3 -pthread
LDFLAGS = `pkg-config --libs gtk+-3.0` -pthread -lm
TARGET = my2048
SRC = src/board.c src/bot.c src/control.c src/parse.c
OBJ = $(SRC:.c=.o)

CRITERION = -lcriterion

all: $(TARGET)

$(TARGET): $(OBJ) src/main.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

testBot: tests/testBot.o $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS) $(CRITERION)
	./testBot

testParse: tests/testParse.o $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)
	./testParse

check: testBot testParse

clean:
	rm -f $(TARGET) $(OBJ) src/main.o tests/*.o testBot testParse

.PHONY: all check clean testBot testParse
