#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <unistd.h> 
#include "board.h"
#include "control.h"
#include "master.h"

/*struct game
{
	int score;
	int size;
	struct gameBoard board;
	int status;
};*/


int play()
{
	int startScore = 0;
	struct game partie =
	{
		.score = &startScore,
		.size = 4,
		.board = initBoard(4),
		.status = playing,
	};
	while(partie.status != lost)
	{
		printAll(partie);
		/*
		 *		DEBUG 4 predictions
		 *
		 */
		printf("Test Move:\n");
		printf("============================================================\n");
		printf("Up\n");
		printAll(*boardUp(partie));
		printf("============================================================\n");
		printf("Down\n");
		printAll(*boardDown(partie));
		printf("============================================================\n");
		printf("Left\n");
		printAll(*boardLeft(partie));
		printf("============================================================\n");
		printf("Right\n");
		printAll(*boardRight(partie));
		
		if(possibleMove(partie.board) == 0)
		{
			partie.status = 1;
			continue;
		}
		int input = -1;
		while(input == -1)
		{
			input = DoMove(partie);
		}
		if(isFull(partie.board) == 1)
		{
			putNewValue(partie.board);
		}
		printf("\n");
	}
	printf("Finished :)\n");
	freeBoard(partie.board);
	return 1;
}

int randomBot(int n)
{
	int startScore = 0;
	struct game partie =
	{
		.score = &startScore,
		.size = 4,
		.board = initBoard(4),
		.status = playing,
	};
	int nbMove = 0;
	while(partie.status != lost)
	{
		if(nbMove % n ==0)
		{
			printAll(partie);
			printf("\n");
		}
		if(possibleMove(partie.board) == 0)
		{
			partie.status = 1;
			continue;
		}
		int input = -1;
		while(input == -1)
		{
			input = DoRandomMove(partie);
		}
		if(isFull(partie.board) == 1)
		{
			putNewValue(partie.board);
		}
		nbMove += 1;
		usleep(500000);
	}
	if(nbMove % n != 0)
	{
		printAll(partie);
		printf("\n");
	}
	printf("Finished :)\n");
	freeBoard(partie.board);
	return 1;
}


int prioBot(int n)
{
	int startScore = 0;
	struct game partie =
	{
		.score = &startScore,
		.size = 4,
		.board = initBoard(4),
		.status = playing,
	};
	int nbMove = 0;
	while(partie.status != lost)
	{
		if(nbMove % n == 0)
		{
			printAll(partie);
			printf("\n");
		}
		if(possibleMove(partie.board) == 0)
		{
			partie.status = 1;
			continue;
		}
		if(moveUp(partie) == -1)
		{
			if(moveLeft(partie) == -1)
			{
				if(moveDown(partie) == -1)
				{
					moveRight(partie);
				}
			}
		}
		usleep(500000);
		if(isFull(partie.board) == 1)
		{
			putNewValue(partie.board);
		}
		nbMove += 1;
	}
	if(nbMove % n != 0)
	{
		printAll(partie);
		printf("\n");
	}
	printf("Finished :)\n");
	freeBoard(partie.board);
	return 1;
}

int main(int argc, char**  argv)
{
	srand(time(NULL));
	if(argc == 1)
	{
		return play();
	}
	else
	{
		if(strcmp(argv[1],"--h")==0)
		{
			printf("Help settings for My2048:\n");
			printf("	\"./a.out\" --> Normal playing\n");
			printf("	\"./a.out rdm\"  --> Random Bot Playing\n");
			printf("That's it\n");
			printf("Hope it helped you :)\n");
		}
		else if(strcmp(argv[1],"rdm")==0)
		{
			if(argc == 3)
			{
				return randomBot(atoi(argv[2]));
			}
			return randomBot(1);
		}
		else if(strcmp(argv[1],"prio")==0)
		{
			if(argc == 3)
			{
				return prioBot(atoi(argv[2]));
			}
			return prioBot(1);
		}
		else
		{
			return -1;
		}
	}
}
