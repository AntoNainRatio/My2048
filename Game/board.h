#ifndef BOARD_H
#define BOARD_H

struct gameBoard
{
	int size;
	int* board;
};

struct game
{
	int* score;
	int size;
	struct gameBoard board;
	int status;
};


int* getBoard(int n);
void putNewValue(struct gameBoard arg);
struct gameBoard initBoard(int n);
void printSep(int n);
void printScore(struct game arg);
void printBoard(struct gameBoard arg);
void printAll(struct game arg);
int isFull(struct gameBoard arg);
void freeBoard(struct gameBoard arg);
int possibleMove(struct gameBoard arg);

#endif
