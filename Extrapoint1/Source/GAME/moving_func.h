#ifndef __MOVING_FUNC
#define __MOVING_FUNC

#import "GAME/game_matrix.h"
#import "GAME/drawing_func.h"

#define J_UP_KEY 1
#define J_DOWN_KEY 2
#define J_LEFT_KEY 3
#define J_RIGHT_KEY 4

#define PROBABILITY_TRESHOLD 60
#define MAGIC_RANDOM_NUMBER 1103515245

extern uint16_t direction;

extern uint16_t pacman_x;
extern uint16_t pacman_y;

uint16_t movePacman(uint16_t direction);
void tryGenerationPowerPills();

#endif /* end __MOVING_FUNC */