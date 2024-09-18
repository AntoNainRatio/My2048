#ifndef BOARD_H
#define BOARD_H

#include <cairo.h>

#define SIZE 4

int* getBoard(int n);
int mul(int* a, int* b);
int* getCopy(int* b);
void putNewValue(int* board);
int isFull(int* b);
int possibleMove(int* board);
void drawBoard(int* b, int screenWidth, int screenHeight, cairo_t *cr);
void printBoard(int* b);
void freeBoard(int* b);

#endif
