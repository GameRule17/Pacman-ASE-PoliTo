#ifndef __GAME_STATE
#define __GAME_STATE

#import "GAME/drawing_func.h"

#define MAX_TIME_SECONDS 60
#define INITIAL_NUM_LIVES 1
#define MAX_NUM_LIVES 3
#define MAX_NUM_PILLS 240

extern uint16_t countdown;
extern uint16_t numLives;
extern uint16_t score;
extern uint16_t gamePause;

void startGame();
void updateCountdown();
void updateScore(uint16_t addValue);
void checkVictory();

#endif /* end __GAME_STATE */