/* ToneMatrix - misc.c
 * Copyright (c) 2012 Tanner Babcock */
#include <oslib/oslib.h>
#include <pspkernel.h>
#include <psputils.h>
#include <stdio.h>
#include <string.h>
#include "main.h"

void tmInit(void) {
	oslInit(0);
	oslInitGfx(OSL_PF_8888, 1);
	oslInitConsole();
	oslInitAudio();
	int x, y;
	char tmp[25];
	rflag = FALSE;
	for (x = 0; x < 3; x++) {
		oslStartDrawing();
		oslReadKeys();
		if (osl_keys->pressed.R)
			rflag = TRUE;
		oslEndDrawing();
		oslSyncFrame();
	}
	if (rflag)
		tmDebug(10, 10, "Debug mode activated");
	for (x = 0; x < MAX_Y; x++) {
		bzero(tmp, sizeof(tmp));
		sprintf(tmp, "sounds/tone%d.wav", x);
		sound[x] = oslLoadSoundFile(tmp, OSL_FMT_NONE);
		if (!sound[x]) {
			bzero(tmp, sizeof(tmp));
			sprintf(tmp, "ERROR: sound file %d missing", x);
			tmDebug(10, 10, tmp);
			sceKernelDelayThread(2000000);
			tmQuit();
		}
	}
	// setUpVirtualFileMenu();
	select = oslLoadImageFilePNG("select.png", OSL_IN_RAM, OSL_PF_5551);
	oslSetBkColor(RGBA(0, 0, 0, 0));
	current = 0;
	tmClear(&clipboard);
	for (y = 0; y < MAX_GRIDS; y++)
		tmClear(&data[y]);
	quit = FALSE;
	col = 0;
	menuoption = 0;
	tempo = 125000;
	bpm = tmBPM(tempo);
	isplaying = TRUE;
	loopall = TRUE;
	soundloop = sceKernelCreateThread("Sound Loop", (SceKernelThreadEntry)tmSoundLoop, 0x11, (256 * 1024), PSP_THREAD_ATTR_USER, NULL);
	oslClearScreen(RGBA(0, 0, 0, 255));
	return;
}

void tmDebug(int x, int y, const char *str) {
	int z;
	for (z = 0; z != 3; z++) {
		oslStartDrawing();
		oslDrawString(x, y, str);
		oslEndDrawing();
		oslSyncFrame();
	}
	return;
}

/* void setUpVirtualFileMenu(void) {
	OSL_VIRTUALFILENAME ram_files[] = {{"ram:/select.png", (void*)select_data, sizeof(select_data), &VF_MEMORY}};
	oslAddVirtualFileList(ram_files, oslNumberof(ram_files));
} */
