#include "../include/parse.h"
#include "../include/bot.h"
#include <criterion/assert.h>
#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <stdio.h>
#include <string.h>


Test(test_getMax, sameScore)
{
    int *a = parseStr(
            "64 0 0 2\n
            0 0 0 0\n
            8 2 2 4\n
            32 32 16 8");
    int maxA = getMax(a);

    int *b = parseStr(
            "0 0 0 2\n
            0 0 0 64\n
            8 2 2 4\n
            32 32 16 8");
    int maxB = getMax(b);

    cr_expect(maxA < maxB);

    free(a);
    free(b);
}

Test(test_getMax, case1Seen)
{
    int *a = parseStr(
            "0 0 0 0\n
            0 0 0 0\n
            16 0 0 0\n
            32 8 2 4
            ");
    int maxA = getMax(a);

    int *b = parseStr("
            0 0 0 0\n
            0 0 0 0\n
            16 2 0 0\n
            32 8 4 0
            ");
    int maxB = getMax(b);

    cr_expect(maxA < maxB);

    free(a);
    free(b);
}


Test(test_getMax, case2)
{
    int *a = parseStr(
            "0 0 0 0\n
            0 0 0 0\n
            2 0 0 0\n
            8 0 0 2");
    int maxA = getMax(a);

    int *b = parseStr("
            0 0 0 0\n
            0 0 0 0\n
            4 0 0 0\n
            8 0 0 0");
    int maxB = getMax(b);

    cr_expect(maxA < maxB);

    free(a);
    free(b);
}
