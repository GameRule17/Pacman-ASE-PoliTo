#ifndef __DRAWING_FUNC
#define __DRAWING_FUNC

#import "GAME/game_matrix.h"
#import "GLCD.h"
#import "GAME/game_state.h"

#define PACMAN_RADIUS 3 // Radius of circle representing pacman
#define POWER_PILL_RADIUS 2 // Radius of circle representing power pills

#define X_POSITION_LIVES_IN_GAME 85
#define Y_POSITION_LIVES_IN_GAME 300
#define X_POSITION_LIVES_IN_GAMEOVER 85
#define Y_POSITION_LIVES_IN_GAMEOVER 170

/* *************** PUBLIC FUNCTIONS *************** */

void drawScore();
void drawTimeLeft();
void drawLives(int initialX, int initialY);
void drawPowerPill(int xCoord, int yCoord);
void drawBoard(int drawAllBoardFlag);
void drawPacmanMove(int newY, int newX, int prevY, int prevX);
void drawGameOverScreen();
void clearGameOverScreen();
void drawGameEndedScreen();
void drawPauseBox();
void drawVictoryScreen();

#endif /* end __DRAWING_FUNC */