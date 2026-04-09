// https://rosettacode.org/wiki/Conway%27s_Game_of_Life#C
// Fixed for Z80/Fuzix compiler - with static arrays

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

#define MAX_W 80
#define MAX_H 24

// Global arrays - stored in data segment, not on stack
static bool univ[MAX_H][MAX_W];
static bool new_univ[MAX_H][MAX_W];

void show(int w, int h)
{
    int x, y;

    printf("\033[H");
    for (y = 0; y < h; y++) {
        for (x = 0; x < w; x++) {
            printf(univ[y][x] ? "#" : " ");
        }
        printf("\n");  // Use newline instead of \033[E
    }
    fflush(stdout);
}

void evolve(int w, int h)
{
    int x, y, y1, x1, n, ny, nx;

    memset(new_univ, 0, sizeof(new_univ));

    for (y = 0; y < h; y++) {
        for (x = 0; x < w; x++) {
            n = 0;

            for (y1 = y - 1; y1 <= y + 1; y1++) {
                for (x1 = x - 1; x1 <= x + 1; x1++) {
                    ny = (y1 + h) % h;
                    nx = (x1 + w) % w;
                    if (univ[ny][nx])
                        n++;
                }
            }

            if (univ[y][x])
                n--;

            new_univ[y][x] = (n == 3 || (n == 2 && univ[y][x]));
        }
    }

    for (y = 0; y < h; y++) {
        for (x = 0; x < w; x++) {
            univ[y][x] = new_univ[y][x];
        }
    }
}

void game(int w, int h)
{
    int x, y;

    memset(univ, 0, sizeof(univ));

    for (y = 0; y < h; y++) {
        for (x = 0; x < w; x++) {
            univ[y][x] = (rand() < RAND_MAX / 5) ? 1 : 0;
        }
    }

    printf("\033[?25l");
    printf("\033[2J");

    while (1) {
        show(w, h);
        evolve(w, h);
        usleep(250000);
    }
}

int main(int c, char **v)
{
    int w = 40, h = 24;

    srand(time(NULL));

    if (c > 1) w = atoi(v[1]);
    if (c > 2) h = atoi(v[2]);
    if (w <= 0 || w > MAX_W) w = MAX_W;
    if (h <= 0 || h > MAX_H) h = MAX_H;

    game(w, h);
    return 0;
}
