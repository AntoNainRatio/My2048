#include "../include/parse.h"
#include "../include/bot.h"
#include <criterion/assert.h>
#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <stdio.h>
#include <string.h>


Test(test_getMax, sameScore)
{
    int *a = parseStr("64 0 0 2\n0 0 0 0\n8 2 2 4\n32 32 16 8");
    int maxA = getMax(a);
    int *b = parseStr("0 0 0 2\n0 0 0 64\n8 2 2 4\n32 32 16 8");
    int maxB = getMax(b);
    cr_expect(maxA < maxB);
    free(a);
    free(b);
}
