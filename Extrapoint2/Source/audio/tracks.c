#include "music.h"

#define RIT_SEMIMINIMA 8
#define RIT_MINIMA 16
#define RIT_INTERA 32

#define UPTICKS 1

const NOTE song[] = 
{
	// PACMAN MUSIC 
	// 1
	{b1, time_croma},
	{b2, time_croma},
	{f2d, time_croma},
	{e2b, time_croma},
	{b2, time_semicroma},
	{f2d, time_croma+time_semicroma},
	{e2b, time_semiminima},
	{c2, time_croma},
	{c3, time_croma},
	{g2, time_croma},
	{e2, time_croma},
	{c3, time_semicroma},
	{g2, time_croma+time_semicroma},
	{e2, time_semiminima},
	
	// 2
	{b1, time_croma},
	{b2, time_croma},
	{f2d, time_croma},
	{e2b, time_croma},
	{b2, time_semicroma},
	{f2d, time_croma+time_semicroma},
	{e2b, time_semiminima},
	{e2, time_semicroma},
	{e2, time_semicroma},
	{f2, time_croma},
	{f2, time_semicroma},
	{f2d, time_semicroma},
	{g2, time_croma},
	{g2, time_semicroma},
	{a2b, time_semicroma},
	//{a2, time_croma},
	{b2, time_semiminima}
};

void playMusic() {
	
	static int currentNote = 0;
	static int ticks = 0;
	if(!isNotePlaying()) {
		++ticks;
		if(ticks == UPTICKS) {
			ticks = 0;
			playNote(song[currentNote++]);
		}
	}
	
	if(currentNote == (sizeof(song) / sizeof(song[0]))) {
		currentNote = 0;
	}
}