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
	

	int alienBlock[ALIENS_MAX_NUMBER_Y][ALIENS_MAX_NUMBER_X];	

	
	extern void graphicEngineInit();
	
	extern void playerDisplay(int x, int y);
	extern void playerClear(int x, int y);
	extern void playerMissileDisplay(int x, int y);
	extern void playerMissileClear(int x, int y);
	extern void playerExplode(int x, int y);
	extern void aliensDisplay(int x, int y, int wid, int hgt);
	extern void aliensClear(int x, int y, int wid, int hgt);
	extern void aliensRefresh(int level);
	extern void aliensMissileDisplay(int x, int y);
	extern void aliensMissileClear(int x, int y);
	extern void bunkersDisplay(int *pBunker);
	extern void bunkersClear();
	extern void bunkersClearElement(int x, int y);
	extern void gameOverDisplay(int x, int y);

	extern void statusDisplay(int level, int score, int lives);	
	extern void refreshScreen();
#endif
