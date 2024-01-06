#ifndef BOARD_H
#define BOARD_H

struct gameBoard
{
	int size;
	int* board;
	int* score;
};

int* getBoard(int n);
void putNewValue(struct gameBoard arg);
struct gameBoard initBoard(int n);
void printSep(int n);
void printScore(struct gameBoard arg);
void printBoard(struct gameBoard arg);
void printAll(struct gameBoard arg);
int isFull(struct gameBoard arg);
void freeBoard(struct gameBoard arg);
int possibleMove(struct gameBoard arg);

#endif
