#include "../include/board.h"

#include <cairo.h>
#include <gtk/gtk.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int *getBoard(int n)
{
    int *res = calloc(n * n, sizeof(int));
    return res;
}

int mul(int *a, int *b)
{
    int res = 0;
    for (int y = 0; y < SIZE; y++)
    {
        for (int x = 0; x < SIZE; x++)
        {
            res += a[y * SIZE + x] * b[y * SIZE + x];
        }
    }
    return res;
}

int *getCopy(int *b)
{
    int *res = malloc(SIZE * SIZE * sizeof(int));
    for (int y = 0; y < SIZE; y++)
    {
        for (int x = 0; x < SIZE; x++)
        {
            res[y * SIZE + x] = b[y * SIZE + x];
        }
    }
    return res;
}

void putNewValue(int *board)
{
    int x = rand() % SIZE;
    int y = rand() % SIZE;
    while (board[y * SIZE + x] != 0)
    {
        x = rand() % SIZE;
        y = rand() % SIZE;
    }
    int new = rand() % 10;
    board[y * SIZE + x] = (new > 0 ? 1 : 2) * 2;
}

int getNbVide(int *b)
{
    int res = 0;
    for (int y = 0; y < SIZE; y++)
    {
        for (int x = 0; x < SIZE; x++)
        {
            if (b[y * SIZE + x] == 0)
            {
                res++;
            }
        }
    }
    return res;
}

int isFull(int *b)
{
    if (getNbVide(b) == 0)
    {
        return 0;
    }
    return -1;
}

int possibleMove(int *board)
{
    int n = SIZE;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (board[i * n + j] == 0)
            {
                return 1;
            }
            if (i + 1 < n && board[(i + 1) * n + j] == board[i * n + j])
            {
                return 1;
            }
            if (i - 1 >= 0 && board[(i - 1) * n + j] == board[i * n + j])
            {
                return 1;
            }
            if (j + 1 < n && board[i * n + j + 1] == board[i * n + j])
            {
                return 1;
            }
            if (j - 1 >= 0 && board[i * n + j - 1] == board[i * n + j])
            {
                return 1;
            }
        }
    }
    return 0;
}

void drawBoard(int *b, int screenWidth, int screenHeight, cairo_t *cr)
{
    cairo_set_source_rgba(cr, 0.73, 0.69, 0.63, 1);
    cairo_rectangle(cr, 0, 0, screenWidth, screenHeight);
    cairo_fill(cr);
    int screenSize;
    if (screenWidth < screenHeight)
    {
        screenSize = screenWidth;
    }
    else
    {
        screenSize = screenHeight;
    }

    int borderSize = screenSize / 100;
    int tileSize = screenSize / 4.2;

    int yScreen = borderSize;

    for (int y = 0; y < SIZE; y++)
    {
        int xScreen = borderSize;
        for (int x = 0; x < SIZE; x++)
        {
            int p = 1;
            int n = 0;
            while (p < b[y * SIZE + x])
            {
                p = p * 2;
                n++;
            }
            switch (n)
            {
            case (0):
                cairo_set_source_rgba(cr, 0.80, 0.76, 0.71, 1);
                break;
            case (1):
                cairo_set_source_rgba(cr, 0.93, 0.89, 0.85, 1);
                break;
            case (2):
                cairo_set_source_rgba(cr, 0.93, 0.88, 0.78, 1);
                break;
            case (3):
                cairo_set_source_rgba(cr, 0.95, 0.70, 0.47, 1);
                break;
            case (4):
                cairo_set_source_rgba(cr, 0.96, 0.58, 0.39, 1);
                break;
            case (5):
                cairo_set_source_rgba(cr, 0.96, 0.49, 0.37, 1);
                break;
            case (6):
                cairo_set_source_rgba(cr, 0.96, 0.37, 0.23, 1);
                break;
            case (7):
                cairo_set_source_rgba(cr, 0.96, 0.81, 0.44, 1);
                break;
            case (8):
                cairo_set_source_rgba(cr, 0.93, 0.80, 0.38, 1);
                break;
            case (9):
                cairo_set_source_rgba(cr, 0.93, 0.78, 0.33, 1);
                break;
            case (10):
                cairo_set_source_rgba(cr, 0.93, 0.77, 0.24, 1);
                break;
            case (11):
                cairo_set_source_rgba(cr, 0.93, 0.76, 0.18, 1);
                break;
            case (12):
                cairo_set_source_rgba(cr, 0.24, 0.23, 0.20, 1);
            default:
                cairo_set_source_rgba(cr, 0, 0, 0, 1);
                break;
            }
            cairo_rectangle(cr, xScreen, yScreen, tileSize, tileSize);
            cairo_fill(cr);

            if (b[y * SIZE + x] > 0)
            {
                char str[8];
                snprintf(str, sizeof(str), "%d", b[y * SIZE + x]);

                int v = (n > 2) ? 1 : 0.8;
                cairo_set_source_rgba(cr, v, v, v, 1);

                cairo_set_font_size(cr, tileSize / 4);

                cairo_text_extents_t extents;
                cairo_text_extents(cr, str,
                                   &extents); // Obtenir les dimensions du texte
                double xText = xScreen + (tileSize - extents.width) / 2
                    - extents.x_bearing;
                double yText = yScreen + (tileSize - extents.height) / 2
                    - extents.y_bearing;

                // Dessiner le texte au centre de la tuile
                cairo_move_to(cr, xText, yText);
                cairo_show_text(cr, str);
            }

            xScreen += tileSize + borderSize;
        }
        yScreen += tileSize + borderSize;
    }
}

void printBoard(int *b)
{
    for (int y = 0; y < SIZE; y++)
    {
        for (int x = 0; x < SIZE; x++)
        {
            g_print("%d ", b[y * SIZE + x]);
        }
        g_print("\n");
    }
}

void freeBoard(int *b)
{
    free(b);
}
