CC=gcc
CFLAGS=-O3 -Wall
LIBS=-lncurses

CFILES=globals.c view.c aliens.c player.c nInvaders.c
HFILES=globals.h view.h aliens.h player.h nInvaders.h
OFILES=globals.o view.o aliens.o player.o nInvaders.o
all:		nInvaders

nInvaders: 	$(OFILES) $(HFILES)
		$(CC) $(LDFLAGS) -o$@ $(OFILES) $(LIBS)

.c.o:
		$(CC) -c  -I. $(CFLAGS) $(OPTIONS) $<
clean:
		rm -f nInvaders $(OFILES)
