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
#define HIGHSCORE_ID "nInvaders Highscore"
#define SIZE_HIGHSCORE_ID 30

#define HIGHSCORE_VERSION "01"
#define SIZE_HIGHSCORE_VERSION 5

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
	char identifier[SIZE_HIGHSCORE_ID]; // "nInvaders Highscore";
	char version[SIZE_HIGHSCORE_VERSION]; // "01";
	HighScoreEntry beginner[MAX_NUMBER_HIGHSCORE_ENTRIES];	// beginner
	HighScoreEntry normal[MAX_NUMBER_HIGHSCORE_ENTRIES];	// normal
	HighScoreEntry expert[MAX_NUMBER_HIGHSCORE_ENTRIES];	// expert
};



/**
 * returns object highscore initialized with standard values
 */
HighScore getStandardHighScore(){
	HighScore hs;
	int n;
	
	strcpy(hs.identifier, HIGHSCORE_ID);
	strcpy(hs.version, HIGHSCORE_VERSION);		
	for (n=0; n<MAX_NUMBER_HIGHSCORE_ENTRIES; n++) {
		hs.beginner[MAX_NUMBER_HIGHSCORE_ENTRIES-1-n].score = (n+1)*1000;
		strcpy(hs.beginner[MAX_NUMBER_HIGHSCORE_ENTRIES-1-n].name, "hollinge");
		hs.normal[MAX_NUMBER_HIGHSCORE_ENTRIES-1-n].score = (n+1)*1000;
		strcpy(hs.normal[MAX_NUMBER_HIGHSCORE_ENTRIES-1-n].name, "sen_hoss");
		hs.expert[MAX_NUMBER_HIGHSCORE_ENTRIES-1-n].score = (n+1)*1000;
		strcpy(hs.expert[MAX_NUMBER_HIGHSCORE_ENTRIES-1-n].name, "segoh");
	}	
	
	return hs;
	
} // getStandardHighScore



/**
 * reads highscore to file 
 */
HighScore readHighScore (){
	
	FILE* fpHighScore;
	HighScore hs;
	int fStandardValues = 0;
	
	fpHighScore = fopen ("highscore", "r");  // open file for reading action

	// if opening was successful
	if (fpHighScore != NULL) {
		
		// read header
		fread (&hs.identifier, SIZE_HIGHSCORE_ID, 1, fpHighScore);
		fread (&hs.version, SIZE_HIGHSCORE_VERSION, 1, fpHighScore);
		
		// check if this is the correct highscore version
		if ((strcmp(hs.identifier, HIGHSCORE_ID) == 0)) {
			
			if (strcmp(hs.version, HIGHSCORE_VERSION) == 0) {
		
				// read data
				fread (&hs.beginner, sizeof(HighScoreEntry), MAX_NUMBER_HIGHSCORE_ENTRIES, fpHighScore);
				fread (&hs.normal, sizeof(HighScoreEntry), MAX_NUMBER_HIGHSCORE_ENTRIES, fpHighScore);
				fread (&hs.expert, sizeof(HighScoreEntry), MAX_NUMBER_HIGHSCORE_ENTRIES, fpHighScore);		
				
			} else {
				
				// wrong version
				fStandardValues = 1;
				puts ("(EE) readHighscore: wrong version number"); 
			}
			
		} else {
			
			// wrong file-identifier
			fStandardValues = 1;
			puts ("(EE) readHighscore: wrong file-id"); 
		}
		

		// close file
		fclose (fpHighScore);

		
	} else { 
		// highscore file does not exist or cannot be opened otherwise
		fStandardValues = 1;
		puts ("(EE) readHighscore: cannot open highscore file for reading"); 
		
	} // if
	

	
	if (fStandardValues == 1) {
		// use standard values
		hs = getStandardHighScore ();
		puts ("(II) readHighscore: using standard values");	
	}

	
	return hs;

} // readHighscore
	

	
	
/**
 * writes highscore to file 
 */
void writeHighScore (HighScore hs){

	FILE* fpHighScore;
	fpHighScore = fopen ("highscore", "w");  // open file for writing action

	// if opening was successful
	if (fpHighScore != NULL) {

		// write header
		fwrite (&hs.identifier, SIZE_HIGHSCORE_ID, 1, fpHighScore);
		fwrite (&hs.version, SIZE_HIGHSCORE_VERSION, 1, fpHighScore);

		// write data
		fwrite (&hs.beginner, sizeof(HighScoreEntry), MAX_NUMBER_HIGHSCORE_ENTRIES, fpHighScore);
		fwrite (&hs.normal, sizeof(HighScoreEntry), MAX_NUMBER_HIGHSCORE_ENTRIES, fpHighScore);
		fwrite (&hs.expert, sizeof(HighScoreEntry), MAX_NUMBER_HIGHSCORE_ENTRIES, fpHighScore);
	
		// close file
		fclose (fpHighScore);
		
	} else {
		
		puts ("(EE) writeHighscore: cannot open highscore file for writing");
		
	} // if

} // writeHighScore










void displayHighScore(HighScore hs){
	
	int n;
	
	puts (hs.identifier);
	printf (" v. ");
	puts (hs.version);
	
	puts ("beginner");
	for (n=0; n<MAX_NUMBER_HIGHSCORE_ENTRIES; n++) {
		printf ("  %2.7d ", hs.beginner[n].score);
		puts (hs.beginner[n].name);
	}
	puts ("normal");
	for (n=0; n<MAX_NUMBER_HIGHSCORE_ENTRIES; n++) {
		printf ("  %2.7d ", hs.normal[n].score);
		puts (hs.normal[n].name);
	}
	puts ("expert");	
	for (n=0; n<MAX_NUMBER_HIGHSCORE_ENTRIES; n++) {
		printf ("  %2.7d ", hs.expert[n].score);
		puts (hs.expert[n].name);
	}
	
}


int main(int argc, char **argv)
{
	HighScore hs;
	HighScore hsRead;
	
	
	hs = getStandardHighScore();
	writeHighScore(hs);

	hsRead = readHighScore();
	displayHighScore (hsRead);
	
	
	return 0;
}




