#ifndef MUSIC_H
#define MUSIC_H

#include "../timer/timer.h"

//Default: 1.65
#define SPEEDUP 1.6

#define TIMERSCALER 1

#define SECOND 0x17D7840 * TIMERSCALER

typedef char BOOL;
#define TRUE 1
#define FALSE 0

#define SOUND_BACKGROUND_MUSIC 0
#define SOUND_SUPER_PILL_EATED 1
#define SOUND_LIFE_LOSED 2
#define SOUND_LIFE_GAINED 3

typedef enum note_durations
{
	time_semibiscroma = (unsigned int)(SECOND * SPEEDUP / 64.0f + 0.5), // 1/128
	time_biscroma = (unsigned int)(SECOND * SPEEDUP / 32.0f + 0.5), // 1/64
	time_semicroma = (unsigned int)(SECOND * SPEEDUP / 16.0f + 0.5), // 1/32
	time_croma = (unsigned int)(SECOND * SPEEDUP / 8.0f + 0.5), // 1/16
	time_semiminima = (unsigned int)(SECOND * SPEEDUP / 4.0f + 0.5), // 1/4
	time_minima = (unsigned int)(SECOND * SPEEDUP / 2.0f + 0.5), // 1/2
	time_semibreve = (unsigned int)(SECOND * SPEEDUP + 0.5), // 1
} NOTE_DURATION;

typedef enum frequencies
{
    a2b = 13729,  // 116.54Hz
    b2 = 12959,   // 123.47Hz
    c3b = 12598,  // 127.00Hz
    c3 = 12231,   // 130.81Hz
    d3 = 10897,   // 146.83Hz
    e3 = 9708,    // 164.81Hz
    f3 = 9163,    // 174.61Hz
    g3 = 8163,    // 196.00Hz
    a3b = 7705,   // 207.65Hz
    a3 = 7273,    // 220.00Hz
    b3 = 6479,    // 246.94Hz
    c4 = 6116,    // 261.63Hz
    d4 = 5448,    // 293.66Hz
    e4 = 4854,    // 329.63Hz
    f4 = 4582,    // 349.23Hz
    g4 = 4082,    // 392.00Hz
    a4 = 3636,    // 440.00Hz
    b4 = 3240,    // 493.88Hz
    c5 = 3058,    // 523.25Hz
    pause = 0,    // Pausa (nessun suono)
	
    b1 = 25915,   // 61.74Hz
    f2d = 17297,  // 92.50Hz
    e2b = 20571,  // 77.78Hz
    c2 = 24461,   // 65.41Hz
    g2 = 16327,   // 98.00Hz
    e2 = 19415,   // 82.41Hz
    e2d = 18326,  // 87.31Hz
    a2 = 18545,   // 110.00Hz
    f2 = 18326    // 87.31Hz
} FREQUENCY;

typedef struct {
	FREQUENCY freq;
	NOTE_DURATION duration;
} NOTE;

extern uint8_t soundToPlay;

void playNote(NOTE note);
BOOL isNotePlaying(void);
void playSoundEffect(uint8_t sound);
void playMusicSound();
void playMusicSoundDuration();

#endif
/* EOF */
