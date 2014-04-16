/* ToneMatrix - draw.c
 * Copyright (c) 2012 Tanner Babcock */
#include <oslib/oslib.h>
#include "main.h"

// GOLD
void tmDrawGrid(void) {
	int x, y;
	oslDrawFillRect(0, 15, 480, 255, RGBA(0, 0, 0, 255));
	for (x = 1; x < (MAX_X+1); x++) {
		for (y = 1; y < (MAX_Y+1); y++) {
			if (tmMuteEmpty(mute) || solo == 0) {
				if (data[current].grid[x-1][y-1] == OFF)
					oslDrawFillRect(x1form, y1form, x2form, y2form, (x == col) ? HOFF : OFFC);
				else if (data[current].grid[x-1][y-1] == ON)
					oslDrawFillRect(x1form, y1form, x2form, y2form, (x == col) ? HON : ONC);
				else if (data[current].grid[x-1][y-1] == CURSOFF) {
					oslDrawFillRect(x1form, y1form, x2form, y2form, (x == col) ? HOFF : OFFC);
					oslDrawImageXY(select, x1form, y1form);
				}
				else if (data[current].grid[x-1][y-1] == CURSON) {
					oslDrawFillRect(x1form, y1form, x2form, y2form, (x == col) ? HON : ONC);
					oslDrawImageXY(select, x1form, y1form);
				}
			}
			if (mute[y-1] && solo == 0) {
				if (data[current].grid[x-1][y-1] == OFF)
					oslDrawFillRect(x1form, y1form, x2form, y2form, (x == col) ? MHOFF : MOFF);
				else if (data[current].grid[x-1][y-1] == ON)
					oslDrawFillRect(x1form, y1form, x2form, y2form, (x == col) ? MHON : MON);
				else if (data[current].grid[x-1][y-1] == CURSOFF) {
					oslDrawFillRect(x1form, y1form, x2form, y2form, (x == col) ? MHOFF : MOFF);
					oslDrawImageXY(select, x1form, y1form);
				}
				else if (data[current].grid[x-1][y-1] == CURSON) {
					oslDrawFillRect(x1form, y1form, x2form, y2form, (x == col) ? MHON : MON);
					oslDrawImageXY(select, x1form, y1form);
				}
			}

			if (solo == y && tmMuteEmpty(mute)) {
				if (data[current].grid[x-1][y-1] == OFF)
					oslDrawFillRect(x1form, y1form, x2form, y2form, (x == col) ? SHOFF : SOFF);
				else if (data[current].grid[x-1][y-1] == ON)
					oslDrawFillRect(x1form, y1form, x2form, y2form, (x == col) ? SHON : SON);
				else if (data[current].grid[x-1][y-1] == CURSOFF) {
					oslDrawFillRect(x1form, y1form, x2form, y2form, (x == col) ? SHOFF : SOFF);
					oslDrawImageXY(select, x1form, y1form);
				}
				else if (data[current].grid[x-1][y-1] == CURSON) {
					oslDrawFillRect(x1form, y1form, x2form, y2form, (x == col) ? SHON : SON);
					oslDrawImageXY(select, x1form, y1form);
				}
			}
		}
	}
	return;
}
