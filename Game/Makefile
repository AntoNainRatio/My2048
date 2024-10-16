CC = gcc
CFLAGS = `pkg-config --cflags gtk+-3.0` -Wall -O3
LDFLAGS = `pkg-config --libs gtk+-3.0` -lm
LDLIBS=
TARGET = my2048
SRC = src/board.c src/bot.c src/control.c src/parse.c
OBJ=$(SRC:.c=.o)

all: $(TARGET)

$(TARGET): SRC += src/main.c
$(TARGET): $(OBJ) src/main.o
	$(CC) -o $@ $(LDFLAGS) $(LDLIBS) $^

check: SRC += tests/testBot.c
check: LDLIBS += -lcriterion
check: $(OBJ) tests/testBot.o
	$(CC) -o  $@ $^ $(LDLIBS) $(LDFLAGS)
	./check

testParse: SRC += tests/testParse.c
testParse: $(OBJ) tests/testParse.o
	$(CC) -o $@ $^ $(LDLIBS) $(LDFLAGS)
	./testParse

clean:
	rm -f $(TARGET)
	rm -f $(OBJ)
	rm -f tests/*.o
	rm -f src/*.o
	rm -f check
	rm -f testParse

.PHONY: all clean

