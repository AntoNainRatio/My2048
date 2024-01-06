#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "board.h"
#include "control.h"

#define playing 0
#define lost 1

struct game
{
	int score;
	int size;
	struct gameBoard board;
	int status;
};

int main()
{
	srand(time(NULL));
	struct game partie =
	{
		.score = 0,
		.size = 4,
		.board = initBoard(4),
		.status = playing,
	};
	while(partie.status != lost)
	{
		printAll(partie.board);
		if(possibleMove(partie.board) == 0)
		{
			partie.status = 1;
			continue;
		}
		int input = -1;
		while(input == -1)
		{
			input = DoMove(partie.board);
		}
		if(isFull(partie.board) == 1)
		{
			putNewValue(partie.board);
		}
		printf("\n");
	}
	printf("Lost :(\n");
	freeBoard(partie.board);
	return 1;
}
