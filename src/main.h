/* ToneMatrix - main.h
 * Copyright (c) 2012 Tanner Babcock */
#ifndef MAIN_H
#define MAIN_H

#include <oslib/oslib.h>
#include <pspmodulemgr.h>

#define VERSION "0.9"
#define bool char
#define tmQuit() oslEndGfx(); oslQuit()
#define tmAbort(err) \
	int s; \
	oslClearScreen(RGBA(0, 0, 0, 255)); \
	for (s = 0; s < 4; s++) { \
		oslStartDrawing(); \
		oslReadKeys(); \
		oslDrawString(10, 10, err); \
		oslEndDrawing(); \
		oslSyncFrame(); \
	} \
	sceKernelDelayThread(2000000); \
	tmQuit()

#define OFFC RGBA(30,30,30,255)		// off
#define ONC RGBA(199,199,199,255)	// on
#define HOFF RGBA(50,50,50,255)		// lit up and off
#define HON RGBA(220,220,220,255)	// lit up and on
#define MOFF RGBA(40,0,0,255)		// off, row muted
#define MON RGBA(199,0,0,255)		// on, row muted
#define MHOFF RGBA(60,0,0,255)		// lit up and off, row muted
#define MHON RGBA(220,0,0,255)		// lit up and on, row muted
#define SOFF RGBA(0,7,40,255)		// off, row soloed
#define SON RGBA(0,8,199,255)		// on, row soloed
#define SHOFF RGBA(0,7,60,255)		// lit up and off, row soloed
#define SHON RGBA(0,8,220,255)		// lit up and on, row soloed

#define x1form ((x*30)-29)
#define y1form ((15+(y*30))-29)
#define x2form ((x*30)-1)
#define y2form ((15+(y*30))-1)

enum { FALSE, TRUE };
enum { OFF, ON, CURSOFF, CURSON };
enum {
	SAVEM,		// Save song
	LOADM,		// Load song
	HELPM,		// Help me
	LOOPM,		// Loop all: on
	TEMPOM,		// Tempo: 120 BPM
	GRIDM,		// Grid: 0
	BREAK,		//
	CUTM,		// Cut grid
	COPYM,		// Copy grid
	PASTEM,		// Paste grid
	CLEARM,		// Clear current grid
	CLEARALLM	// Clear all grids
};
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
	char grid[16][8];
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

void				tmInit(void);
void 				tmDebug(int x, int y, const char *str);
void				tmSoundLoop(void);
void 				tmMainLoop(void);
void 				tmDrawGrid(void);
void 				tmHelp(void);
void 				setUpVirtualFileMenu(void);
unsigned char 		tmMenu(void);
tmGrid 				tmClear(void);
double 				tmTempo(int b);
int 				tmBPM(double t);
void				tmMuteCheck(void);
bool				tmMuteEmpty(bool m[8]);
bool				tmIsGridEmpty(tmGrid g);
void				tmSwitchGrid(int a, int b);
bool				tmClearAllWarning(void);
void				tmFileDialog(bool save);
bool				tmOverwriteWarning(int slot);
bool				tmDeleteWarning(int slot);
bool				tmDoesFileExist(const char *path);
const char *		tmOSK(const char *name);
void				tmRead(int slot);
void				tmWrite(int slot);
void				tmStop(void);
void				tmStart(void);

#endif
