#include "view.h"

#ifndef UFO
#define UFO

typedef struct Ufo Ufo;
		
struct Ufo {
	int posX;	  // horizontal position of aliens
	int posY;	  // vertical position of aliens
};
	
Ufo ufo;

void ufoReset();
int ufoShowUfo();
void ufoMoveLeft();
int ufoHitCheck(int shotX, int shotY);
	
// methods that handle graphic display, from view.c
extern void ufoDisplay(int x, int y);
extern void ufoRefresh();
extern void ufoClear(int x, int y);

#endif
