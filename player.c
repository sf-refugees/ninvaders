#include "player.h"
#include "aliens.h"
#include "ufo.h"
#include "nInvaders.h"

struct structPlayer {
	int posX;	  // horizontal position of player
	int posY;	  // vertical position of player
	int speed;	  // 0: no movement; 1: one per turn; etc.
	int missileFired; // 0: missile not running; 1: missile running
	int missileX;	  // horizontal position of missile
	int missileY;	  // vertical position of missile
} p;
	
//struct structPlayer p;

/**
 * initialize player attributes
 */
void playerReset()
{
	// if missile was fired clear that position
	if (p.missileFired == 1) {	
		playerMissileClear(p.missileX, p.missileY);
	}
	
	playerClear(p.posX, p.posY);	// clear old position of player
	
	p.posY = PLAYERPOSY;	// set vertical Position
	p.posX = 0;		// set horizontal Position
	p.speed = 1;
	p.missileFired = 0;
	p.missileX=0; 
	p.missileY=0; 

	playerDisplay(p.posX, p.posY);	// display new position of player
}


/**
 * move player horizontally to position newPosX
 */
static void playerMove(int newPosX)
{
	playerClear(p.posX, p.posY);	 // clear sprite
	p.posX = newPosX;	 // make movement
  	playerDisplay(p.posX, p.posY); // display sprite
}


/**
 * move player left
 */
void playerMoveLeft()
{
	// check if space between player and border of screen is big enough 
	if (p.posX > 0 + p.speed) {
		// desired movement is possible
		playerMove(p.posX - p.speed);
	} else {
		// space too small, move to left-most position
		playerMove(0);
	}
}


/**
 * move player right
 */
void playerMoveRight()
{
	// check if space between player and border of screen is big enough 
	if (p.posX < SCREENWIDTH - PLAYERWIDTH - p.speed) {
		// desired movement is possible
		playerMove(p.posX + p.speed);
	} else {
		// space too small, move to right-most position
		playerMove(SCREENWIDTH - PLAYERWIDTH);
	}
}


/**
 * toggle turbo mode on (if key is kept pressed)
 */
void playerTurboOn()
{
	p.speed = 2;
}


/**
 * toggle turbo mode off (if key is kept pressed)
 */
void playerTurboOff()
{
	p.speed = 1;
}


/**
 * player was hit by an alien shot
 */
int playerHitCheck(int hostileShotX, int hostileShotY)
{
	int fPlayerWasHit = 0;
	
	// if shot reached vertikal position of player
	if (hostileShotY == PLAYERPOSY) {
		// if shot hits player
		if (hostileShotX >= p.posX && hostileShotX <= p.posX + PLAYERWIDTH -1) {
			fPlayerWasHit = 1;		// set return value
		}
	}
	
	return fPlayerWasHit;				// return if player was hit
}


/**
 * Launch Missile
 */
void playerLaunchMissile()
{
	// only launch missile if no other is on its way
	if (p.missileFired == 0) {
		p.missileFired = 1;	// missile is on its way
		p.missileX = p.posX + PLAYERWIDTH / 2;	// launched from the middle of player...
		p.missileY = PLAYERPOSY;	// ...at same horizontal position
	}
}


/**
 * Reload Missile
 */
static void playerReloadMissile()
{
	p.missileFired = 0;	// no player missile flying
}


/**
 * move player missile and do alien/bunker hit testing
 * return value - 0: still some aliens left, 1: no aliens left
 */
int playerMoveMissile()
{
	int fNoAliensLeft = 0;	// return value
	int alienTypeHit = 0;

	// only do movements if there is a missile to move
	if (p.missileFired == 1) {
		
		playerMissileClear(p.missileX, p.missileY);		// clear old missile position
		playerDisplay(p.posX, p.posY); // todo: check if this can be removed later if missiled is fired, 
						//the middle of player is cleared
		p.missileY--;						// move missile		

		// if missile out of battlefield
		if (p.missileY < 0) {
			playerReloadMissile();				// reload missile
		} else {
			playerMissileDisplay(p.missileX, p.missileY);	// display missile at new position
		}

		// if missile hits an alien (TODO)
		alienTypeHit = aliensHitCheck(p.missileX, p.missileY);
		if (alienTypeHit != 0) {
			
			doScoring(alienTypeHit);			// increase score
			playerReloadMissile();				// reload missile

			aliensClear(a.posX, a.posY, a.right, a.bottom); // clear old posiiton of aliens
			
			render();
			if (shipnum == 0) {
				fNoAliensLeft = 1;
			}
			
			// speed of aliens
			weite = (shipnum + (skill_level * 10) - (level * 5) + 5) / 10;
			if (weite < 0) {
				weite = 0;
			}
			
			playerMissileClear(p.missileX, p.missileY);	// clear old missile position
			aliensDisplay(a.posX, a.posY, a.right, a.bottom);  // display aliens
		}
		
		// if missile hits a bunker
		if (bunkersHitCheck(p.missileX, p.missileY) == 1) {
			bunkersClearElement(p.missileX, p.missileY);	// clear element of bunker
			playerReloadMissile();				// reload player missile
		}

		// if missile hits ufo
		if (ufoHitCheck(p.missileX, p.missileY) == 1) {
			doScoring(UFO_ALIEN_TYPE);
			playerReloadMissile();
		}
	}

	return fNoAliensLeft;
	
}

/** 
 * let player explode
 */
void playerExplode(){
	playerExplosionDisplay(p.posX, p.posY);
	playerDisplay(p.posX, p.posY);
}
