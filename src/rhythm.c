/* ToneMatrix - rhythm.c
 * Copyright (c) 2011-2012 Tanner Babcock */
#include "main.h"

double tmTempo(int b) {
	return (15000000 / b);
}

int tmBPM(double t) {
	return (15000000 / t);
}

bool tmMuteEmpty(bool m[8]) {
	int x;
	for (x = 0; x < MAX_Y; x++) {
		if (m[x])
			return FALSE;
	}
	return TRUE;
}
