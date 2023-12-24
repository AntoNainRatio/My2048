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
				int minus = 1;
				while((y-minus > 0) && (tab[(y-minus)*l+x] == 0))
				{
					minus++;
				}
				if(tab[(y-minus)*l+x] == 0)
				{
					tab[(y-minus)*l+x] = tab[y*l+x];
					tab[y*l+x] = 0;
				}
				else
				{
					if(tab[(y-minus)*l+x] == tab[y*l+x])
					{
						tab[(y-minus)*l+x] *=2;
						tab[y*l+x] = 0;
						if(arg.maxValue < tab[(y-minus)*l+x])
						{
							arg.maxValue = tab[(y-minus)*l+x];
						}
					}
					else
					{
						tab[(y-minus+1)*l+x] = tab[y*l+x];
						if(minus>1)
						{
							tab[y*l+x] = 0;
						}
					}
				}
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
				int plus = 1;
				while((y+plus < l-1) && (tab[(y+plus) * l + x]==0))
				{
					plus++;
				}
				if((tab[(y+plus) * l + x] == 0))
				{
					tab[(y+plus) * l + x] = tab[y*l+x];
					tab[y*l+x] = 0;
				}
				else
				{
					if(tab[y*l+x] == tab[(y+plus)*l+x])
					{
						tab[(y+plus)*l+x]*=2;
						tab[y*l+x] = 0;
						if(arg.maxValue < tab[(y+plus)*l+x])
						{
							arg.maxValue = tab[(y+plus)*l+x];
						}

					}
					else
					{
						tab[(y+plus-1) * l + x] = tab[y*l+x];
						if(plus>1)
						{
							tab[y*l+x] = 0;
						}
					}
				}
			}
		}
	}
	return 0;
}

int moveLeft(struct gameBoard arg)
{
	int l = arg.size;
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
				}
				else
				{
					if(tab[y*l+x-minus] == tab[y*l+x])
					{
						tab[y*l+x-minus] *= 2;
						tab[y*l+x] = 0;
						if(arg.maxValue < tab[y*l+x-minus])
						{
							arg.maxValue = tab[y*l+x-minus];
						}
					}
					else
					{
						tab[y*l+x-minus+1] = tab[y*l+x];
						if(minus>1)
						{
							tab[y*l+x] = 0;
						}
					}
				}
			}
		}
	}
	return 0;
}

int moveRight(struct gameBoard arg)
{
	int l = arg.size;
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
				}
				else
				{
					if(tab[y*l+x+plus] == tab[y*l+x])
					{
						tab[y*l+x+plus] *= 2;
						tab[y*l+x] = 0;
						if(arg.maxValue < tab[y*l+x+plus])
						{
							arg.maxValue = tab[y*l+x+plus];
						}

					}
					else
					{
						tab[y*l+x+plus-1] = tab[y*l+x];
						if(plus>1)
						{
							tab[y*l+x] = 0;
						}
					}
				}
			}
		}
	}
	return 0;
}

int DoMove(struct gameBoard arg)
{
	char res;
	scanf("%c",&res);
	if(res == 'a')
	{
		moveLeft(arg);
		return 0;
	}
	else if(res == 'w')
	{
		moveUp(arg);
		return 0;
	}
	else if(res == 's')
	{
		moveDown(arg);
		return 0;
	}
	else if(res == 'd')
	{
		moveRight(arg);
		return 0;
	}
	else if(res == 'h')
	{
		printf("%s\n%s\n%s\n%s\n%s\n%s\n","Help for controls: ","w for up","s for down","a for left","d for right","Hope it helped you :)");
		return -1;
	}
	return 0;;
}
