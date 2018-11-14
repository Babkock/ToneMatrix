/* ToneMatrix - grid.c
 * Copyright (c) 2011-2012 Tanner Babcock */
#include <oslib/oslib.h>
#include <stdlib.h>
#include "main.h"

void tmClear(tmGrid *g) {
	int y, z;
	for (y = 0; y < MAX_X; y++) {
		for (z = 0; z < MAX_Y; z++)
			g->grid[y][z] = OFF;
	}
	g->grid[0][0] = CURSOFF;
	return;
}

bool tmIsGridEmpty(tmGrid *g) {
	int x, y;
	for (x = 0; x < MAX_Y; x++) {
		for (y = 0; y < MAX_X; y++) {
			if (g->grid[x][y] != OFF && g->grid[x][y] != CURSOFF)
				return FALSE;
		}
	}
	return TRUE;
}

void tmSwitchGrid(int *a, int *b) {
	// call from tmMainloop with tmSwitchGrid(&x, &y)
	int x, y;
	for (x = 0; x < MAX_X; x++) {
		for (y = 0; y < MAX_Y; y++) {
			if (data[current].grid[x][y] == CURSON)
				data[current].grid[x][y] = ON;
			if (data[current].grid[x][y] == CURSOFF)
				data[current].grid[x][y] = OFF;	
		}
	}
	return;
}
