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


#ifndef HIGHSCORE
#define HIGHSCORE

// constants
#define HIGHSCORE_ID "nInvaders Highscore"
#define SIZE_HIGHSCORE_ID 30

#define HIGHSCORE_VERSION "01"
#define SIZE_HIGHSCORE_VERSION 5

#define MAX_CHARS_HIGHSCORE_NAME 8
#define MAX_NUMBER_HIGHSCORE_ENTRIES 10

// data structures
typedef struct HighScoreEntry HighScoreEntry;
struct HighScoreEntry
{
	int score;	  			// score
	char name[MAX_CHARS_HIGHSCORE_NAME+1];	// player name
};
      
typedef struct HighScore HighScore;
struct HighScore
{
	char identifier[SIZE_HIGHSCORE_ID]; // "nInvaders Highscore";
	char version[SIZE_HIGHSCORE_VERSION]; // "01";
	HighScoreEntry beginner[MAX_NUMBER_HIGHSCORE_ENTRIES];	// beginner
	HighScoreEntry normal[MAX_NUMBER_HIGHSCORE_ENTRIES];	// normal
	HighScoreEntry expert[MAX_NUMBER_HIGHSCORE_ENTRIES];	// expert
};

HighScore highscore;

HighScore readHighScore();
void writeHighScore(HighScore hs);
void addEntry(char *name, int score, int hsType);

#endif
