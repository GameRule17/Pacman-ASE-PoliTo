#ifndef __GAME_STATE
#define __GAME_STATE

#import "GAME/drawing_func.h"

#define MAX_TIME_SECONDS 60
#define INITIAL_NUM_LIFES 1
#define MAX_NUM_LIFES 5

#define X_POSITION_LIVES_IN_GAME 85
#define Y_POSITION_LIVES_IN_GAME 300
#define X_POSITION_LIVES_IN_GAMEOVER 85
#define Y_POSITION_LIVES_IN_GAMEOVER 170

extern int countdown;
extern int num_lifes;
extern int score;
extern int game_pause;

void updateCountdown();
void addNewValueScore(int addValue);

#endif /* end __GAME_STATE */