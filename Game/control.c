#include <stdlib.h>
#include <stdio.h>
#include "board.h"

int moveUp(struct gameBoard arg)
{
	int l = arg.size;
	int* tab = arg.board;
	for(int x = 0; x < l; x++)
	{
		for(int y = 1; y < l; y++)
		{
			if(tab[ y * l + x ] != 0)
			{
				int minus = 0;
				while( (y - (minus+1) > 0) && (tab[(y-(minus+1)) * l + x] == 0) )
				{
					minus+=1;
				}
				tab[(y-minus) * l + x] = tab[y * l + x];
				tab[y * l + x] = 0;
			}
		}
	}
	return 0;
}
