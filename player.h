#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <unistd.h>


#ifndef PLAYER
#define PLAYER

#include "view.h"

struct structPlayer {
	int posX;	  // horizontal position of player
	int posY;	  // vertical position of player
	int speed;	  // 0: no movement; 1: one per turn; etc.
	int missileFired; // 0: missile not running; 1: missile running
	int missileX;	  // horizontal position of missile
	int missileY;	  // vertical position of missile
	int lives;	  // number of lives
};
	
struct structPlayer p;
	
void playerReset();
	
void playerMoveLeft();
void playerMoveRight();
void playerTurboOn();
void playerTurboOff();
int playerHitCheck(int hostileShotX, int hostileShotY);
void playerLaunchMissile();
int playerMoveMissile();
	
// methods that handle graphic display, from view.c
extern void playerInit();
extern void playerDisplay(int x, int y);
extern void playerClear(int x, int y);
extern void playerMissileInit();
extern void playerMissileDisplay(int x, int y);
extern void playerMissileClear(int x, int y);
extern void playerExplode(int x, int y);
extern void bunkersClearElement(int x, int y);

extern void doScoring(int alienType);
	
#endif

