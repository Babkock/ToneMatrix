# ToneMatrix 0.93

## This repository has moved to [GitLab](https://gitlab.com/Babkock/ToneMatrix).

![test](https://raw.githubusercontent.com/Babkock/ToneMatrix/master/screen5.png)

Hello, I am Tanner Babcock. This is a restoration, out of several in a series, of one of my PSP homebrew programs. *ToneMatrix* version 0.92 was completed May 2012. The code was all written by me.

## Original Readme

ToneMatrix is a 16-step drum machine. The Y (vertical) axis represents eight different sounds, and more than one can be played at a time. The X (horizontal) axis represents one 4/4 measure in sixteenth-notes.

Select a node on the grid with the **D-pad** and the **X** button, and that sound will be played in time. Press **O** to stop/resume playing. Press **[] (square)** to mute the row the cursor is on. Press **/\ (triangle)** to mute every row except the row the cursor is on. You can mute more than one row at once.

Press **START** to use the menu, and use the **D-pad** to select a menu item or change a value (like the tempo), and **X (cross)** to confirm your choice. Press **SELECT** for help.

You can play up to twelve measures in a row by using the **R and L** triggers, or by switching the "grid" value in the **START** mneu. If "loop all" is on, then the measures will play one after another. If it is off, it will only repeat one measure. It is recommended that you stop playback before editing another grid.

## How PSP Homebrew is Built

When I wrote PSP software as a teenager, I used a Windows build of the [universally-known PSP SDK](https://github.com/pspdev/pspsdk), through Wine, on my Mac. The build process revolves around GNU Make, but there are many extra steps. Every PSP binary is named `EBOOT.PBP` ("PSP binary package"). The actual machine code is only one out of up to eight elements.

* `PARAM.SFO` - Metadata about the program, contains its title, version, language, and parental rating - the program will not be recognized at all if this is not present
* `DATA.PSP` - The binary itself, usually comes as a \*.elf or a \*.prx (in typical Executable and Linkable format), technically has no filename until it's dumped from the package

A package really only needs these first two, the six remaining elements are totally optional.

* `DATA.PSAR` - Compressed archive for system software updates or video game updates
* `ICON0.PNG` - The icon of the game or app, appears in the vertical list next to the others when in the XMB
* `ICON1.PMF` - A short animation that takes the place of `ICON0.PNG` when focused - no audio included (.PMF is a native video format on PSP, .PAM is the PS3 version)
* `PIC0.PNG` - A caption or description image, appears on top of `PIC1.PNG` and after a short delay
* `PIC1.PNG` - The background image that appears behind the XMB icons when focused
* `SND0.AC3` - Sound that plays - often theme music for a game or a movie

One specifies which real files they want compiled into their EBOOT via the [Makefile](https://github.com/Babkock/ToneMatrix/blob/master/src/Makefile). The PARAM.SFO is generated by **mksfo**, the PRX is built from **psp-prxgen**, and the PBP is packaged with **pack-pbp** (it can be unpackaged with **unpack-pbp**).

## Installation

If you have custom firmware or a homebrew-enabled PSP, place the **"unsigned"** folder into the `/PSP/GAME` folder on your Memory Stick. If you have official firmware on your PSP (or if you have a PSPgo), place the **"signed"** folder into the `/PSP/GAME` folder on your Memory Stick.

## License

This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 2 of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with this program; if not, visit [http://www.gnu.org/licenses/gpl-2.0.txt](http://www.gnu.org/licenses/gpl-2.0.txt)

If you want to redistribute any modifications you make to the program, please credit yourself in the modified source file(s) under my name as,

```
Copyright (c) <year> <your name here>
```

Feel free to contact me at [babkock@gmail.com](mailto:babkock@gmail.com) if you have any questions or concerns. Thanks for playing :)
