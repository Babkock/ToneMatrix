/* ToneMatrix - main.h
 * Copyright (c) 2011-2012 Tanner Babcock */
#ifndef MAIN_H
#define MAIN_H

#include <oslib/oslib.h>
#include <pspmodulemgr.h>

#define VERSION "0.93"
#define bool char
#define tmQuit() oslEndGfx(); oslQuit()
#define tmAbort(err) \
	oslClearScreen(RGBA(0, 0, 0, 255)); \
	oslStartDrawing(); \
	oslReadKeys(); \
	oslDrawString(10, 10, err); \
	oslEndDrawing(); \
	oslSyncFrame();\
	sceKernelDelayThread(2000000); \
	tmQuit()

enum { FALSE, TRUE };
enum { OFF, ON, CURSOFF, CURSON };
enum {
	MAX_MENU_ITEMS = 12,
	MAX_GRIDS = 16,
	MAX_X = 16,
	MAX_Y = 8,
	MAX_BPM = 250,
	MIN_BPM = 60,
	MAX_SAVE_SLOTS = 10
};

typedef struct {
	char grid[MAX_X][MAX_Y];
} tmGrid;

int					bpm;
unsigned char		col, solo;
unsigned char		menuoption, current;
char				msg[30];
double 				tempo;
bool 				mute[MAX_Y];
bool 				quit, isplaying, loopall, rflag;
tmGrid				data[MAX_GRIDS], clipboard;
SceUID 				soundloop;
OSL_SOUND			*sound[MAX_Y];
OSL_IMAGE			*select;

// draw.c
int					tmGetColor(char gridval, int x, int y);
void 				tmDrawGrid(void);

// file.c
void				tmFileDialog(bool save);
bool				tmDoesFileExist(const char *path);
void				tmRead(int slot);
void				tmWrite(int slot);

// grid.c
void				tmClear(tmGrid *g);
bool				tmIsGridEmpty(tmGrid *g);
void				tmSwitchGrid(int *a, int *b);

// main.c
void 				tmMainLoop(void);

// menu.c
unsigned char 		tmMenu(void);
void 				tmHelp(void);
bool				tmClearAllWarning(void);
bool				tmOverwriteWarning(int slot);
bool				tmDeleteWarning(int slot);

// misc.c
void				tmInit(void);
void 				tmDebug(int x, int y, const char *str);
void 				setUpVirtualFileMenu(void);

// rhythm.c
double 				tmTempo(int b);
int 				tmBPM(double t);
bool				tmMuteEmpty(bool m[8]);

// sound.c
void				tmSoundLoop(void);
void				tmStop(void);
void				tmStart(void);

#endif
