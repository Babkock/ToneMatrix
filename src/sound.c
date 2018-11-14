/* ToneMatrix - sound.c
 * Copyright (c) 2012 Tanner Babcock */
#include <oslib/oslib.h>
#include <pspkernel.h>
#include <pspthreadman.h>
#include "main.h"

void tmSoundLoop(void) {
	int x, y;
	bpm = tmBPM(tempo);
	tempo = tmTempo(bpm);
	while (!quit) {
		for (x = 0; x < MAX_X; x++) {
			col = (x+1);
			for (y = 0; y < 8; y++) {
				if (data[current].grid[x][y] == ON || data[current].grid[x][y] == CURSON) {
					if ((solo != 0 && solo == (y +1)) || ((solo == 0) && (!mute[y])))
						oslPlaySound(sound[y], y);
				}
			}
			sceKernelDelayThread(tmTempo(bpm));
		}
		if (rflag) {
			if (loopall)
				current = (!tmIsGridEmpty(&data[current+1])) ? (current+1) : 0;
		}
		else {
			if (loopall)
				current = ((!tmIsGridEmpty(&data[current+1])) && (current < MAX_GRIDS)) ? (current+1) : 0;
		}
	}
	sceKernelExitDeleteThread(0);
	return;
}

void tmStop(void) {
	isplaying = FALSE;
	col = 0;
	sceKernelTerminateThread(soundloop);
	return;
}

void tmStart(void) {
	isplaying = TRUE;
	sceKernelStartThread(soundloop, 0, NULL);
	return;
}
