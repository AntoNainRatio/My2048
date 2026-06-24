#include "../include/parse.h"
#include "../include/board.h"
#include <stdio.h>
#include <stdlib.h>


int main(void)
{
    int  *a = parseStr(
            "1 2 3 4\n"
            "5 6 7 8\n"
            "9 10 11 12\n"
            "13 14 15 16");

    for (int i = 0; i < 16; i++)
    {
        if (a[i] != i + 1)
        {

            free(a);
            return 1;
        }
    }

    free(a);
    return 0;
}
