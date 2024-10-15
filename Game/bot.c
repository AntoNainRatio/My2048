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

	/*int tmp1 = mul(b,bottomRight);
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
	}*/

	return res;
}



int* getSpawns(int* b, int* l)
{
	int* res = malloc(16*2*sizeof(int));
	int n = 0;
	for(int y = 0; y < SIZE; y++)
	{
		for(int x = 0; x < SIZE; x++)
		{
			if(b[y * SIZE + x] == 0)
			{
				res[n] = x;
				res[n+1] = y;
				n += 2;
			}
			else
			{
				res[y * SIZE + x] = 1;
			}
		}
	}
	*l = (int)(n / 2);
	res = realloc(res, n*sizeof(int));
	return res;
}




long double rec_depth(int* b, long double preProba, int depth, int currScore)
{
	if(depth == 0)
	{
		return currScore + getMax(b)*preProba;
	}
	else
	{
		long double res = 0;
		int n;

		// UP

		int* up = getCopy(b);
		int vUp = moveUp(up);
		if(vUp != -1)
		{
			int* spawns = getSpawns(b, &n);
			
			for(int i = 0; i < n*2; i += 2)
			{
				int* tmpB = getCopy(up);
				tmpB[ (spawns[i+1]) * SIZE + (spawns[i])] = 2;
				//g_print("preProba = %Lf\n",preProba);
				res += rec_depth(tmpB, ((preProba / n)  * 0.9), depth - 1, getMax(tmpB) * preProba + currScore);
				free(tmpB);

				int* tmpB1 = getCopy(up);
				tmpB1[ (spawns[i+1]) * SIZE + (spawns[i]) ] = 4;
				res += rec_depth(tmpB1, ((preProba / n) * 0.1), depth -1,  getMax(tmpB1) * preProba + currScore);
				free(tmpB1);
			}
			free(spawns);
		}
		free(up);

			// DOWN

		int* down = getCopy(b);
		int vDown = moveDown(down);
		if(vDown != -1)
		{
			int* spawns = getSpawns(b, &n);
			
			for(int i = 0; i < n*2; i += 2)
			{
				int* tmpB = getCopy(down);
				tmpB[ (spawns[i+1]) * SIZE + (spawns[i])] = 2;
				res += rec_depth(tmpB, ((preProba / n) * 0.9), depth - 1,  getMax(tmpB) * preProba + currScore);
				free(tmpB);

				int* tmpB1 = getCopy(down);
				tmpB1[ (spawns[i+1]) * SIZE + (spawns[i]) ] = 4;
				res += rec_depth(tmpB1, ((preProba / n) * 0.1), depth -1,  getMax(tmpB1) * preProba + currScore);
				free(tmpB1);
			}
			free(spawns);
		}
		free(down);

		// LEFT

		int* left = getCopy(b);
		int vLeft = moveLeft(left);
		if(vLeft != -1)
		{
			int* spawns = getSpawns(b, &n);
			
			for(int i = 0; i < n*2; i += 2)
			{
				int* tmpB = getCopy(left);
				tmpB[ (spawns[i+1]) * SIZE + (spawns[i])] = 2;
				res += rec_depth(tmpB, ((preProba / n) * 0.9), depth - 1,  getMax(tmpB) * preProba + currScore);
				free(tmpB);

				int* tmpB1 = getCopy(left);
				tmpB1[ (spawns[i+1]) * SIZE + (spawns[i]) ] = 4;
				res += rec_depth(tmpB1, ((preProba / n) * 0.1), depth -1,  getMax(tmpB1) * preProba + currScore);
				free(tmpB1);
			}
			free(spawns);
		}
		free(left);

		// RIGHT

		int* right = getCopy(b);
		int vRight = moveRight(right);
		if(vRight != -1)
		{
			int* spawns = getSpawns(b, &n);
			
			for(int i = 0; i < n*2; i += 2)
			{
				int* tmpB = getCopy(right);
				tmpB[ (spawns[i+1]) * SIZE + (spawns[i])] = 2;
				res += rec_depth(tmpB, ((preProba / n) * 0.9), depth - 1,  getMax(tmpB) * preProba + currScore);
				free(tmpB);

				int* tmpB1 = getCopy(right);
				tmpB1[ (spawns[i+1]) * SIZE + (spawns[i]) ] = 4;
				res += rec_depth(tmpB1, ((preProba / n) * 0.1), depth -1,  getMax(tmpB1) * preProba + currScore);
				free(tmpB1);
			}
			free(spawns);
		}
		free(right);

		return res;
	}
}




long double* chapo(int* b)
{
	long double* res = calloc(4,sizeof(long double));
	int depth = 4;
	long double preProba = 1;
	int n;

	int* up = getCopy(b);
	int vUp = moveUp(up);
	if(vUp != -1)
	{
		int* spawns = getSpawns(b, &n);
		
		for(int i = 0; i < n*2; i += 2)
		{
			int* tmpB = getCopy(up);
			tmpB[ (spawns[i+1]) * SIZE + (spawns[i])] = 2;
			res[0] += rec_depth(tmpB, ((preProba / n) * 0.9), depth - 1, getMax(tmpB));
			free(tmpB);

			int* tmpB1 = getCopy(up);
			tmpB1[ (spawns[i+1]) * SIZE + (spawns[i]) ] = 4;
			res[0] += rec_depth(tmpB1, ((preProba / n) * 0.1), depth -1, getMax(tmpB1));
			free(tmpB1);
		}
		free(spawns);
	}
	else
	{
		res[0] = -1;
	}
	free(up);

	int* down = getCopy(b);
	int vDown = moveDown(down);
	if(vDown != -1)
	{
		int* spawns = getSpawns(b, &n);
		
		for(int i = 0; i < n*2; i += 2)
		{
			int* tmpB = getCopy(down);
			tmpB[ (spawns[i+1]) * SIZE + (spawns[i])] = 2;
			res[1] += rec_depth(tmpB, ((preProba / n) * 0.9), depth - 1, getMax(tmpB));
			free(tmpB);

			int* tmpB1 = getCopy(down);
			tmpB1[ (spawns[i+1]) * SIZE + (spawns[i]) ] = 4;
			res[1] += rec_depth(tmpB1, ((preProba / n) * 0.1), depth -1, getMax(tmpB1));
			free(tmpB1);
		}
		free(spawns);
	}
	else
	{
		res[1] = -1;
	}
	free(down);

	int* left = getCopy(b);
	int vLeft = moveLeft(left);
	if(vLeft != -1)
	{
		int* spawns = getSpawns(b, &n);
		
		for(int i = 0; i < n*2; i += 2)
		{
			int* tmpB = getCopy(left);
			tmpB[ (spawns[i+1]) * SIZE + (spawns[i])] = 2;
			res[2] += rec_depth(tmpB, ((preProba / n) * 0.9), depth - 1, getMax(tmpB));
			free(tmpB);

			int* tmpB1 = getCopy(left);
			tmpB1[ (spawns[i+1]) * SIZE + (spawns[i]) ] = 4;
			res[2] += rec_depth(tmpB1, ((preProba / n) * 0.1), depth -1, getMax(tmpB1));
			free(tmpB1);
		}
		free(spawns);
	}
	else
	{
		res[2] = -1;
	}
	free(left);

	int* right = getCopy(b);
	int vRight = moveRight(right);
	if(vRight != -1)
	{
		int* spawns = getSpawns(b, &n);
		
		for(int i = 0; i < n*2; i += 2)
		{
			int* tmpB = getCopy(right);
			tmpB[ (spawns[i+1]) * SIZE + (spawns[i])] = 2;
			res[3] += rec_depth(tmpB, ((preProba / n) * 0.9), depth - 1, getMax(tmpB));
			free(tmpB);

			int* tmpB1 = getCopy(right);
			tmpB1[ (spawns[i+1]) * SIZE + (spawns[i]) ] = 4;
			res[3] += rec_depth(tmpB1, ((preProba / n) * 0.1), depth -1, getMax(tmpB1));
			free(tmpB1);
		}
		free(spawns);
	}
	else
	{
		res[3] = -1;
	}
	free(right);


	return res;
}

void doMove(int* b)
{
	long double* moveScore = chapo(b);
	int iMax = 0;
	int i = 1;
	while (i < 4)
	{
		if(moveScore[i] > moveScore[iMax])
		{
			iMax = i;
		}
		i++;
	}

	switch(iMax)
	{
		case 0:
			moveUp(b);
			break;
		case 1:
			moveDown(b);
			break;
		case 2:
			moveLeft(b);
			break;
		default:
			moveRight(b);
			break;
	}
}

