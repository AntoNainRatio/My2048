#ifndef BOARD_H
#define BOARD_H

/*struct gameBoard
{
	int size;
	int* board;
	int* score;
};*/

struct game
{
	int* score;
	int size;
	int* board;
	int status;
};


int* getBoard(int n);
void putNewValue(struct game arg);
struct game initGame(int n);
void printSep(int n);
void printScore(struct game arg);
void printBoard(struct game arg);
void printAll(struct game arg);
int isFull(struct game arg);
void freeBoard(struct game arg);
int possibleMove(struct game arg);

#endif
