#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "board.h"

int* getBoard(int n)
{
	int* res = calloc(n*n,sizeof(int));
	return res;
}

void putNewValue(struct game arg)
{
	int n = arg.size;
	int *board = arg.board;
	int x = rand() % n;
	int y = rand() % n;
	while(board[y*n+x] != 0)
	{
		x=rand() % n;
		y=rand() % n; 
	}
	int new = rand()%10;
	board[y*n+x]=(new == 1 ? 2 : 1)*2;
}

struct game initGame(int n)
{
	int *board = getBoard(n);
	int startScore = 0;
	struct game game =
	{
		.size = n,
		.board = board,
		.score = &startScore,
	};
	putNewValue(game);
	putNewValue(game);
	return game;
}

/*int* strToBoard(char* s, int size)
{
	int* res = malloc(size*size*sizeof(int));
	int i = 0;
	int y = 0;
	int x = 0;
	while(s[i] != 0)
	{
		if(s[i] == '\')
		{
			y++;
			x = 0;
		}
		i++;
	}
	return res;
}*/

void printScore(struct game arg)
{
	printf("Score : %d\n",*arg.score);
}

void printSep(int n)
{
	for(int i = 0; i < n; i++)
	{
		printf("=====");
	}
	printf("\n");
	}

void printBoard(struct game arg)
{
	int n = arg.size;
	int *board = arg.board;
	for(int i = 0; i < n; i++)
	{
		for(int j = 0; j < n; j++)
		{
			printf("%04d ", board[i * n + j]);
		}
		printf("\n");
	}
}

void printAll(struct game arg)
{
	printf("%d\n",*arg.score);
	int n = arg.size;
	printf("%d\n",*arg.score);
	printSep(n);
	printf("- My 2048 Game -\n");
	printf("%d\n",*arg.score);
	printScore(arg);
	printSep(n);
	printBoard(arg);
	printSep(n);
}

int isFull(struct game arg)
{
	int* board = arg.board;
	int n = arg.size;
	for(int i = 0; i < n; i++)
	{
		for(int j = 0; j < n; j++)
		{
			if(board[i*n + j] == 0)
			{
				return 1;
			}
		}
	}
	return 0;
}

void freeBoard(struct game arg)
{
	free(arg.board);
}

int possibleMove(struct game arg)
{
	int n = arg.size;
	int *board = arg.board;
	for(int i = 0; i < n; i++)
	{
		for(int j = 0; j < n; j++)
		{
			if(board[i*n+j] == 0)
			{
				return 1;
			}
			if(i+1 < n && board[(i+1)*n+j] == board[i*n+j])
			{
				return 1;
			}
			if(i-1 >= 0 && board[(i-1)*n+j] == board[i*n+j])
			{
				return 1;
			}
			if(j+1 < n && board[i*n + j+1] == board[i*n+j])
			{
				return 1;
			}
			if(j-1 >= 0 && board[i*n+j-1] == board[i*n+j])
			{
				return 1;
			}
		}
	}
	return 0;
}


/*int main(int argc, char** argv)
{
	if(argc != 2)
	{
		printf("board.c error: Too much or arg missing\n");
		return -1;
	}
	int size = atoi(argv[1]);
	if(size<=0 || size >= 10)
	{
		printf("board.c error: A respectable size is between 1 and 9 \n");
		return -1;
	}
	srand(time(NULL));
	struct gameBoard newBoard = initBoard(size);
	printBoard(newBoard);
	free(newBoard.board);
}*/
