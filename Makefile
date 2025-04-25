CC = gcc
CFLAGS = `pkg-config --cflags gtk+-3.0` -Wall -O3
LDFLAGS = `pkg-config --libs gtk+-3.0` -lm
LDLIBS=
TARGET = my2048
SRC = src/board.c src/bot.c src/control.c src/parse.c src/main.c
OBJ=$(SRC:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ) $(LDFLAGS) $(LDLIBS)

check: LDLIBS += -lcriterion
check_SRC = test/testBot.c
check_OBJ = $(check_SRC:.c=.o) $(OBJ)
check: $(check_OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LDLIBS) $(LDFLAGS)
	./check

testParse: LDLIBS += -lcriterion
testParse_SRC = tests/testParse.c
testParse_OBJ = $(testParse_SRC:.c=.o) $(OBJ)
testParse: $(testParse_OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LDLIBS) $(LDFLAGS)
	./testParse

clean:
	rm -f $(TARGET)
	rm -f $(OBJ)
	rm -f tests/*.o
	rm -f src/*.o
	rm -f check
	rm -f testParse

.PHONY: all clean

