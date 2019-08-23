/* ToneMatrix - menu.c
 * Copyright (c) 2012 Tanner Babcock */
#include <oslib/oslib.h>
#include "main.h"
#include "menu.h"

unsigned char tmMenu(void) {
	int x;
	char mstrings[MAX_MENU_ITEMS][40];
	while (!osl_quit) {
		oslStartDrawing();
		oslReadKeys();
		tmDrawGrid();
		oslDrawFillRect(0, 0, 480, 272, RGBA(0, 0, 0, 125));
		tempo = tmTempo(bpm);
		bpm = tmBPM(tempo);
		for (x = 0; x < MAX_MENU_ITEMS; x++) {
			bzero(mstrings[x], sizeof(mstrings[x]));
			switch (x) {
				case SAVEM:
					sprintf(mstrings[x], "%s Save song", (menuoption == x) ? "->" : "  ");
					break;
				case LOADM:
					sprintf(mstrings[x], "%s Load song", (menuoption == x) ? "->" : "  ");
					break;
				case HELPM:
					sprintf(mstrings[x], "%s Help me", (menuoption == x) ? "->" : "  ");
					break;
				case LOOPM:
					sprintf(mstrings[x], "%s Loop all: %s", (menuoption == x) ? "->" : "  ", (loopall) ? "on" : "off");
					break;
				case TEMPOM:
					sprintf(mstrings[x], "%s Tempo: %d BPM", (menuoption == x) ? "->" : "  ", tmBPM(tempo));
					break;
				case GRIDM:
					sprintf(mstrings[x], "%s Grid: %d", (menuoption == x) ? "->" : "  ", (current+1));
					break;
				case CUTM:
					sprintf(mstrings[x], "%s Cut grid", (menuoption == x) ? "->" : "  ");
					break;
				case COPYM:
					sprintf(mstrings[x], "%s Copy grid", (menuoption == x) ? "->" : "  ");
					break;
				case PASTEM:
					if (tmIsGridEmpty(&clipboard))
						oslSetTextColor(RGBA(255,0,0,255));
					sprintf(mstrings[x], "%s Paste grid", (menuoption == x) ? "->" : "  ");
					break;
				case CLEARM:
					sprintf(mstrings[x], "%s Clear grid", (menuoption == x) ? "->" : "  ");
					break;
				case CLEARALLM:
					sprintf(mstrings[x], "%s Clear all grids", (menuoption == x) ? "->" : "  ");
					break;
			}
			oslDrawString(10, (60+(x*10)), mstrings[x]);
			oslSetTextColor(RGBA(255,255,255,255));
		}
		if ((osl_keys->pressed.up) && (menuoption > 0)) {
			menuoption--;
			if (menuoption == BREAK)
				menuoption--;
		}
		if ((osl_keys->pressed.down) && (menuoption < (MAX_MENU_ITEMS-1))) {
			menuoption++;
			if (menuoption == BREAK)
				menuoption++;
		}
		if (osl_keys->pressed.left) {
			switch (menuoption) {
				case GRIDM:
					if (current > 0)
						current--;
					break;
				case LOOPM:
					loopall = (loopall) ? FALSE : TRUE;
					break;
				case TEMPOM:
					if (bpm > MIN_BPM)
						bpm -= 5;
					tempo = tmTempo(bpm);
					break;
			}
		}
		if (osl_keys->pressed.right) {
			switch (menuoption) {
				case GRIDM:
					if (current < (MAX_GRIDS-1))
						current++;
					break;
				case LOOPM:
					loopall = (loopall) ? FALSE : TRUE;
					break;
				case TEMPOM:
					if (bpm < MAX_BPM)
						bpm += 5;
					tempo = tmTempo(bpm);
					break;
			}
		}
		if (osl_keys->pressed.cross) {
			if ((menuoption != LOOPM) && (menuoption != TEMPOM) && (menuoption != GRIDM) &&
				(menuoption != CUTM) && (menuoption != COPYM) && (menuoption != PASTEM))
				return menuoption;
			else {
				switch (menuoption) {
					case CUTM:
						tmClear(&clipboard);
						clipboard = data[current];
						tmClear(&data[current]);
						break;
					case COPYM:
						tmClear(&clipboard);
						clipboard = data[current];
						break;
					case PASTEM:
						if (!tmIsGridEmpty(&clipboard)) {
							tmClear(&data[current]);
							data[current] = clipboard;
						}
						break;
				}
			}
		}
		if (osl_keys->pressed.start)
			break;
		oslEndDrawing();
		oslSyncFrame();
	}
	return 69;
}

void tmHelp(void) {
	oslClearScreen(RGBA(0, 0, 0, 255));
	while (!osl_quit) {
		oslStartDrawing();
		oslReadKeys();
		tmDrawGrid();
		oslDrawFillRect(0, 0, 480, 272, RGBA(0, 0, 0, 125));
		oslDrawString(1, 10, "ToneMatrix is a 16-step drum machine. The X axis represents one");
		oslDrawString(1, 20, "4/4 measure in sixteenth notes, and the Y axis represents eight");
		oslDrawString(1, 30, "different sounds. Select a node on the grid with the D-pad and the");
		oslDrawString(1, 40, "sound will be played in time.");
		oslDrawString(1, 60, "Press O (circle) to stop or resume playing. Press [] (square) to");
		oslDrawString(1, 70, "mute the row the cursor is on. Press /\\ (triangle) to mute every");
		oslDrawString(1, 80, "row except the row the cursor is on. You can mute more than one row");
		oslDrawString(1, 90, "at once.");
		oslDrawString(1, 110, "Press START to use the menu, and use the D-pad to select a menu");
		oslDrawString(1, 120, "item or change a value (like the tempo), and X (cross) to confirm");
		oslDrawString(1, 130, "to confirm your choice.");
		oslDrawString(1, 150, "You can play up to sixteen measures in a row by using the R and L");
		oslDrawString(1, 160, "triggers, or by switching the \"grid\" value in the START menu.");
		oslDrawString(1, 170, "If \"loop all\" is on, then the measures will play one after");
		oslDrawString(1, 180, "another. If it is off, it will only repeat one measure. It is");
		oslDrawString(1, 190, "recommended that you stop playback before editing another grid.");
		oslDrawString(1, 210, "Press SELECT to hide this screen.");
		if (osl_keys->pressed.select)
			break;
		oslEndDrawing();
		oslSyncFrame();
	}
}

bool tmClearAllWarning(void) {
	oslClearScreen(RGBA(0, 0, 0, 255));
	bool x = FALSE;
	while (!osl_quit) {
		oslStartDrawing();
		oslReadKeys();
		tmDrawGrid();
		oslDrawFillRect(0, 0, 480, 272, RGBA(0, 0, 0, 125));
		oslSetTextColor(RGBA(255,0,0,255));
		oslDrawString(200, 50, "WARNING:");
		oslSetTextColor(RGBA(255,255,255,255));
		oslDrawString(3, 70, "Are you sure you want to clear all grids? This cannot be undone.");
		oslDrawString(13, 80, "Press X to clear all grids, or press O to cancel.");
		if (osl_keys->pressed.cross) {
			x = TRUE;
			break;
		}
		if (osl_keys->pressed.circle)
			break;
		oslEndDrawing();
		oslSyncFrame();
	}
	return x;
}

bool tmOverwriteWarning(int slot) {
	bool x = FALSE;
	char msg[50];
	sprintf(msg, "Are you sure you want to overwrite song%d.tms ?", slot);
	while (!osl_quit) {
		oslStartDrawing();
		oslReadKeys();
		tmDrawGrid();
		oslDrawFillRect(0, 0, 480, 272, RGBA(0, 0, 0, 125));
		oslDrawString(13, 70, msg);
		oslDrawString(100, 90, "X - Yes");
		oslDrawString(100, 100, "O - No");
		if (osl_keys->pressed.cross) {
			x = TRUE;
			break;
		}
		if (osl_keys->pressed.circle)
			break;
		oslEndDrawing();
		oslSyncFrame();
	}
	return x;
}

bool tmDeleteWarning(int slot) {
	bool x = FALSE;
	char msg[50];
	sprintf(msg, "Are you sure you want to delete song%d.tms ?", slot);
	while (!osl_quit) {
		oslStartDrawing();
		oslReadKeys();
		tmDrawGrid();
		oslDrawFillRect(0, 0, 480, 272, RGBA(0, 0, 0, 125));
		oslDrawString(13, 70, msg);
		oslDrawString(100, 90, "X - Yes");
		oslDrawString(100, 100, "O - No");
		if (osl_keys->pressed.cross) {
			x = TRUE;
			break;
		}
		if (osl_keys->pressed.circle)
			break;
		oslEndDrawing();
		oslSyncFrame();
	}
	return x;
}
