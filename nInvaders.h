#include <stdio.h>
#include <stdlib.h>
#include "view.h"
#include "globals.h"


#ifndef NINVADERS
#define NINVADERS

#define UFO_ALIEN_TYPE   0
#define RED_ALIEN_TYPE   1
#define GREEN_ALIEN_TYPE 2
#define BLUE_ALIEN_TYPE  3 

int main(int argv, char **argc);	// hey! it has to start somewhere!

extern void render(void);
	
void game_over(int a);
void drawscore();
		
void doScoring(int alienType);

// todo: let's try to not having to declare these "public"
int weite;
int level;
int skill_level;
	
// included from globals.h
extern void doSleep();
extern void showUsage();
extern void showVersion();
extern void showGplShort();
extern void showGpl();

#endif
