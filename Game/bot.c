#include <stdio.h>
#include <stdlib.h>
#include "board.h"
#include "control.h"
#include "bot.h"

int bottomLeft[SIZE*SIZE] = 
{
	2, 4, 8, 16,
	256, 128, 64, 32,
	512, 1024, 2048, 4096,
	65536, 32768, 16384, 8192
};

int bottomRight[SIZE*SIZE] =
{
	16, 8, 4, 2,
	32, 64, 128, 256,
	4096, 2048, 1024,512,
	8192, 16384, 32768, 65536
};

int topRight[SIZE*SIZE] =
{
	8192, 16384, 32768, 65536,
	4096, 2048, 1024, 512,
	32, 64, 128, 256,
	16, 8, 4, 2
};

int topLeft[SIZE*SIZE] =
{
	65536, 32768, 16384, 8192,
	512, 1024, 2048, 4096,
	256, 128, 64, 32,
	2, 4, 8, 16
};

int getMax(int* b)
{
	int res = mul(b,bottomLeft);

	int tmp1 = mul(b,bottomRight);
	if(tmp1 > res)
	{
		res = tmp1;
	}

	int tmp2 = mul(b,topRight);
	if(tmp2 > res)
	{
		res = tmp2;
	}

	int tmp3 = mul(b, topLeft);
	if(tmp3 > res)
	{
		res = tmp3;
	}

	return res;
}

/*void rec_depth(int* b, int depth, int* scores, int* probas, int index)
{
	if(depth == 0)
	{
		
	}
	int* up = getCopy(b);
	int vUp = moveUp(up);
	if(vUp != -1)
	{
		
	}
}*/

int* getDepthMovesValue(int* b, int d)
{
	int* res = malloc(4*sizeof(int *));

	

	return res;
}

