#ifndef PLAYER
#define PLAYER

#include "view.h"


void playerReset();
	
void playerMoveLeft();
void playerMoveRight();
void playerTurboOn();
void playerTurboOff();
int playerHitCheck(int hostileShotX, int hostileShotY);
void playerLaunchMissile();
int playerMoveMissile();
void playerExplode();
	
// methods that handle graphic display, from view.c
extern void playerInit();
extern void playerDisplay(int x, int y);
extern void playerClear(int x, int y);
extern void playerMissileInit();
extern void playerMissileDisplay(int x, int y);
extern void playerMissileClear(int x, int y);
extern void playerExplosionDisplay(int x, int y);
extern void bunkersClearElement(int x, int y);

extern void doScoring(int alienType);
	
#endif

