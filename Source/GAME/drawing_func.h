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
void drawLives(uint16_t initialX, uint16_t initialY);
void drawPowerPill(uint16_t xCoord, uint16_t yCoord);
void drawBoard(uint16_t drawAllBoardFlag);
void drawPacmanMove(uint16_t newY, uint16_t newX, uint16_t prevY, uint16_t prevX);
void drawGameOverScreen();
void clearGameOverScreen();
void drawGameEndedScreen();
void drawPauseBox();
void drawVictoryScreen();

#endif /* end __DRAWING_FUNC */