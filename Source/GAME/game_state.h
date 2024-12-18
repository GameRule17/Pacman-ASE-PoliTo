#ifndef __GAME_STATE
#define __GAME_STATE

#import "GAME/drawing_func.h"

#define MAX_TIME_SECONDS 60
#define INITIAL_NUM_LIFES 1
#define MAX_NUM_LIFES 3
#define MAX_NUM_PILLS 240

extern uint16_t countdown;
extern int num_lifes;
extern uint16_t score;
extern uint16_t game_pause;
extern uint16_t num_eated_pills;

void updateCountdown();
void updateScoreAndCheckVictory(uint16_t addValue);

#endif /* end __GAME_STATE */