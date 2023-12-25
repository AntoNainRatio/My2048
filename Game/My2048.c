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
		printBoard(partie.board);
		printf("maxValue actual is %d\n",*partie.board.maxValue);
		printf("\n");
		int input = -1;
		while(input == -1)
		{
			input = DoMove(partie.board);
		}
		printf("\n");
		putNewValue(partie.board);
	}
	return 1;
}
