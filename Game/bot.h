#ifndef BOT_H
#define BOT_H

int getMax(int* b);
int* getSpawns(int* b, int* l);
long double rec_depth(int* b, long double preProba, int depth);
long double* chapo(int* b);
void doMove(int * b);

#endif
