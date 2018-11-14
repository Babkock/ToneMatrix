/* ToneMatrix - draw.h
 * Copyright (c) 2011-2012 Tanner Babcock */
#ifndef DRAW_H
#define DRAW_H

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

#endif
