#include "view.h"

#ifndef UFO
#define UFO
		
struct structUfo {
	int posX;	  // horizontal position of aliens
	int posY;	  // vertical position of aliens
};
	
struct structUfo u;

void ufoReset();
int ufoShowUfo();
void ufoMoveLeft();
int ufoHitCheck(int shotX, int shotY);
	
// methods that handle graphic display, from view.c
extern void ufoDisplay(int x, int y);
extern void ufoRefresh();
extern void ufoClear(int x, int y);

#endif
