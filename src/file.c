/* ToneMatrix - file.c
 * Copyright (c) 2012 Tanner Babcock */
#include <oslib/oslib.h>
#include <pspiofilemgr_stat.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include "main.h"

void tmFileDialog(bool save) {
	int x;
	unsigned char option = 0;
	bool empty[MAX_SAVE_SLOTS];
	char strings[MAX_SAVE_SLOTS][50];
	char mdate[MAX_SAVE_SLOTS][50];
	char tmp[30];
	
	SceIoStat a;
	typedef struct {
		int year, month, day;
		int minute, hour;
	} metadata;
	metadata songMeta[MAX_SAVE_SLOTS];

	current = 0;
	for (x = 0; x < MAX_SAVE_SLOTS; x++) {
		bzero(tmp, sizeof(tmp));
		sprintf(tmp, "songs/song%d.tms", x);
		sceIoGetstat(tmp, &a);
		songMeta[x].year = a.st_mtime.year;
		songMeta[x].month = a.st_mtime.month;
		songMeta[x].day = a.st_mtime.day;
		songMeta[x].minute = a.st_mtime.minute;
		songMeta[x].hour = a.st_mtime.hour;
	}
	// I have to make a separate struct because accessing sm->tm_mday
	// from the while (!osl_quit) fries the memory stick
	// same reason why there's a bool empty[]

	for (x = 0; x < MAX_SAVE_SLOTS; x++) {
		bzero(tmp, sizeof(tmp));
		sprintf(tmp, "songs/song%d.tms", x);
		empty[x] = tmDoesFileExist(tmp);
	}
	while (!osl_quit) {
		oslStartDrawing();
		oslReadKeys();
		tmDrawGrid();
		oslDrawFillRect(0, 0, 480, 272, RGBA(0, 0, 0, 125));
		if (save)
			oslDrawString(10, 40, "Press X (cross) to save your song in the selected slot.");
		else
			oslDrawString(10, 40, "Press X (cross) to load a song from the selected slot.");
		oslDrawString(10, 50, "Press O (circle) to cancel.");
		for (x = 0; x < MAX_SAVE_SLOTS; x++) {
			bzero(strings[x], sizeof(strings[x]));
			bzero(tmp, sizeof(tmp));
			sprintf(tmp, "song%d.tms", x);
			sprintf(strings[x], "%s %s", (option == x) ? "->" : "  ", (empty[x]) ? "EMPTY" : tmp);
			sprintf(mdate[x], "%d/%d/%d %d:%d UTC", songMeta[x].month, songMeta[x].day, songMeta[x].year, songMeta[x].hour, songMeta[x].minute);
			oslDrawString(10, (70+(x*10)), strings[x]);
			if (!empty[x])
				oslDrawString(200, (70+(x*10)), mdate[x]);
		}
		oslDrawString(10, 190, "Press /\\ (triangle) to delete the selected song slot.");
		if ((osl_keys->pressed.up) && (option > 0))
			option--;
		if ((osl_keys->pressed.down) && (option < (MAX_SAVE_SLOTS-1)))
			option++;
		if (osl_keys->pressed.cross) {
			if (empty[option]) {
				if (save) {
					tmWrite(option);
					break;
				}
			}
			else {
				if (save) {
					if (tmOverwriteWarning(option)) {
						tmWrite(option);
						break;
					}
				}
				else {
					tmRead(option);
					break;
				}
			}
		}
		if (osl_keys->pressed.triangle) {
			if (!empty[option]) {
				if (tmDeleteWarning(option)) {
					bzero(tmp, sizeof(tmp));
					sprintf(tmp, "songs/song%d.tms", option);
					remove(tmp);
					empty[option] = TRUE;
				}
			}
		}
		if (osl_keys->pressed.circle)
			break;
		if (osl_keys->pressed.start)
			break;
		oslEndDrawing();
		oslSyncFrame();
	}
	return;
}

bool tmDoesFileExist(const char *path) {
	FILE *in = fopen(path, "r");
	if (!in) {
		fclose(in);
		return TRUE;
	}
	else {
		fclose(in);
		return FALSE;
	}
}

void tmRead(int slot) {
	int x, y, z;
	char f[25];
	sprintf(f, "songs/song%d.tms", slot);
	FILE *in = fopen(f, "r");
	for (z = 0; z < MAX_GRIDS; z++) {
		for (x = 0; x < MAX_X; x++) {
			for (y = 0; y < MAX_Y; y++)
				fscanf(in, "%c", &data[z].grid[x][y]);
			fseek(in, 4, SEEK_CUR);
		}
		fseek(in, 5, SEEK_CUR);
	}
	fclose(in);
	return;
}

void tmWrite(int slot) {
	int x, y, z;
	char f[25];
	sprintf(f, "songs/song%d.tms", slot);
	FILE *out = fopen(f, "r");
	if (out)
		remove(f);
	fclose(out);
	out = fopen(f, "w");
	for (z = 0; z < MAX_GRIDS; z++) {
		for (x = 0; x < MAX_X; x++) {
			for (y = 0; y < MAX_Y; y++)
				fprintf(out, "%c", data[z].grid[x][y]);
			fprintf(out, "%c%c%c%c", 82, 42, 82, 22);
		}
		fprintf(out, "%c%c%c%c\a", 82, 42, 82, 22);
	}
	fclose(out);
	return;
}
