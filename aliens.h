
#include "view.h"

#ifndef ALIENS
#define ALIENS

typedef struct Aliens Aliens;
	
struct Aliens {
	int posX;	  // horizontal position of aliens
	int posY;	  // vertical position of aliens
	int right;
	int left;
	int bottom;
	int speed;	  // 0: no movement; 1: one per turn; etc.
};
	
Aliens aliens;
	

int shootme_counter;	
int shipnum;	

#define ALIENS_MAX_NUMBER_X 10
#define ALIENS_MAX_NUMBER_Y 5	
#define ALIENS_MAX_MISSILES 50	

// todo: move to structure
int lowest_ship[ALIENS_MAX_NUMBER_X];
int alienshotx[ALIENS_MAX_MISSILES];
int alienshoty[ALIENS_MAX_MISSILES];
int alienshotnum;
int alienBlock[ALIENS_MAX_NUMBER_Y][ALIENS_MAX_NUMBER_X];

int bunker[BUNKERHEIGHT][BUNKERWIDTH + 1];	


void aliensReset();
void bunkersReset();	
int aliensMove();
int aliensMissileMove();
void render();
int aliensHitCheck(int shotx, int shoty);
int bunkersHitCheck(int shotx, int shoty);

	
// methods that handle graphic display, from view.c
extern void aliensDisplay(int x, int y, int wid, int hgt);
extern void aliensClear(int x, int y, int wid, int hgt);
extern void aliensRefresh(int level, int *pAliens);
extern void aliensMissileDisplay(int x, int y);
extern void aliensMissileClear(int x, int y);
extern void bunkersClearElement(int x, int y);
extern void bunkersClear();
extern void bunkersRefresh();
	
#endif
