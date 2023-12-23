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
				if(y-(minus+1) >=0 && tab[(y-(minus+1)) * l +x]==0)
				{
					tab[(y-minus-1) * l + x] = tab[y * l + x];
				}
				else
				{
					tab[(y-minus) * l + x] = tab[y * l + x];
				}
				tab[y * l + x] = 0;
			}
		}
	}
	return 0;
}

int moveDown(struct gameBoard arg)
{
	int l = arg.size;
	int* tab = arg.board;
	for(int x = 0; x < l; x++)
	{
		for(int y = l-2; y >= 0; y--)
		{
			if(tab[y * l + x] != 0)
			{
				int plus = 0;
				while((y+plus+1 < l) && (tab[(y+plus+1) * l + x]==0))
				{
					plus++;
				}
				if((y+plus+1 < l) && (tab[(y+plus+1) * l + x]==0))
				{
					tab[(y+plus+1) * l + x] = tab[y*l+x];
				}
				else
				{
					tab[(y+plus) * l + x] = tab[y*l+x];
				}
				tab[y * l + x] = 0;
			}
		}
	}
	return 0;
}
