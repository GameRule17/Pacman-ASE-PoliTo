#ifndef __GAME_STATE
#define __GAME_STATE

#import "GAME/drawing_func.h"

#define MAX_TIME_SECONDS 60
#define INITIAL_NUM_LIFES 1
#define MAX_NUM_LIFES 3
#define MAX_NUM_PILLS 240

extern int countdown;
extern int num_lifes;
extern int score;
extern int game_pause;
extern int num_eated_pills;

void updateCountdown();
void updateScoreAndCheckVictory(int addValue);

#endif /* end __GAME_STATE */