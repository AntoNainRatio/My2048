/*Petite ref Epita
  Merci algo.master*/

#include "board.h"
#include "control.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "master.h"

struct gameBoard getBoardCopy(struct gameBoard arg)
{
	int l = arg.size;
	int* tab = arg.board;
	struct gameBoard res = initBoard(arg.size);
	for(int i = 0; i < l; i++)
	{
		for(int j = 0; j < l; j++)
		{
			res.board[i*l+j] = tab[i*l+j];
		}
	}
	return res;
}

void copyInt(int *src, int *dest)
{
    *dest = *src;
}

struct game getGameCopy(struct game arg)
{
	struct game res = initGame(arg.size);
	res.board = getBoardCopy(arg.board);
	int tmp = 0;
	int* ptr = &tmp;
	copyInt(arg.score,ptr);
	*res.score = *ptr;
	return res;
}

struct game* boardUp(struct game arg)
{
	int valid = -1;
	struct game tmp = getGameCopy(arg);
	printAll(tmp);
	valid = moveUp(tmp);
	if(valid == 0)
	{
		struct game* res = &tmp;
		return res;
	}
	else
	{
		return (struct game*)(NULL);
	}
}


struct game* boardDown(struct game arg)
{
	int valid = -1;
	struct game tmp = getGameCopy(arg);
	printAll(tmp);
	valid = moveDown(tmp);
	if(valid == 0)
	{
		struct game* res = &tmp;
		return res;
	}
	else
	{
		return (struct game*)(NULL);
	}
}

struct game* boardLeft(struct game arg)
{
	int valid = -1;
	struct game tmp = getGameCopy(arg);
	printAll(tmp);
	valid = moveLeft(tmp);
	if(valid == 0)
	{
		struct game* res = &tmp;
		return res;
	}
	else
	{
		return (struct game*)(NULL);
	}
}


struct game* boardRight(struct game arg)
{
	int valid = -1;
	struct game tmp = getGameCopy(arg);
	printAll(tmp);
	valid = moveRight(tmp);
	if(valid == 0)
	{
		struct game* res = &tmp;
		return res;
	}
	else
	{
		return (struct game*)(NULL);
	}
}

/*int getScoreFromState(struct gameBoard arg)
{
	
}*/
