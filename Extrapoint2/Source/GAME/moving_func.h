#ifndef __MOVING_FUNC
#define __MOVING_FUNC

#include <stdlib.h>
#include <math.h>

#import "GAME/game_matrix.h"
#import "GAME/drawing_func.h"

#define J_UP_KEY 1
#define J_DOWN_KEY 2
#define J_LEFT_KEY 3
#define J_RIGHT_KEY 4
#define DIRECTION_STOP 0

/*
	Power pill generation using real board is much faster,
	so a lower treshold is set
*/
#ifdef SIMULATOR
#define PROBABILITY_TRESHOLD_PILLS 60
#else
#define PROBABILITY_TRESHOLD_PILLS 10
#endif
#define MAGIC_RANDOM_NUMBER 1103515245

extern uint16_t direction;

void setPacman();
void setBlinky();
uint16_t movePacman(uint16_t direction);
void moveBlinky();
void freeBlinkyFromCage();
void tryGenerationPowerPills();
uint8_t checkCollision();

#endif /* end __MOVING_FUNC */