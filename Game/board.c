#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct gameBoard
{
	int size;
	int *board;
};


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
	board[y*n+x]=(new >= 3 ? 1 : 2)*2;
}

struct gameBoard initBoard(int n)
{
	int *board = getBoard(n);
	struct gameBoard game =
	{
		.size = n,
		.board = board,
	};
	putNewValue(game);
	putNewValue(game);
	return game;
}

void printBoard(struct gameBoard arg)
{
	int n = arg.size;
	int *board = arg.board;
	for(int i = 0; i < n; i++)
	{
		for(int j = 0; j < n; j++)
		{
			printf("%d ",board[i * n + j]);
		}
		printf("\n");
	}
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
