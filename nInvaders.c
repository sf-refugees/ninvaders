#include <stdio.h>
//#include <stdlib.h>
//#include <ncurses.h>
//#include <signal.h>
#include <string.h>
#include <unistd.h>
#include "nInvaders.h"
#include "player.h"
#include "aliens.h"
#include "ufo.h"
#ifndef true
#define true 1
#endif
#ifndef false
#define false 0
#endif

void initlevel()
{
	playerReset();
	aliensReset();
	ufoReset();
	bunkersReset();
	render();
}


static void finish(int sig)
{
        endwin();
fprintf(stderr,"\n");
fprintf(stderr,"This program is free software; you can redistribute it and/or modify\n");
fprintf(stderr,"it under the terms of the GNU General Public License as published by\n");
fprintf(stderr,"the Free Software Foundation; either version 2 of the License, or\n");
fprintf(stderr,"(at your option) any later version.\n");
fprintf(stderr,"\n");
fprintf(stderr,"This program is distributed in the hope that it will be useful,\n");
fprintf(stderr,"but WITHOUT ANY WARRANTY; without even the implied warranty of\n");
fprintf(stderr,"MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n");
fprintf(stderr,"GNU General Public License for more details.\n");
fprintf(stderr,"\n");
fprintf(stderr,"You should have received a copy of the GNU General Public License\n");
fprintf(stderr,"along with this program; if not, write to the Free Software\n");
fprintf(stderr,"Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA\n");
fprintf(stderr,"\n");
fprintf(stderr,"Use the -gpl  command line switch to see the full license of this program\n");
fprintf(stderr,"Use the -help command line switch to see who wrote this program \n");
fprintf(stderr,"\n");
fprintf(stderr,"\n");
fprintf(stderr,"\n");
fprintf(stderr,"=========================================================================\n");
fprintf(stderr,"\n");

fprintf(stderr,"Final score: %7.7ld, Final level: %2.2d\nFinal rating... ",score,level);
	if (p.lives>0)
		fprintf(stderr,"Quitter\n\n");
	else if(score<5000)
		fprintf(stderr,"Alien Fodder\n\n");
	else if(score<7500)
		fprintf(stderr,"Easy Target\n\n");
	else if(score<10000)
		fprintf(stderr,"Barely Mediocre\n\n");
	else if(score<10000)
		fprintf(stderr,"Shows Promise\n\n");
	else if(score<15000)
		fprintf(stderr,"Alien Blaster\n\n");
	else if(score<20000)
		fprintf(stderr,"Earth Defender\n\n");
	else if(score>19999)
		fprintf(stderr,"Supreme Protector\n\n");
	showVersion();
        exit(0);
}



void game_over(int a) 
{
	int xo, yo;
	xo = (SCREENWIDTH / 2) - (31 / 2);
	yo = (SCREENHEIGHT / 2) - (13 / 2);
	gameOverDisplay (xo, yo);
	
	sleep(4);
	finish(0);
}

int hit_alien_test(int shotx, int shoty, int alienx, int alieny)
{
	int getroffen = 0;
	int shipx, shipy = 0;
	if (shotx >= alienx && shotx <= alienx + ALIENS_MAX_NUMBER_X * 3 - 1
	    && shoty >= alieny && shoty <= alieny + (ALIENS_MAX_NUMBER_Y - 1) * 2) {
		shipx = (shotx - alienx) / 3;
		shipy = (shoty - alieny) / 2;
		if (alienBlock[shipy][shipx] != 0) {
			alienBlock[shipy][shipx] = 0;
			getroffen = 1;
		}
	}
	return getroffen;
}

int hit_bunker_test(int shotx, int shoty)
{
	int adjx, adjy;
	if (shotx >= BUNKERX && shotx <= BUNKERX + BUNKERWIDTH
	    && shoty >= BUNKERY && shoty <= BUNKERY + BUNKERHEIGHT) {
		// the shot is in the range - do a detailed bunker collision test
		adjy = shoty - BUNKERY; 
		adjx = shotx - BUNKERX;
		if (adjy <= BUNKERHEIGHT-1){ //todo: eingefuegt. abfrage ist sonst unsinnig, da speicher zufällig gemischt.
			if(bunker[adjy][adjx] == 1){
				bunker[adjy][adjx] = 0;
				return 1; 
			}
		}
	}
	return 0;
}

void drawscore()
{
	statusDisplay(level, score, p.lives);
}


/**
 * reads input from keyboard and do action
 */
int readInput()
{
	int value = 0;
	int ch;
	static int lastmove;

	doSleep(1);

	ch = getch();		// get key pressed


	if (ch == 'l' || ch == KEY_RIGHT) {	// move player right

		if (lastmove == 'l') {
			playerTurboOn();	// enable Turbo
		} else {
			playerTurboOff();	// disable Turbo
		}
		playerMoveRight();		// move player
		lastmove = 'l';			// remember last move for turbo mode

	} else if (ch == 'h' || ch == KEY_LEFT) {	// move player left 

		if (lastmove == 'h') {
			playerTurboOn();	// enable Turbo
		} else {
			playerTurboOff();	// disable Turbo
		}
		playerMoveLeft();		// move player
		lastmove = 'h';			// remember last move for turbo mode

	} else if (ch == 'k' || ch == ' ') {	// shoot missile

		playerLaunchMissile();

	} else if (ch == 'p') {			// pause game until 'p' pressed again

		doSleep(100000);
		while (getch() != 'p')
			doSleep(100000);

	} else if (ch == 'W') {			// cheat: goto next level

		value = 1;

	} else if (ch == 'L') {			// cheat: one more live

		p.lives++;
		drawscore();
		
	} else if ((ch == 'q' || ch == 27)) {	// quit game

		finish(0);

	} else {		// disable turbo mode if key is not kept pressed

		lastmove = ' ';

	}

	return value;
}


int main(int argc, char **argv)
{
	int move_counter, shot_counter, ufo_move_counter;
	int alienshot_counter;
	int gotoNextLevel;
	weite = 0;

	/* initialize variables */

	score = 0L;
	p.lives = 3;
	skill_level = 1;


	/* evaluate command line parameters */

	if (argc == 3 && strcmp(argv[1], "-l") == 0) {
		if (argv[2][0] >= '0' && argv[2][0] <= '9') {
			skill_level = argv[2][0] - 48;
		} else {
			argc = 2;
		}
	}

	if (argc == 2 && strcmp(argv[1], "-gpl") == 0) {
		showGpl();
	}

	if (argc == 2 || (argc == 3 && strcmp(argv[1], "-l") != 0)) {
		showVersion();
		showUsage();
		exit(1);
	}


	/* initialize gaming field */

	graphicEngineInit();
	initlevel();




	/* start game */

	for (level = 1;; level++) {		

		move_counter = 0; 
		shot_counter = 0;
		alienshot_counter = 0;
		shootme_counter = 0;
		ufo_move_counter = 0;

		weite = (shipnum+(skill_level*10)-(level*5)+5)/10;

		if (weite < 0) {
			weite = 0;
		}

		/* display gaming field */
		refreshScreen();	
		drawscore();

		/* game loop */

		do {
			gotoNextLevel=0;
			
			if (move_counter == 0) {
				
				// move aliens
				if (aliensMove() == 1) {
					// aliens reached player
					p.lives = 0;
					game_over(1);
				}
				
			}
			
			if (shot_counter == 0) {
				
				// move player missile and break to next level if no aliens left
				if (playerMoveMissile() == 1) { 
					gotoNextLevel = 1;
				}

			}

			if (alienshot_counter == 0) {
				
				// move aliens' missiles and do action if player was hit
				if (aliensMissileMove() == 1) {
					// player was hit
					p.lives--;			// player looses one life
					drawscore();	                // draw score
					playerExplode(p.posX, p.posY);	// display some explosion graphics
					if (p.lives == 0) {		// if no lives left ...
						game_over(1);		// ... exit game
					}
				}
				
			}

			if (ufoShowUfo() == 1 && ufo_move_counter == 0) {
				// if there's a ufo move it one position left
				ufoMoveLeft();
			}
			
			
			if (alienshot_counter++ >= 5) {alienshot_counter=0;} // speed of alien shot
			if (shot_counter++ >= 1) {shot_counter=0;}           // speed of player shot
			if (move_counter++ >= weite) {move_counter=0;}       // speed of aliend
			if (ufo_move_counter++ >= 3) {ufo_move_counter=0;}   // speed of ufo

			playerDisplay(p.posX, p.posY);
			refreshScreen();	

			// do movements and key-checking; if cheat-warping goto next level
			if (readInput() == 1) {
				gotoNextLevel = 1;
			}
			
		} while (gotoNextLevel == 0);

		initlevel();
	}

	return 0;
	
}


void doScoring(int alienType)
{
	int points[4] = {100, 100, 100, 400};   // 0:blue, 1:green, 2:red, 3:ufo
	
	score += points[alienType];		// every alien does 100pts
	
	// every 6000 pts player gets a new live
	if (score % 6000 == 0){
		p.lives++;
	}
	
	drawscore();	// display score
}

