#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "board.h"
#include "control.h"

/*struct game
{
	int score;
	int size;
	struct gameBoard board;
	int status;
};*/


int moveUp(struct game arg)
{
	int valid = -1;
	int l = arg.size;
	int* m = calloc(l*l,sizeof(int));
	int* tab = arg.board;
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
						tab[(y-minus)*l+x] *= 2;
						int newscore = *arg.score + tab[(y-minus)*l+x];
						arg.score = &newscore;
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
	return valid;
}

int moveDown(struct game arg)
{
	int valid = -1;
	int l = arg.size;
	int* m = calloc(l*l, sizeof(int));
	int* tab = arg.board;
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
						int newscore = *arg.score + tab[(y+plus)*l+x];
						arg.score = &newscore;
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
	return valid;
}

int moveLeft(struct game arg)
{
	int valid = -1;
	int l = arg.size;
	int* m = calloc(l*l, sizeof(int));
	int* tab = arg.board;
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
						int newscore = (*arg.score + tab[y*l+x-minus]);
						arg.score = &newscore;
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
	return valid;
}

int moveRight(struct game arg)
{
	int valid = -1;
	int l = arg.size;
	int* m = calloc(l*l, sizeof(int));
	int* tab = arg.board;
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
						int newscore = (*arg.score + tab[y*l+x+plus]);
						arg.score = &newscore;
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
	return valid;
}

int DoMove(struct game arg)
{
	char res;
	scanf("%c", &res);
	if(res == 'a')
	{
		return moveLeft(arg);
	}
	else if(res == 'w')
	{
		return moveUp(arg);
	}
	else if(res == 's')
	{
		return moveDown(arg);
	}
	else if(res == 'd')
	{
		return moveRight(arg);
	}
	else if(res == 'h')
	{
		printf("%s\n%s\n%s\n%s\n%s\n%s\n","Help for controls: ","w for up","s for down","a for left","d for right","Hope it helped you :)");
		return -1;
	}
	else
	{
		return -1;
	}
}

int DoRandomMove(struct game arg)
{
	int m = rand() % 4;
	if(m == 0)
	{
		return moveLeft(arg);
	}
	else if(m == 1)
	{
		return moveRight(arg);
	}
	else if(m == 2)
	{
		return moveUp(arg);
	}
	else
	{
		return moveDown(arg);
	}
}
