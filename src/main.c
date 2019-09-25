/* ToneMatrix - main.c
 * Copyright (c) 2012 Tanner Babcock */
#include <oslib/oslib.h>
#include <pspkernel.h>
#include <psputils.h>
#include "main.h"
#include "menu.h"
#define c data[current]
PSP_MODULE_INFO("ToneMatrix", 0, 1, 1);
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER | THREAD_ATTR_VFPU);
PSP_HEAP_SIZE_KB(2048);

void tmMainLoop(void) {
	int x = 0, y = 0, q, m;
	unsigned char tmpcurrent = current;
	clock_t start, cu;
	start = sceKernelLibcClock();
	oslClearScreen(RGBA(0, 0, 0, 255));
	tmStart();
	while (!osl_quit && !quit) {
		oslStartDrawing();
		oslReadKeys();
		oslClearScreen(RGBA(0, 0, 0, 255));
		cu = sceKernelLibcClock();
		tmDrawGrid();
		tmSwitchGrid(&x, &y);
		if (current != tmpcurrent) {
			if (c.grid[x][y] == ON)
				c.grid[x][y] = CURSON;
			if (c.grid[x][y] == OFF)
				c.grid[x][y] = CURSOFF;
			tmpcurrent = current;
		}
		/* if ((d = start - cu) <= 1250000)
			oslDrawString(0, 300, msg); */
		// grid[x][y] is where the cursor is
		if (c.grid[x][y] == ON)
			c.grid[x][y] = CURSON;
		else if (c.grid[x][y] == OFF)
			c.grid[x][y] = CURSOFF;
		if (x > MAX_X || x < 0)
			x = 0;
		if (y > MAX_Y || y < 0)
			y = 0;
		if (osl_keys->pressed.up) {
			if (y > 0) {
				if (c.grid[x][y] == CURSON)
					c.grid[x][y] = ON;
				else if (c.grid[x][y] == CURSOFF)
					c.grid[x][y] = OFF;
				if (c.grid[x][y-1] == OFF)	// fix for the "trail" bug
					c.grid[x][y-1] = CURSOFF;
				else if (c.grid[x][y-1] == ON)
					c.grid[x][y-1] = CURSON;
				y--;
			}
		}
		if (osl_keys->pressed.down) {
			if (y < (MAX_Y-1)) {
				if (c.grid[x][y] == CURSON)
					c.grid[x][y] = ON;
				else if (c.grid[x][y] == CURSOFF)
					c.grid[x][y] = OFF;
				if (c.grid[x][y+1] == ON)
					c.grid[x][y+1] = CURSON;
				else if (c.grid[x][y+1] == OFF)
					c.grid[x][y+1] = CURSOFF;
				y++;
			}
		}
		if (osl_keys->pressed.left) {
			if (x > 0) {
				if (c.grid[x][y] == CURSON)
					c.grid[x][y] = ON;
				else if (c.grid[x][y] == CURSOFF)
					c.grid[x][y] = OFF;
				if (c.grid[x-1][y] == ON)
					c.grid[x-1][y] = CURSON;
				else if (c.grid[x-1][y] == OFF)
					c.grid[x-1][y] = CURSOFF;
				x--;
			}
		}
		if (osl_keys->pressed.right) {
			if (x < (MAX_X-1)) {
				if (c.grid[x][y] == CURSON)
					c.grid[x][y] = ON;
				else if (c.grid[x][y] == CURSOFF)
					c.grid[x][y] = OFF;
				if (c.grid[x+1][y] == ON)
					c.grid[x+1][y] = CURSON;
				else if (c.grid[x+1][y] == OFF)
					c.grid[x+1][y] = CURSOFF;
				x++;
			}
		}
		if (osl_keys->pressed.cross) {
			if (c.grid[x][y] == CURSOFF)
				c.grid[x][y] = CURSON;
			else if (c.grid[x][y] == CURSON)
				c.grid[x][y] = CURSOFF;
		}
		if (osl_keys->pressed.circle) {
			if (isplaying)
				tmStop();
			else if (!isplaying)
				tmStart();
		}
		if (osl_keys->pressed.triangle) {
			if (solo != 0)
				solo = 0;
			else if (tmMuteEmpty(mute))
				solo = (y +1);
			else {
				for (m = 0; m < 8; m++)
					mute[m] = FALSE;
				solo = (y +1);
			}
		}
		if (osl_keys->pressed.square) {
			if (solo != 0)
				solo = 0;
			mute[y] = (mute[y]) ? FALSE : TRUE;
		}

		if (osl_keys->pressed.R) {
			if (current < 11)
				current++;
		}
		if (osl_keys->pressed.L) {
			if (current > 0)
				current--;
		}
		if (osl_keys->pressed.start) {
			switch (tmMenu()) {
				case SAVEM:
					tmFileDialog(TRUE);
					break;
				case LOADM:
					tmFileDialog(FALSE);
					break;
				case HELPM:
					tmHelp();
					break;
				case CLEARM:
					tmClear(&data[current]);
					break;
				case CLEARALLM:
					if (tmClearAllWarning()) {
						for (q = 0; q < MAX_GRIDS; q++)
							tmClear(&data[q]);
						current = 0;
						x = 0, y = 0;
					}
					break;
			}
		}
		if (osl_keys->pressed.select)
			tmHelp();
		oslEndDrawing();
		oslSyncFrame();
	}
	quit = TRUE;
	return;
}

int main(void) {
	tmInit();
	tmMainLoop();
	tmQuit();
	return 0;
}
