#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include "view.h"
#include "globals.h"


#ifndef NINVADERS
#define NINVADERS

#define BLUE_ALIEN_TYPE  0 
#define GREEN_ALIEN_TYPE 1
#define RED_ALIEN_TYPE   2
#define UFO_ALIEN_TYPE   3

int main(int argv, char **argc);	// hey! it has to start somewhere!
//static void finish(int sig);
extern void render(void);
	
void game_over(int a);
void drawscore();
	
int hit_bunker_test(int shotx, int shoty);
int hit_alien_test(int shotx, int shoty, int alienx, int alieny);
	
void doScoring(int alienType);

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
