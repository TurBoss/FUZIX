#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdint.h>
#include <time.h>

#define for_x for (int x = 0; x < w; x++)
#define for_y for (int y = 0; y < h; y++)
#define for_xy for_x for_y

//void show(void *u, int w, int h)
//{
//	bool (*univ)[w] = u;
//	printf("\033[H");
//	for_y {
//		for_x printf(univ[y][x] ? "\033[42m " : "\033[0m ");
//		printf("\033[E");
//	}
//	fflush(stdout);
//}


void show(void *u, int w, int h)
{
	bool (*univ)[w] = u;
	printf("\033[H");
	for_y {
		for_x printf(univ[y][x] ? "@" : " ");
		printf("\033[E");
	}
	fflush(stdout);
}

void evolve(void *u, int w, int h)
{
	bool (*univ)[w] = u;
	bool new[h][w];

	for_y for_x {
		int n = 0;

		for (int y1 = y - 1; y1 <= y + 1; y1++)
			for (int x1 = x - 1; x1 <= x + 1; x1++)
				if (univ[(y1 + h) % h][(x1 + w) % w])
					n++;

		if (univ[y][x]) n--;

		new[y][x] = (n == 3 || (n == 2 && univ[y][x]));
	}

	for_y for_x univ[y][x] = new[y][x];
}

void game(int w, int h)
{
	bool univ[h][w];

	for_xy univ[y][x] = rand() < RAND_MAX / 5 ? 1 : 0;

	printf("\033[?25l");
	printf("\033[2J");
	printf("\033[38;5;42m ");
	printf("\033[48;5;00m ");

	while (1) {
		show(univ, w, h);

		evolve(univ, w, h);

		usleep(250000);
	}
}

int main(int c, char **v)
{
	time_t t;

	/* Intializes random number generator */
	srand((unsigned) time(&t));

	int w = 0, h = 0;

	if (c > 1) w = atoi(v[1]);
	if (c > 2) h = atoi(v[2]);

	if (w <= 0) w = 80;
	if (h <= 0) h = 28;

	game(w, h);
}
