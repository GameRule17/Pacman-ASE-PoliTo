#ifndef __MOVING_FUNC
#define __MOVING_FUNC

#import "GAME/game_matrix.h"
#import "GAME/drawing_func.h"

#define J_UP_KEY 1
#define J_DOWN_KEY 2
#define J_LEFT_KEY 3
#define J_RIGHT_KEY 4

/*
	Power pill generation using real board is much faster,
	so a lower treshold is set
*/
#ifdef SIMULATOR
#define PROBABILITY_TRESHOLD 60
#else
#define PROBABILITY_TRESHOLD 10
#endif
#define MAGIC_RANDOM_NUMBER 1103515245

extern uint16_t direction;

extern uint16_t pacman_x;
extern uint16_t pacman_y;

uint16_t movePacman(uint16_t direction);
void tryGenerationPowerPills();

#endif /* end __MOVING_FUNC */