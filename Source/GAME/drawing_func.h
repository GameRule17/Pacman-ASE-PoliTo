#ifndef __DRAWING_FUNC
#define __DRAWING_FUNC

#import "GAME/game_matrix.h"
#import "GLCD.h"

void Draw_Wall(int current_X, int current_Y, int color);
void Draw_Point(int current_X, int current_Y, int color);
void Draw_Circle(int center_X, int center_Y, int radius, int color);

void Draw_Matrix();
void Draw_Pacman_Move(int newX, int newY, int prevX, int prevY);

#endif /* end __DRAWING_FUNC */