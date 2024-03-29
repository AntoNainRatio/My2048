#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "board.h"

int* getBoard(int n)
{
	int* res = calloc(n*n,sizeof(int));
	return res;
}

void putNewValue(struct gameBoard arg)
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
	int new = rand()%8;
	board[y*n+x]=(new >= 2 ? 1 : 2)*2;
}

int* persoBoard(int* tab, int size)
{
	tab[0*size+0]=64;
	tab[1*size+0]=32;
	tab[2*size+0]=32;
	tab[3*size+0]=0;
	return tab;
}

struct gameBoard initBoard(int n)
{
	int *board = getBoard(n);
	struct gameBoard game =
	{
		.size = n,
		.board = board,
	};
	game.board = persoBoard(game.board,game.size);
	putNewValue(game);
	putNewValue(game);
	return game;
}

struct game initGame(int n)
{
	int startScore = 0;
	struct game res = 
	{
		.score = &startScore,
		.size = n,
		.board = initBoard(n),
		.status = playing,
	};
	return res;
}

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

void printBoard(int* tab,int n)
{
	if(tab == NULL)
	{
		printf("Not valid move\n");
	}
	else
	{
		int *board = tab;
		for(int i = 0; i < n; i++)
		{
			for(int j = 0; j < n; j++)
			{
				printf("%04d ", board[i * n + j]);
			}
			printf("\n");
		}
	}
}

void printAll(struct game arg)
{
	int n = arg.size;
	printSep(n);
	printf("- My 2048 Game -\n");
	printScore(arg);
	printSep(n);
	printBoard(arg.board.board,arg.board.size);
	printSep(n);
}

int isFull(struct gameBoard arg)
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

void freeBoard(struct gameBoard arg)
{
	free(arg.board);
}

int possibleMove(struct gameBoard arg)
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
