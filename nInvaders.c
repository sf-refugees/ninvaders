#include <stdio.h>
#include <string.h>
#include "nInvaders.h"
#include "player.h"
#include "aliens.h"
#include "ufo.h"

int lives;
long score;


/**
 * initialize level: reset attributes of most units
 */
static void initLevel()
{
	playerReset();
	aliensReset();
	ufoReset();
	bunkersReset();
	render();
	drawscore();
}


/**
 * evaluate command line parameters 
 */
static void evaluateCommandLine(int argc, char **argv)
{
	
	// -l : set skill level
	if (argc == 3 && strcmp(argv[1], "-l") == 0) {
		if (argv[2][0] >= '0' && argv[2][0] <= '9') {
			skill_level = argv[2][0] - 48;
		} else {
			argc = 2;
		}
	}

	// -gpl : show GNU GPL
	if (argc == 2 && strcmp(argv[1], "-gpl") == 0) {
		showGpl();
	}

	// wrong command line: show usage
	if (argc == 2 || (argc == 3 && strcmp(argv[1], "-l") != 0)) {
		showVersion();
		showUsage();
		exit(1);
	}
}


static void finish(int sig)
{
        endwin();
	showGplShort();
	
	fprintf(stderr,"\n");
	fprintf(stderr,"\n");
	fprintf(stderr,"=========================================================================\n");
	fprintf(stderr,"\n");
	
	fprintf(stderr,"Final score: %7.7ld, Final level: %2.2d\nFinal rating... ",score,level);
	if (lives>0)
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
	gameOverDisplay(xo, yo);
	
	doSleep(3*1000*1000);
	finish(0);
}


void drawscore()
{
	statusDisplay(level, score, lives);
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

		lives++;
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
	int aliens_move_counter = 0; 
	int aliens_shot_counter = 0;
	int player_shot_counter = 0;
	int ufo_move_counter = 0;
	int gotoNextLevel = 0;
	
	// initialize variables 

	weite = 0;
	score = 0;
	lives = 3;
	skill_level = 1;

	
	evaluateCommandLine(argc, argv);	// evaluate command line parameters
	graphicEngineInit();			// initialize graphic engine
	
			


	// start game
	for (level = 1;; level++) {		

		initLevel();			// initialize level
		
		
		aliens_move_counter = 0; 
		aliens_shot_counter = 0;
		player_shot_counter = 0;
		ufo_move_counter = 0;
	
		
		weite = (shipnum+(skill_level*10)-(level*5)+5)/10;

		if (weite < 0) {
			weite = 0;
		}


		// game loop 
		do {
			gotoNextLevel=0;

			// move aliens			
			if (aliens_move_counter == 0 && aliensMove() == 1) {
				// aliens reached player
				lives = 0;
				game_over(1);
				
			}
			
			// move player missile			
			if (player_shot_counter == 0 && playerMoveMissile() == 1) {
				// no aliens left
				gotoNextLevel = 1;
			}

			// move aliens' missiles
			if (aliens_shot_counter == 0 && aliensMissileMove() == 1) {
				// player was hit
				lives--;			// player looses one life
				drawscore();	                // draw score
				playerExplode();		// display some explosion graphics
				if (lives == 0) {		// if no lives left ...
					game_over(1);		// ... exit game
				}
			}

			// move ufo
			if (ufo_move_counter == 0 && ufoShowUfo() == 1) {
				ufoMoveLeft();			// move it one position to the left
			}
			
			
			if (aliens_shot_counter++ >= 5) {aliens_shot_counter=0;} // speed of alien shot
			if (player_shot_counter++ >= 1) {player_shot_counter=0;}           // speed of player shot
			if (aliens_move_counter++ >= weite) {aliens_move_counter=0;}       // speed of aliend
			if (ufo_move_counter++ >= 3) {ufo_move_counter=0;}   // speed of ufo

			refreshScreen();

			// do movements and key-checking; if cheat-warping goto next level
			if (readInput() == 1) {
				gotoNextLevel = 1;
			}

			
		} while (gotoNextLevel == 0);


	} // for (level...

	return 0;
	
}


void doScoring(int alienType)
{
	int points[4] = {500, 200, 150, 100};   	// 0: ufo, 0:red, 1:green, 2:blue
	
	score += points[alienType];		// every alien type does different scoring points
	
	// every 6000 pts player gets a new live
	if (score % 6000 == 0){
		lives++;
	}
	
	drawscore();	// display score
}

