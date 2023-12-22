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
	printBoard(partie.board);
	moveUp(partie.board);
	printf("\n");
	printBoard(partie.board);
	return 1;
}
