#include "../include/control.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/board.h"

int moveUp(int *tab)
{
    int valid = -1;
    int l = SIZE;
    int *m = calloc(l * l, sizeof(int));
    for (int x = 0; x < l; x++)
    {
        for (int y = 1; y < l; y++)
        {
            if (tab[y * l + x] != 0)
            {
                int minus = 1;
                while ((y - minus > 0) && (tab[(y - minus) * l + x] == 0))
                {
                    minus++;
                }
                if (tab[(y - minus) * l + x] == 0)
                {
                    tab[(y - minus) * l + x] = tab[y * l + x];
                    tab[y * l + x] = 0;
                    valid = 0;
                }
                else
                {
                    if (tab[(y - minus) * l + x] == tab[y * l + x]
                        && m[(y - minus) * l + x] == 0)
                    {
                        tab[(y - minus) * l + x] *= 2;
                        //*arg.score = *arg.score + tab[(y-minus)*l+x];
                        tab[y * l + x] = 0;
                        valid = 0;
                        m[(y - minus) * l + x] = 1;
                    }
                    else
                    {
                        tab[(y - minus + 1) * l + x] = tab[y * l + x];
                        if (minus > 1)
                        {
                            tab[y * l + x] = 0;
                            valid = 0;
                        }
                    }
                }
            }
        }
    }
    free(m);
    return valid;
}

int moveDown(int *tab)
{
    int valid = -1;
    int l = SIZE;
    int *m = calloc(l * l, sizeof(int));
    for (int x = 0; x < l; x++)
    {
        for (int y = l - 2; y >= 0; y--)
        {
            if (tab[y * l + x] != 0)
            {
                int plus = 1;
                while ((y + plus < l - 1) && (tab[(y + plus) * l + x] == 0))
                {
                    plus++;
                }
                if ((tab[(y + plus) * l + x] == 0))
                {
                    tab[(y + plus) * l + x] = tab[y * l + x];
                    tab[y * l + x] = 0;
                    valid = 0;
                }
                else
                {
                    if (tab[y * l + x] == tab[(y + plus) * l + x]
                        && m[(y + plus) * l + x] == 0)
                    {
                        tab[(y + plus) * l + x] *= 2;
                        //*arg.score = *arg.score + tab[(y+plus)*l+x];
                        tab[y * l + x] = 0;
                        m[(y + plus) * l + x] = 1;
                        valid = 0;
                    }
                    else
                    {
                        tab[(y + plus - 1) * l + x] = tab[y * l + x];
                        if (plus > 1)
                        {
                            tab[y * l + x] = 0;
                            valid = 0;
                        }
                    }
                }
            }
        }
    }
    free(m);
    return valid;
}

int moveLeft(int *tab)
{
    int valid = -1;
    int l = SIZE;
    int *m = calloc(l * l, sizeof(int));
    for (int y = 0; y < l; y++)
    {
        for (int x = 1; x < l; x++)
        {
            if (tab[y * l + x] != 0)
            {
                int minus = 1;
                while (x - minus > 0 && tab[y * l + x - minus] == 0)
                {
                    minus++;
                }
                if ((tab[y * l + x - minus] == 0))
                {
                    tab[y * l + x - minus] = tab[l * y + x];
                    tab[y * l + x] = 0;
                    valid = 0;
                }
                else
                {
                    if (tab[y * l + x - minus] == tab[y * l + x]
                        && m[y * l + x - minus] == 0)
                    {
                        tab[y * l + x - minus] *= 2;
                        //*arg.score = *arg.score + tab[y*l+x-minus];
                        tab[y * l + x] = 0;
                        valid = 0;
                    }
                    else
                    {
                        tab[y * l + x - minus + 1] = tab[y * l + x];
                        if (minus > 1)
                        {
                            tab[y * l + x] = 0;
                            valid = 0;
                        }
                    }
                }
            }
        }
    }
    free(m);
    return valid;
}

int moveRight(int *tab)
{
    int valid = -1;
    int l = SIZE;
    int *m = calloc(l * l, sizeof(int));
    for (int y = 0; y < l; y++)
    {
        for (int x = l - 2; x >= 0; x--)
        {
            if (tab[y * l + x] != 0)
            {
                int plus = 1;
                while ((x + plus < l - 1) && (tab[y * l + x + plus] == 0))
                {
                    plus++;
                }
                if (tab[y * l + x + plus] == 0)
                {
                    tab[y * l + x + plus] = tab[y * l + x];
                    tab[y * l + x] = 0;
                    valid = 0;
                }
                else
                {
                    if (tab[y * l + x + plus] == tab[y * l + x]
                        && m[y * l + x + plus] == 0)
                    {
                        tab[y * l + x + plus] *= 2;
                        //*arg.score = *arg.score + tab[y*l+x+plus];
                        tab[y * l + x] = 0;
                        m[y * l + x + plus] = 1;
                        valid = 0;
                    }
                    else
                    {
                        tab[y * l + x + plus - 1] = tab[y * l + x];
                        if (plus > 1)
                        {
                            tab[y * l + x] = 0;
                            valid = 0;
                        }
                    }
                }
            }
        }
    }
    free(m);
    return valid;
}
