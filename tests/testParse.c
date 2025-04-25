#include "../include/parse.h"
#include "../include/board.h"
#include <stdio.h>
#include <stdlib.h>


int main(void)
{
    int  *a = parseStr("1 2 3 4\n5 6 7 8\n9 10 11 12\n13 14 15 16");
    printBoard(a);
    free(a);
    return 0;
}
