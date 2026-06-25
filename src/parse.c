#include "../include/board.h"

int *parseStr(char *str)
{
    int *res = getBoard(SIZE);
    int y = 0;
    int x = 0;
    int tmp = 0;
    int reading = 0;
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (str[i] >= '0' && str[i] <= '9')
        {
            tmp = tmp * 10 + str[i] - '0';
            reading = 1;
        }
        else if (str[i] == '\n')
        {
            if (reading)
            {
                res[y * SIZE + x] = tmp;
                x++;
            }
            tmp = 0;
            reading = 0;
            y++;
            x = 0;
        }
        else
        {
            if (reading)
            {
                res[y * SIZE + x] = tmp;
                x++;
            }
            tmp = 0;
            reading = 0;
        }
    }
    if (reading)
        res[y * SIZE + x] = tmp;
    return res;
}
