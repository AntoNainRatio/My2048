#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include "board.h"
#include "control.h"

#define playing 0
#define lost 1

/*struct game
{
	int score;
	int size;
	struct gameBoard board;
	int status;
};*/


int play()
{
	struct game partie = initGame(4);
	printf("%d\n",*partie.score);
	while(partie.status != lost)
	{
			printf("%d\n",*partie.score);
		printAll(partie);
		printf("%d\n",*partie.score);
		if(possibleMove(partie) == 0)
		{
			partie.status = 1;
			continue;
		}
		int input = -1;
		while(input == -1)
		{
			input = DoMove(partie);
		}
		if(isFull(partie) == 1)
		{
			putNewValue(partie);
		}
		printf("\n");
	}
	printf("Finished :)\n");
	freeBoard(partie);
	return 1;
}

int randomBot(int n)
{
	struct game partie = initGame(4);
	int nbMove = 0;
	while(partie.status != lost)
	{
		if(nbMove % n ==0)
		{
			printAll(partie);
			printf("\n");
		}
		if(possibleMove(partie) == 0)
		{
			partie.status = 1;
			continue;
		}
		int input = -1;
		while(input == -1)
		{
			input = DoRandomMove(partie);
		}
		if(isFull(partie) == 1)
		{
			putNewValue(partie);
		}
		nbMove += 1;
	}
	if(nbMove % n != 0)
	{
		printAll(partie);
		printf("\n");
	}
	printf("Finished :)\n");
	freeBoard(partie);
	return 1;
}


int prioBot(int n)
{
	struct game partie = initGame(4);
	int nbMove = 0;
	while(partie.status != lost)
	{
		if(nbMove % n == 0)
		{
			printAll(partie);
			printf("\n");
		}
		if(possibleMove(partie) == 0)
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
		if(isFull(partie) == 1)
		{
			putNewValue(partie);
		}
		nbMove += 1;
	}
	if(nbMove % n != 0)
	{
		printAll(partie);
		printf("\n");
	}
	printf("Finished :)\n");
	freeBoard(partie);
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
