/*Petite ref Epita
  Merci algo.master*/

#include "board.h"
#include "control.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "master.h"

int* getCopy(struct gameBoard arg)
{
	int l = arg.size;
	int* tab = arg.board;
	int* res = (int*)malloc(l*l*sizeof(int));
	for(int i = 0; i < l; i++)
	{
		for(int j = 0; j < l; j++)
		{
			res[i*l+j] = tab[i*l+j];
		}
	}
	return res;
}

int* boardUp(struct gameBoard arg)
{
	int valid = -1;
	int l = arg.size;
	int* m = calloc(l*l,sizeof(int));
	int* tab = getCopy(arg);
	for(int x = 0; x < l; x++)
	{
		for(int y = 1; y < l; y++)
		{
			if(tab[ y * l + x ] != 0)
			{
				int minus = 1;
				while((y-minus > 0) && (tab[(y-minus)*l+x] == 0))
				{
					minus++;
				}
				if(tab[(y-minus)*l+x] == 0)
				{
					tab[(y-minus)*l+x] = tab[y*l+x];
					tab[y*l+x] = 0;
					valid = 0;
				}
				else
				{
					if(tab[(y-minus)*l+x] == tab[y*l+x] && m[(y-minus)*l+x]==0)
					{
						tab[(y-minus)*l+x] *=2;
						tab[y*l+x] = 0;
						valid = 0;
						m[(y-minus)*l+x] = 1;
					}
					else
					{
						tab[(y-minus+1)*l+x] = tab[y*l+x];
						if(minus>1)
						{
							tab[y*l+x] = 0;
							valid = 0;
						}
					}
				}
			}
		}
	}
	free(m);
	if(valid==0)
	{
		return tab;
	}
	else
	{
		return NULL;
	}
}


int* boardDown(struct gameBoard arg)
{
	int valid = -1;
	int l = arg.size;
	int* m = calloc(l*l, sizeof(int));
	int* tab = getCopy(arg);
	for(int x = 0; x < l; x++)
	{
		for(int y = l-2; y >= 0; y--)
		{
			if(tab[y * l + x] != 0)
			{
				int plus = 1;
				while((y+plus < l-1) && (tab[(y+plus) * l + x]==0))
				{
					plus++;
				}
				if((tab[(y+plus) * l + x] == 0))
				{
					tab[(y+plus) * l + x] = tab[y*l+x];
					tab[y*l+x] = 0;
					valid = 0;
				}
				else
				{
					if(tab[y*l+x] == tab[(y+plus)*l+x] && m[(y+plus)*l+x] == 0)
					{
						tab[(y+plus)*l+x]*=2;
						tab[y*l+x] = 0;
						m[(y+plus)*l+x] = 1;
						valid = 0;
					}
					else
					{
						tab[(y+plus-1) * l + x] = tab[y*l+x];
						if(plus>1)
						{
							tab[y*l+x] = 0;
							valid = 0;
						}
					}
				}
			}
		}
	}
	free(m);
	if(valid == 0)
	{
		return tab;
	}
	else
	{
		return NULL;
	}
}

int* boardLeft(struct gameBoard arg)
{
	int valid = -1;
	int l = arg.size;
	int* m = calloc(l*l, sizeof(int));
	int* tab = getCopy(arg);
	for(int y = 0; y < l; y++)
	{
		for(int x = 1; x < l; x++)
		{
			if(tab[y * l + x] != 0)
			{
				int minus = 1;
				while(x-minus > 0 && tab[y*l+x-minus]==0)
				{
					minus++;
				}
				if((tab[y*l + x-minus]==0))
				{
					tab[y*l+x-minus] = tab[l*y+x];
					tab[y*l+x] = 0;
					valid = 0;
				}
				else
				{
					if(tab[y*l+x-minus] == tab[y*l+x] && m[y*l+x-minus] == 0)
					{
						tab[y*l+x-minus] *= 2;
						tab[y*l+x] = 0;
						valid = 0;
					}
					else
					{
						tab[y*l+x-minus+1] = tab[y*l+x];
						if(minus>1)
						{
							tab[y*l+x] = 0;
							valid = 0;
						}
					}
				}
			}
		}
	}
	free(m);
	if(valid == 0)
	{
		return tab;
	}
	else
	{
		return NULL;
	}
}


int* boardRight(struct gameBoard arg)
{
	int valid = -1;
	int l = arg.size;
	int* m = calloc(l*l, sizeof(int));
	int* tab = getCopy(arg);
	for(int y = 0; y < l; y++)
	{
		for(int x = l-2; x >= 0; x--)
		{
			if(tab[y*l+x] != 0)
			{
				int plus = 1;
				while((x+plus < l-1) && (tab[y * l + x+plus] == 0))
				{
					plus++;
				}
				if(tab[y * l +x+plus] == 0)
				{
					tab[y*l +x+plus] = tab[y*l+x];
					tab[y*l+x] = 0;
					valid = 0;
				}
				else
				{
					if(tab[y*l+x+plus] == tab[y*l+x] && m[y*l+x+plus] == 0)
					{
						tab[y*l+x+plus] *= 2;
						tab[y*l+x] = 0;
						m[y*l+x+plus] = 1;
						valid = 0;
					}
					else
					{
						tab[y*l+x+plus-1] = tab[y*l+x];
						if(plus>1)
						{
							tab[y*l+x] = 0;
							valid =0;
						}
					}
				}
			}
		}
	}
	free(m);
	if(valid == 0)
	{
		return tab;
	}
	else
	{
		return NULL;
	}
}

/*int getScoreFromState(struct gameBoard arg)
{
	
}*/
