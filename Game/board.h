#ifndef BOARD_H
#define BOARD_H

struct gameBoard
{
	int size;
	int* board;
	int* maxValue;
};

int* getBoard(int n);
void putNewValue(struct gameBoard arg);
struct gameBoard initBoard(int n);
void printBoard(struct gameBoard arg);

#endif
