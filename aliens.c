#include "aliens.h"
#include "player.h"
#include "nInvaders.h"

/**
 * initialize aliens attributes
 */
void aliensReset()
{
	int i,j;
	
	// three different types of aliens [5], [10]
	int level[ALIENS_MAX_NUMBER_Y][ALIENS_MAX_NUMBER_X]={
		{1,1,1,1,1,1,1,1,1,1},
		{2,2,2,2,2,2,2,2,2,2},
		{2,2,2,2,2,2,2,2,2,2},
		{3,3,3,3,3,3,3,3,3,3},
		{3,3,3,3,3,3,3,3,3,3}
	};

	aliensClear(a.posX, a.posY, a.right, a.bottom);	// clear old position of aliens
	
	// reset alien position
	a.posX = 0;
	a.posY = 0;
	a.right = 0;
	a.bottom = 0;
	a.left = 0;
	a.speed = 1;
	
	// copy level-array to enemy-array 
	for (i=0;i<ALIENS_MAX_NUMBER_X;i++) {
		for (j=0;j<ALIENS_MAX_NUMBER_Y;j++) {
			alienBlock[j][i]=level[j][i];
		}
	}
	
	// reset missiles
	for (i = 0; i < ALIENS_MAX_MISSILES; i++) {
		alienshotx[i] = 0;  // start with zero values
		alienshoty[i] = 0;  // start with zero values
	}
	alienshotnum = 1;	    // one missile at the same time
	alienshotx[0] = 5;	    // x position of first alienshot
	alienshoty[0] = 1;	    // y position of first alienshot

}

/**
 * initialize bunkers attributes
 */
void bunkersReset()
{
	int a, b;

	// set position of bunker sprites. user graphical char bunkerd for better visual overview
	// and set according to this the bunker-array
	char bunkerd[BUNKERHEIGHT][BUNKERWIDTH+1] = {
		"        ###                 ###                 ###                 ###         ",
		"       #####               #####               #####               #####        ",
		"      #######             #######             #######             #######       ",
		"      ##   ##             ##   ##             ##   ##             ##   ##       "
	};
	//       12345678901234567890123456789012345678901234567890123456789012345678901234567890
	// 80 characters wide

	// copy graphical "bunkerd" to binary "bunker"
	for (a = 0; a < BUNKERWIDTH; a++) {
		for (b = 0; b < BUNKERHEIGHT; b++) {
			if (bunkerd[b][a] == '#')
				bunker[b][a] = 1;
			else
				bunker[b][a] = 0;
		}
	}
	
	// display bunkers sprite
	bunkersDisplay(&bunker[0][0]);	
}

/**
 * move aliens and test if they've reached the
 * bottom of the windows or the bunkers.
 */
int aliensMove()
{
	
	int cx,cy;
	int fReachedPlayer=0; 				// return value

	render();	
	aliensClear(a.posX, a.posY, a.right, a.bottom);	// clear old position of aliens

	a.posX = a.posX + a.speed;			// move aliens left/ right
	
	// when aliens reached left or right screen-border
	if (a.posX == (BUNKERWIDTH + BUNKERX - 5 - a.right) || a.posX == (BUNKERX + a.left)) {
		
		a.posY++;				// move aliens downwards
		
		// aliens reached player
		if (a.posY == SCREENHEIGHT - 2 - a.bottom) {
			fReachedPlayer = 1;		// set return value
		}
		
		// aliens reached bunkers //funzt nicht ganz: todo
		if (a.posY == BUNKERY - a.bottom) {
			// clear bunkers
			for(cx=0;cx<BUNKERWIDTH;cx++) {
				for(cy=0;cy<BUNKERHEIGHT;cy++) { 
					bunker[cy][cx]=0;	
				}
			}
			bunkersClear();	// clear bunkers sprites
		}
		
		a.speed = a.speed * (-1);		  // change direction of aliens' movements
	}

	aliensDisplay(a.posX, a.posY, a.right, a.bottom); // display aliens at new position
	
	return fReachedPlayer;				  // return if aliens reached player
}


/**
 * display alien animation, display remaining parts of aliens and bunker 
 */
void render()
{
	int k,row;
	int c=0;

	// calculate left, right, bottom, lowest_ship	
	a.left=1;
	a.right=-1;
	a.bottom=-1;
	shipnum=0;
	for (k=0;k<11;k++) {
		lowest_ship[k]=-1;
	}
	
	for (row=0;row<ALIENS_MAX_NUMBER_Y*2;row++) {
		if ((row%2)==0){
			for (k=0;k<ALIENS_MAX_NUMBER_X;k++) {
				if (alienBlock[c][k] != 0) {
					lowest_ship[k]=row;
					shipnum++;
					if (a.left==1 || -k>a.left) {a.left=-k;}
					if (a.right==-1 || k>a.right) {a.right=k;}
					if (a.bottom==-1 || c>a.bottom) {a.bottom=c;}
				} 
			}
		} else {
			c++;
		}
	}
	a.bottom=a.bottom*2;	// every 2nd row is an empty row
	a.left=a.left*3; // alien sprite is 3 chars wide
	a.right=a.right*3; // alien sprite is 3 chars wide
	
	// display remaining aliens with animation
	aliensRefresh(level);

}


/**
 * move aliens' missiles and do player/bunker hit testing
 * a zero value in alienshotx indicates that the appropriate missile is loaded, but not fired
 */
int aliensMissileMove(){
	int i, tmp;
	int fPlayerWasHit = 0;

	
	// loop all possible missiles
	for (i = 0; i < ALIENS_MAX_MISSILES; i++) {
		
		// if the current missile is flying we should do movements
		if (alienshotx[i] != 0) {
			
			aliensMissileClear(alienshotx[i],alienshoty[i]);	// clear old position
				
			// if missile hit the bunkers	
			if (hit_bunker_test(alienshotx[i], alienshoty[i]) == 1) {
				alienshotx[i] = 0;		// value of zero reloads missile
			}
			
			alienshoty[i]++;			// move missile downwards
			
			// check if player was hit by an alien missile
			if (playerHitCheck(alienshotx[i], alienshoty[i]) == 1) {
				fPlayerWasHit = 1;
			}
			
		} else {					// missile not launched yet
			
			// start new missile if counter says so
			if (shootme_counter++ > (skill_level * 8 + 10) * (shipnum + 5)) {
				shootme_counter = 0;				// reset counter				
				tmp = random() % ALIENS_MAX_NUMBER_X;  		// randomly select one of the ...
				while (lowest_ship[tmp] == -1) {		// ...aliens at the bottom of ...
					tmp = random() % ALIENS_MAX_NUMBER_X;	// ...a column to launch missile
				}
				alienshoty[i]=a.posY+lowest_ship[tmp];		// set y position of missile
				alienshotx[i]=a.posX+tmp*3;			// set x position of missile
			}
		} // if 
		
		// display missiles if still running or just launched; could have been modified in the above code
		if (alienshotx[i] != 0) {
			aliensMissileDisplay(alienshotx[i], alienshoty[i]); // display Missile at new position
		}		
		
	} // for


	return fPlayerWasHit;
}
