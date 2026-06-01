#include "../include/bot.h"

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

#include "../include/board.h"
#include "../include/control.h"

#define MAX_DEPTH 4

int bottomLeft[SIZE * SIZE] = {
    2,   4,    8,    16,   256,   128,   64,    32,
    512, 1024, 2048, 4096, 65536, 32768, 16384, 8192
};

int bottomRight[SIZE * SIZE] = { 16,   8,     4,     2,    32,   64,
                                 128,  256,   4096,  2048, 1024, 512,
                                 8192, 16384, 32768, 65536 };

int topRight[SIZE * SIZE] = { 8192, 16384, 32768, 65536, 4096, 2048, 1024, 512,
                              32,   64,    128,   256,   16,   8,    4,    2 };

int topLeft[SIZE * SIZE] = { 65536, 32768, 16384, 8192, 512, 1024, 2048, 4096,
                             256,   128,   64,    32,   2,   4,    8,    16 };

typedef struct {
    int *board;                 // Copie du board à évaluer
    int direction;              // 0=UP, 1=DOWN, 2=LEFT, 3=RIGHT
    long double score;          // Résultat du calcul
    int valid;                  // 1 si le mouvement était possible
    char *label;               // "UP", "DOWN", "LEFT", "RIGHT"
} ThreadArg;


int getMax(int *b) {
    int res = mul(b, bottomLeft);

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

int *getSpawns(int *b, int *l) {
    int *res = malloc(16 * 2 * sizeof(int));
    int n = 0;
    
    for (int y = 0; y < SIZE; y++) {
        for (int x = 0; x < SIZE; x++) {
            if (b[y * SIZE + x] == 0) {
                res[n] = x;
                res[n + 1] = y;
                n += 2;
            }
        }
    }
    
    *l = (int)(n / 2);
    res = realloc(res, n * sizeof(int));
    return res;
}


long double rec_depth(int *b, long double curr, int depth) {
    if (depth == 0) {
        return curr;
    }
    
    long double res = 0;
    int n;

    // UP
    int *up = getCopy(b);
    int vUp = moveUp(up);
    if (vUp != -1) {
        int *spawns = getSpawns(up, &n);
        for (int i = 0; i < n * 2; i += 2) {
            int *tmpB = getCopy(up);
            tmpB[(spawns[i + 1]) * SIZE + (spawns[i])] = 2;
            res += 0.9 * rec_depth(tmpB, curr + (getMax(tmpB)), depth - 1);
            free(tmpB);

            int *tmpB1 = getCopy(up);
            tmpB1[(spawns[i + 1]) * SIZE + (spawns[i])] = 4;
            res += 0.1 * rec_depth(tmpB1, curr + (getMax(tmpB1)), depth - 1);
            free(tmpB1);
        }
        free(spawns);
    }
    free(up);

    // DOWN
    int *down = getCopy(b);
    int vDown = moveDown(down);
    if (vDown != -1) {
        int *spawns = getSpawns(down, &n);
        for (int i = 0; i < n * 2; i += 2) {
            int *tmpB = getCopy(down);
            tmpB[(spawns[i + 1]) * SIZE + (spawns[i])] = 2;
            res += 0.9 * rec_depth(tmpB, curr + (getMax(tmpB)), depth - 1);
            free(tmpB);

            int *tmpB1 = getCopy(down);
            tmpB1[(spawns[i + 1]) * SIZE + (spawns[i])] = 4;
            res += 0.1 * rec_depth(tmpB1, curr + (getMax(tmpB1)), depth - 1);
            free(tmpB1);
        }
        free(spawns);
    }
    free(down);

    // LEFT
    int *left = getCopy(b);
    int vLeft = moveLeft(left);
    if (vLeft != -1) {
        int *spawns = getSpawns(left, &n);
        for (int i = 0; i < n * 2; i += 2) {
            int *tmpB = getCopy(left);
            tmpB[(spawns[i + 1]) * SIZE + (spawns[i])] = 2;
            res += 0.9 * rec_depth(tmpB, curr + getMax(tmpB), depth - 1);
            free(tmpB);

            int *tmpB1 = getCopy(left);
            tmpB1[(spawns[i + 1]) * SIZE + (spawns[i])] = 4;
            res += 0.1 * rec_depth(tmpB1, curr + getMax(tmpB1), depth - 1);
            free(tmpB1);
        }
        free(spawns);
    }
    free(left);

    // RIGHT
    int *right = getCopy(b);
    int vRight = moveRight(right);
    if (vRight != -1) {
        int *spawns = getSpawns(right, &n);
        for (int i = 0; i < n * 2; i += 2) {
            int *tmpB = getCopy(right);
            tmpB[(spawns[i + 1]) * SIZE + (spawns[i])] = 2;
            res += 0.9 * rec_depth(tmpB, curr + getMax(tmpB), depth - 1);
            free(tmpB);

            int *tmpB1 = getCopy(right);
            tmpB1[(spawns[i + 1]) * SIZE + (spawns[i])] = 4;
            res += 0.1 * rec_depth(tmpB1, curr + getMax(tmpB1), depth - 1);
            free(tmpB1);
        }
        free(spawns);
    }
    free(right);

    return res;
}


void *evaluate_direction(void *arg) {
    ThreadArg *threadData = (ThreadArg *)arg;
    
    int *testBoard = threadData->board;  // Copie unique pour ce thread
    int direction = threadData->direction;
    
    int moveValid = -1;
    switch (direction) {
        case 0:  // UP
            moveValid = moveUp(testBoard);
            break;
        case 1:  // DOWN
            moveValid = moveDown(testBoard);
            break;
        case 2:  // LEFT
            moveValid = moveLeft(testBoard);
            break;
        case 3:  // RIGHT
            moveValid = moveRight(testBoard);
            break;
    }
    
    if (moveValid == -1) {
        threadData->valid = 0;
        threadData->score = -1;
        return NULL;
    }
    
    threadData->valid = 1;
    
    long double result = 0;
    int n;
    int *spawns = getSpawns(testBoard, &n);
    
    int curr = 0;
    
    for (int i = 0; i < n * 2; i += 2) {
	// 2 spawns
        int *tmpB = getCopy(testBoard);
        tmpB[(spawns[i + 1]) * SIZE + (spawns[i])] = 2;
        result += 0.9 * rec_depth(tmpB, curr + getMax(tmpB), MAX_DEPTH - 1);
        free(tmpB);
        
	// 4 spawns
        int *tmpB1 = getCopy(testBoard);
        tmpB1[(spawns[i + 1]) * SIZE + (spawns[i])] = 4;
        result += 0.1 * rec_depth(tmpB1, curr + getMax(tmpB1), MAX_DEPTH - 1);
        free(tmpB1);
    }
    
    free(spawns);
    
    threadData->score = result;
    return NULL;
}

long double *chapo_threaded(int *b) {
    long double *res = calloc(4, sizeof(long double));
    pthread_t threads[4];
    ThreadArg threadArgs[4];
    
    const char *labels[] = { "UP", "DOWN", "LEFT", "RIGHT" };
    
    int *boardCopies[4];
    for (int i = 0; i < 4; i++) {
        boardCopies[i] = getCopy(b);
    }
    
    for (int i = 0; i < 4; i++) {
        threadArgs[i].board = boardCopies[i];  // Copie unique par thread
        threadArgs[i].direction = i;
        threadArgs[i].score = 0;
        threadArgs[i].valid = 0;
        threadArgs[i].label = (char *)labels[i];
        
        pthread_create(&threads[i], NULL, evaluate_direction, &threadArgs[i]);
    }
    
    for (int i = 0; i < 4; i++) {
        pthread_join(threads[i], NULL);
    }
    
    for (int i = 0; i < 4; i++) {
        if (threadArgs[i].valid == 1) {
            res[i] = threadArgs[i].score;
        } else {
            res[i] = -1;
        }
        free(boardCopies[i]);  // Libère la copie
    }
    
    return res;
}


void doMove(int *b) {
    long double *moveScore = chapo_threaded(b);
    
    int iMax = 0;
    for (int i = 1; i < 4; i++) {
        if (moveScore[i] > moveScore[iMax]) {
            iMax = i;
        }
    }
    
    switch (iMax) {
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
    
    free(moveScore);
}
