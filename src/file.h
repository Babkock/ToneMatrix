/* ToneMatrix - file.h
 * Copyright (c) 2012 Tanner Babcock */
#ifndef FILE_H
#define FILE_H

#define bool char
#define MAX_SAVE_SLOTS 10

typedef struct {
	int year, month, day;
	int minute, hour;
} metadata;

void				tmFileDialog(bool save);
bool				tmDoesFileExist(const char *path);
void				tmRead(int slot);
void				tmWrite(int slot);

#endif
