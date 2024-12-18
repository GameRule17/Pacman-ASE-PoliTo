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
extern uint8_t pacman_movement_completed;

void updateCountdown();
void updateScore(uint16_t addValue);
void checkVictory();

#endif /* end __GAME_STATE */