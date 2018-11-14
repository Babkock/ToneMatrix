TARGET = tm
OBJS = draw.o file.o grid.o main.o menu.o misc.o rhythm.o sound.o

CFLAGS = -G4 -Wall -O2
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CFLAGS)

BUILD_PRX = 1

LIBS = -losl -lc -ljpeg -lpng -lz -lpspsdk -lpspctrl -lpspumd -lpsprtc -lpsppower -lpspgu -lpspgum -lpsphprm -lpspaudiolib -lpspaudio -lm

EXTRA_TARGETS = EBOOT.PBP
PSP_EBOOT_TITLE = ToneMatrix 0.93
PSP_EBOOT_ICON = ICON0.PNG

PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak
