#include <ncurses.h>
#include <unistd.h>
#include <signal.h>

#ifndef VIEW
#define VIEW

#include "globals.h"

#define SCREENHEIGHT 24
#define SCREENWIDTH 80	
	
#define PLAYERWIDTH 5
#define PLAYERPOSY (SCREENHEIGHT-2)

#define BUNKERWIDTH 80
#define BUNKERHEIGHT 4
#define BUNKERX 0
#define BUNKERY (SCREENHEIGHT-8)
	
#define ALIENS_MAX_NUMBER_X 10
#define ALIENS_MAX_NUMBER_Y 5	
#define ALIENS_MAX_MISSILES 50

#define UFOWIDTH 5
#define UFOPOSY 0

int alienBlock[ALIENS_MAX_NUMBER_Y][ALIENS_MAX_NUMBER_X];	
	
void graphicEngineInit();
	
void playerDisplay(int x, int y);
void playerClear(int x, int y);
void playerMissileDisplay(int x, int y);
void playerMissileClear(int x, int y);
void playerExplode(int x, int y);
void aliensDisplay(int x, int y, int wid, int hgt);
void aliensClear(int x, int y, int wid, int hgt);
void aliensRefresh(int level);
void aliensMissileDisplay(int x, int y);
void aliensMissileClear(int x, int y);
void bunkersDisplay(int *pBunker);
void bunkersClear();
void bunkersClearElement(int x, int y);
void ufoDisplay(int x, int y);
void ufoRefresh();
void ufoClear(int x, int y);
void gameOverDisplay(int x, int y);

void statusDisplay(int level, int score, int lives);	
void refreshScreen();

#endif
