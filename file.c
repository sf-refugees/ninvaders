/**
 * nInvaders - a space invaders clone for ncurses
 * Copyright (C) 2002-2003 Dettus
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA
 *
 * homepage: http://ninvaders.sourceforge.net
 * mailto: ninvaders-devel@lists.sourceforge.net
 *
 */

 
//#include "file.h"
#include <stdio.h>	
#include <string.h>


// some constant values
#define HIGHSCORE_VERSION 1
#define MAX_CHARS_HIGHSCORE_NAME 8
#define MAX_NUMBER_HIGHSCORE_ENTRIES 10


// data structure
typedef struct HighScoreEntry HighScoreEntry;
struct HighScoreEntry {
	int score;	  			// score
	char name[MAX_CHARS_HIGHSCORE_NAME+1];	// player name
};
      
typedef struct HighScore HighScore;
struct HighScore {
	HighScoreEntry beginner[MAX_NUMBER_HIGHSCORE_ENTRIES];	// beginner
	HighScoreEntry normal[MAX_NUMBER_HIGHSCORE_ENTRIES];	// normal
	HighScoreEntry expert[MAX_NUMBER_HIGHSCORE_ENTRIES];	// expert
};



/**
 * writes highscore to file 
 */
void writeHighScore (HighScore hs){

	FILE* fpHighScore;
	int n;

	fpHighScore = fopen ("highscore", "w");  // open file for writing action

	// if opening was successful
	if (fpHighScore != 0) {
		
		// header
		fputs ("nInvaders HighScore\n", fpHighScore);
		fputs ("  version ", fpHighScore);		
		fprintf (fpHighScore, "%d ", HIGHSCORE_VERSION);
		fputs ("\n\n", fpHighScore);
			
		// score-beginner
		fputs ("beginner\n", fpHighScore);		
		for (n=0; n<MAX_NUMBER_HIGHSCORE_ENTRIES; n++) {
			fprintf (fpHighScore, "  %2.7d ", hs.beginner[n].score);
			fputs (hs.beginner[n].name, fpHighScore);
			fputs ("\n", fpHighScore);
		}
		
		// score-normal
		fputs ("normal\n", fpHighScore);
		for (n=0; n<MAX_NUMBER_HIGHSCORE_ENTRIES; n++) {
			fprintf (fpHighScore, "  %2.7d ", hs.normal[n].score);
			fputs (hs.normal[n].name, fpHighScore);
			fputs ("\n", fpHighScore);
		}
		
		// score-expert
		fputs ("expert\n", fpHighScore);
		for (n=0; n<MAX_NUMBER_HIGHSCORE_ENTRIES; n++) {
			fprintf (fpHighScore, "  %2.7d ",  hs.expert[n].score);
			fputs (hs.expert[n].name, fpHighScore);
			fputs ("\n", fpHighScore);
		}
		
		// close file
		if (fclose (fpHighScore) == 0) {
			//sucessfully closed file
		} else {
			// error occured
		} // if
		
		
	} // if


}



int main(int argc, char **argv)
{
	HighScore hs;
	
	int n;
	
	for (n=0; n<MAX_NUMBER_HIGHSCORE_ENTRIES; n++) {
		hs.beginner[MAX_NUMBER_HIGHSCORE_ENTRIES-1-n].score = n*1000;
		strcpy(hs.beginner[MAX_NUMBER_HIGHSCORE_ENTRIES-1-n].name, "hollinge");
		hs.normal[MAX_NUMBER_HIGHSCORE_ENTRIES-1-n].score = n*1000;
		strcpy(hs.normal[MAX_NUMBER_HIGHSCORE_ENTRIES-1-n].name, "sen_hoss");
		hs.expert[MAX_NUMBER_HIGHSCORE_ENTRIES-1-n].score = n*1000;
		strcpy(hs.expert[MAX_NUMBER_HIGHSCORE_ENTRIES-1-n].name, "segoh");
	}
	
	writeHighScore(hs);
	
	return 0;
}



