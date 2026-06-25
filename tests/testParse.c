#include "../include/parse.h"
#include "../include/board.h"
#include <criterion/assert.h>
#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <stdio.h>
#include <stdlib.h>

Test(test_parseStr, simple)
{
    int  *a = parseStr(
            "1 2 3 4\n"
            "5 6 7 8\n"
            "9 10 11 12\n"
            "13 14 15 16");

    for (int i = 0; i < 16; i++)
    {
        cr_expect(a[i] == i + 1);
    }

    free(a);
}

Test(test_parseStr, skip_space)
{
    int  *a = parseStr(
            " 1   2   3   4\n"
            " 5   6   7   8\n"
            " 9  10  11  12\n"
            "13  14  15  16");

    for (int i = 0; i < 16; i++)
    {
        cr_expect(a[i] == i + 1);
    }

    free(a);
}
