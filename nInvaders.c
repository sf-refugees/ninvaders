#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include "nInvaders.h"
#include "player.h"
#include "aliens.h"
#include "ufo.h"
#define FPS 50
   int lives;
long score;

int status; // status handled in timer
#define GAME_LOOP 1
#define GAME_NEXTLEVEL 2
#define GAME_PAUSED 3
#define GAME_OVER 4
#define GAME_EXIT 5
#define GAME_HIGHSCORE 6




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


void drawscore()
{
	statusDisplay(level, score, lives);
}


/**
 * reads input from keyboard and do action
 */
void readInput()
{
	int ch;
	static int lastmove;

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

		// set status to game paused
		if (status == GAME_PAUSED) {
			status = GAME_LOOP;
		} else {
			status = GAME_PAUSED;
		}

	} else if (ch == 'W') {			// cheat: goto next level

		status = GAME_NEXTLEVEL;

	} else if (ch == 'L') {			// cheat: one more live

		lives++;
		drawscore();
		
	} else if ((ch == 'q')) {	// quit game

		status = GAME_EXIT;

	} else {		// disable turbo mode if key is not kept pressed

		lastmove = ' ';

	}

}


/**
 * timer
 * this method is executed every 1 / FPS seconds  
 */
void handleTimer()
{
	static int aliens_move_counter = 0; 
	static int aliens_shot_counter = 0;
	static int player_shot_counter = 0;
	static int ufo_move_counter = 0;
	
	switch (status) {
		
		// go to next level
		case GAME_NEXTLEVEL:
			
			level++;	// increase level
			
			initLevel();	// initialize level
	
			aliens_move_counter = 0; 
			aliens_shot_counter = 0;
			player_shot_counter = 0;
			ufo_move_counter = 0;
		
			weite = (shipnum+(skill_level*10)-(level*5)+5)/10;
	
			if (weite < 0) {
				weite = 0;
			}
			
			// change status and start game!
			status = GAME_LOOP;
		
		
		// do game handling
		case GAME_LOOP:
		
			// move aliens			
			if (aliens_move_counter == 0 && aliensMove() == 1) {
				// aliens reached player
				lives = 0;
				status = GAME_OVER;
			}
			
			// move player missile			
			if (player_shot_counter == 0 && playerMoveMissile() == 1) {
				// no aliens left
				status = GAME_NEXTLEVEL;
			}

			// move aliens' missiles
			if (aliens_shot_counter == 0 && aliensMissileMove() == 1) {
				// player was hit
				lives--;			// player looses one life
				drawscore();	                // draw score
				playerExplode();		// display some explosion graphics
				if (lives == 0) {		// if no lives left ...
					status = GAME_OVER;		// ... exit game
				}
			}

			// move ufo
			if (ufo_move_counter == 0 && ufoShowUfo() == 1) {
				ufoMoveLeft();			// move it one position to the left
			}
			
			
			if (aliens_shot_counter++ >= 5) {aliens_shot_counter=0;}     // speed of alien shot
			if (player_shot_counter++ >= 1) {player_shot_counter=0;}     // speed of player shot
			if (aliens_move_counter++ >= weite) {aliens_move_counter=0;} // speed of aliend
			if (ufo_move_counter++ >= 3) {ufo_move_counter=0;}           // speed of ufo

			refreshScreen();
			break;
			
			
		// game is paused	
		case GAME_PAUSED:
			break;
			

		// game over			
		case GAME_OVER:
			// todo: let player decide if he wants to start over or quit.
			gameOverDisplay((SCREENWIDTH / 2) - (31 / 2), (SCREENHEIGHT / 2) - (13 / 2));
			doSleep(3*1000*1000);
			status = GAME_EXIT;
			break;
			
		
		// exit game
		case GAME_EXIT:
			finish(0);
			break;
			
			
		// display highscore
		case GAME_HIGHSCORE:
			break;
			
	}
}


/**
 * set up timer
 */
void setUpTimer()
{
	struct itimerval myTimer;
	struct sigaction myAction;
	myTimer.it_value.tv_sec = 0;
	myTimer.it_value.tv_usec = 1000000 / FPS;
	myTimer.it_interval.tv_sec = 0;
	myTimer.it_interval.tv_usec = 1000000 / FPS;
	setitimer(ITIMER_REAL, &myTimer, NULL);
	
	myAction.sa_handler = &handleTimer;
	myAction.sa_flags = SA_RESTART;
	sigaction(SIGALRM, &myAction, NULL);
}


int main(int argc, char **argv)
{
	
	// initialize variables 

	weite = 0;
	score = 0;
	lives = 3;
	level = 0;
	skill_level = 1;
	
	evaluateCommandLine(argc, argv);	// evaluate command line parameters
	graphicEngineInit();			// initialize graphic engine
	
	// set up timer/ game handling
	setUpTimer();		
	status = GAME_NEXTLEVEL;

	// read keyboard input
	do {
		// do movements and key-checking
		readInput();
	} while (0 == 0);


	return 0;
	
}


void doScoring(int alienType)
{
	int points[4] = {500, 200, 150, 100};   	// 0: ufo, 1:red, 2:green, 3:blue
	
	score += points[alienType];		// every alien type does different scoring points
	
	// every 6000 pts player gets a new live
	if (score % 6000 == 0){
		lives++;
	}
	
	drawscore();	// display score
}

