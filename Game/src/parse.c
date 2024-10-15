#include "../include/board.h"

int *parseStr(char * str)
{
    int *res = initBoard(SIZE);
    int y = 0;
    int x = 0;
    for (int i = 0; str[i] != '\0'; i++)
    {
        int tmp = 0;
        if (str[i] == ' ')
        {
            res[y * SIZE + x] = tmp;
            tmp = 0;
            x++;
        }
        else if (str[i] == '\n')
        {
            res[y * SIZE + x] = tmp;
            tmp = 0;
            y++;
            x = 0;
        }
        else
        {
            tmp = tmp + str[i] - '0';
        }
    }
    res[y * SIZE + x] = tmp;
    return res;
}
