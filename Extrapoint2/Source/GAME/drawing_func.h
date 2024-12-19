#ifndef __DRAWING_FUNC
#define __DRAWING_FUNC

#import "GAME/game_matrix.h"
#import "GLCD.h"
#import "GAME/game_state.h"

#define PACMAN_RADIUS 3 // Radius of circle representing pacman
#define POWER_PILL_RADIUS 2 // Radius of circle representing power pills

/* ******************************* POSITION FOR OBJECTS ******************************* */

#define X_POSITION_LIVES_IN_GAME 85
#define Y_POSITION_LIVES_IN_GAME 300
#define X_POSITION_LIVES_IN_GAMEOVER 85
#define Y_POSITION_LIVES_IN_GAMEOVER 170

#define SINGLE_CHARACTER_SIZE 8

#define DISPLAY_WIDTH 240
#define DISPLAY_HEIGTH 320

#define TEXT_HEIGHT 20

#define DISPLAY_CENTER_Y_COORD (DISPLAY_HEIGTH-TEXT_HEIGHT)/2

// GAME OVER Text screen positions
#define GAME_OVER_TEXT_SIZE 9*SINGLE_CHARACTER_SIZE
#define X_GAME_OVER (DISPLAY_WIDTH-GAME_OVER_TEXT_SIZE)/2
#define Y_GAME_OVER ((DISPLAY_HEIGTH-TEXT_HEIGHT)/2)-20

// NO REMAINING LIVES Text screen positions
#define NO_REMAINING_LIVES_TEXT_SIZE 18*SINGLE_CHARACTER_SIZE
#define X_NO_REMAINING_LIVES (DISPLAY_WIDTH-NO_REMAINING_LIVES_TEXT_SIZE)/2
#define Y_NO_REMAINING_LIVES DISPLAY_CENTER_Y_COORD

// YOU LOST Text screen positions
#define YOU_LOST_TEXT_SIZE 8*SINGLE_CHARACTER_SIZE
#define X_YOU_LOST (DISPLAY_WIDTH-YOU_LOST_TEXT_SIZE)/2
#define Y_YOU_LOST DISPLAY_CENTER_Y_COORD+20

// GAME PAUSED Text screen positions
#define GAME_PAUSED_SIZE 11*SINGLE_CHARACTER_SIZE
#define X_GAME_PAUSED (DISPLAY_WIDTH-GAME_PAUSED_SIZE)/2
#define Y_GAME_PAUSED DISPLAY_CENTER_Y_COORD-35

// PRESS INT0 Text screen positions
#define PRESS_INT0_SIZE 10*SINGLE_CHARACTER_SIZE
#define X_PRESS_INT0 (DISPLAY_WIDTH-PRESS_INT0_SIZE)/2
#define Y_PRESS_INT0 DISPLAY_CENTER_Y_COORD-5

// TO RESUME Text screen positions
#define TO_RESUME_SIZE 9*SINGLE_CHARACTER_SIZE
#define X_TO_RESUME (DISPLAY_WIDTH-TO_RESUME_SIZE)/2
#define Y_TO_RESUME DISPLAY_CENTER_Y_COORD+15

// REMAINING LIVES Text screen positions
#define REMAINING_LIVES_SIZE 15*SINGLE_CHARACTER_SIZE
#define X_REMAINING_LIVES (DISPLAY_WIDTH-REMAINING_LIVES_SIZE)/2
#define Y_REMAINING_LIVES DISPLAY_CENTER_Y_COORD

// PRESS KEY1 TO RESTART Text screen positions
#define PRESS_KEY1_TO_RESTART_SIZE 21*SINGLE_CHARACTER_SIZE
#define X_PRESS_KEY1_TO_RESTART (DISPLAY_WIDTH-PRESS_KEY1_TO_RESTART_SIZE)/2
#define Y_PRESS_KEY1_TO_RESTART DISPLAY_CENTER_Y_COORD+50

/* ******************************* PUBLIC FUNCTIONS ******************************* */

void drawScore();
void drawTimeLeft();
void drawLives(uint16_t initialX, uint16_t initialY);
void drawPowerPill(uint16_t xCoord, uint16_t yCoord);
void drawBoard(uint16_t drawAllBoardFlag);
void drawPacmanMove(uint16_t newY, uint16_t newX, uint16_t prevY, uint16_t prevX);
void drawBlinkyMove(uint16_t newY, uint16_t newX, uint16_t prevY, uint16_t prevX, uint8_t prevValue);
void drawGameOverScreen();
void clearGameOverScreen();
void drawGameEndedScreen();
void drawPauseBox();
void drawVictoryScreen();

#endif /* end __DRAWING_FUNC */