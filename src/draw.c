/* ToneMatrix - draw.c
 * Copyright (c) 2012 Tanner Babcock */
#include <oslib/oslib.h>
#include "main.h"
#include "draw.h"

int tmGetColor(char gridval, int x, int y) {
	int c = 0;
	if (tmMuteEmpty(mute) || solo == 0) {
		switch (gridval) {
			case OFF: case CURSOFF: c = (x == col) ? HOFF : OFFC; break;
			case ON: case CURSON: c = (x == col) ? HON : ONC; break;
		}
	}
	if (mute[y-1] && solo == 0) {
		switch (gridval) {
			case OFF: case CURSOFF: c = (x == col) ? MHOFF : MOFF; break;
			case ON: case CURSON: c = (x == col) ? MHON : MON; break;
		}
	}
	if (solo == y && tmMuteEmpty(mute)) {
		switch (gridval) {
			case OFF: case CURSOFF: c = (x == col) ? SHOFF : SOFF; break;
			case ON: case CURSON: c = (x == col) ? SHON : SON; break;
		}
	}
	return c;
}

// GOLD
void tmDrawGrid(void) {
	int x, y;
	oslDrawFillRect(0, 15, 480, 255, RGBA(0, 0, 0, 255));
	for (x = 1; x < (MAX_X+1); x++) {
		for (y = 1; y < (MAX_Y+1); y++) {
			oslDrawFillRect(x1form, y1form, x2form, y2form, tmGetColor(data[current].grid[x-1][y-1], x, y));
			if (data[current].grid[x-1][y-1] == CURSON || data[current].grid[x-1][y-1] == CURSOFF)
				oslDrawImageXY(select, x1form, y1form);
		}
	}
}
