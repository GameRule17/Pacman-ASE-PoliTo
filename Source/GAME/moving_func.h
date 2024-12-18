#ifndef __MOVING_FUNC
#define __MOVING_FUNC

#import "GAME/game_matrix.h"
#import "GAME/drawing_func.h"

#define J_UP_KEY 1
#define J_DOWN_KEY 2
#define J_LEFT_KEY 3
#define J_RIGHT_KEY 4

#define MAGIC_RANDOM_NUMBER 1103515245

extern int direction;

extern int pacman_x;
extern int pacman_y;

void setPacman ();
int movePacman(int direction);
void tryGenerationPowerPills();

#endif /* end __MOVING_FUNC */