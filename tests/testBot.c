#include "../include/parse.h"
#include "../include/bot.h"
#include <criterion/assert.h>
#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <stdio.h>
#include <string.h>


#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3


Test(test_getMax, sameScore)
{
    int *a = parseStr(
            "64 0 0 2\n"
            "0 0 0 0\n"
            "8 2 2 4\n"
            "32 32 16 8");
    int maxA = getMax(a);

    int *b = parseStr(
            "0 0 0 2\n"
            "0 0 0 64\n"
            "8 2 2 4\n"
            "32 32 16 8");
    int maxB = getMax(b);

    cr_expect(maxA > maxB);

    free(a);
    free(b);
}

Test(test_getMax, case1Seen)
{
    int *a = parseStr(
            "0 0 0 0\n"
            "0 0 0 0\n"
            "16 0 0 0\n"
            "32 8 2 4");
    int maxA = getMax(a);

    int *b = parseStr(
            "0 0 0 0\n"
            "0 0 0 0\n"
            "16 2 0 0\n"
            "32 8 4 0");
    int maxB = getMax(b);

    cr_expect(maxA < maxB);

    free(a);
    free(b);
}


Test(test_getMax, case2)
{
    int *a = parseStr(
            "0 0 0 0\n"
            "0 0 0 0\n"
            "2 0 0 0\n"
            "8 0 0 2");
    int maxA = getMax(a);

    int *b = parseStr(
            "0 0 0 0\n"
            "0 0 0 0\n"
            "4 0 0 0\n"
            "8 0 0 0");
    int maxB = getMax(b);

    cr_expect(maxA > maxB);

    free(a);
    free(b);
}

static int choice(int *b)
{
    long double *scores = chapo_threaded(b);
    int best = 0;
    for (int i = 1; i < 4; i++)
    {
        if (scores[i] > scores[best])
        {
            best = i;
        }
    }
    free(scores);
    return best;
}

Test(test_choice, simple)
{
    int *a = parseStr(
            "4 4 2 0\n"
            "0 0 0 0\n"
            "0 0 0 0\n"
            "0 0 0 0");

    cr_expect(choice(a) == LEFT);

    free(a);
}

Test(test_choice, simple2)
{
    int *a = parseStr(
            "4 4 2 0\n"
            "0 0 0 0\n"
            "0 0 0 0\n"
            "0 0 0 64");

    cr_expect(choice(a) == LEFT);

    free(a);
}

Test(test_choice, simple3)
{
    int *a = parseStr(
            "4 4 2 0\n"
            "0 0 0 0\n"
            "0 0 0 0\n"
            "2 0 0 64");

    cr_expect(choice(a) == UP);

    free(a);
}

Test(test_choice, simple4)
{
    int *a = parseStr(
            "4 2 2 4\n"
            "0 0 0 0\n"
            "0 0 0 64\n"
            "2 0 0 2");

    cr_expect(choice(a) == LEFT);

    free(a);
}
