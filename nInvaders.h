#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include "view.h"
#include "globals.h"


#ifndef NINVADERS
#define NINVADERS


	int main(int argv, char **argc);	// hey! it has to start somewhere!
	//static void finish(int sig);
	extern void render(void);
	
	void game_over(int a);
	void drawscore();
	
	int hit_bunker_test(int shotx, int shoty);
	int hit_player_test(int shotx, int shoty, int alienx, int alieny);
	
	void doScoring();
	
	int weite;
	int level;
	int skill_level;
	long score;
	
	// included from globals.h
	extern void doSleep();
	extern void showUsage();
	extern void showVersion();
	extern void showGpl();

#endif
