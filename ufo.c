#include "ufo.h"
#include "aliens.h"
#include "nInvaders.h"

static int fShowUfo = 0;

/**
 * initialize ufo attributes
 */
void ufoReset()
{
	ufoClear(u.posX, u.posY);	// clear old position of player

	fShowUfo = 0;                   // do not show ufo
	u.posY = UFOPOSY;	        // set vertical Position
	u.posX = SCREENWIDTH - UFOWIDTH;// set horizontal Position
}

/**
 * move ufo horizontally to position posX
 */
static void ufoMove(int posX)
{
	ufoClear(u.posX, u.posY);   // clear sprite
	u.posX = posX;
	ufoRefresh();
	ufoDisplay(u.posX, u.posY);
}


/**
 * move ufo and check if it reached the left screen border
 */
void ufoMoveLeft()
{
	// check if space between ufo and screen border is big enough 
	if (u.posX > 1) {
		// desired movement is possible
		ufoMove(u.posX - 1);
	} else {
		ufoReset();
	}
}

/**
 * check if the first screen line is free for the ufo and
 * display it randomly
 */
int ufoShowUfo()
{
	if (a.posY > 0 && fShowUfo == 0) { // aliens one line down
		if ((random() % 200) == 0) {
			fShowUfo = 1;
		}
	}

	return fShowUfo;
}

/**
 * check if ufo was hit by player and delete it from screen
 */
int ufoHitCheck(int shotX, int shotY)
{
	int fUfoWasHit = 0;
	
	// if shot reached vertikal position of ufo
	if (shotY == UFOPOSY) {
		// if shot hits ufo
		if (shotX >= u.posX && shotX <= u.posX + UFOWIDTH -1) {
			ufoReset();
			fUfoWasHit = 1;
		}
	}
	
	return fUfoWasHit;
}
