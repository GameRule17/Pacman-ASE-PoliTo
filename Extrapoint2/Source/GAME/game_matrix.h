#ifndef __GAME_MATRIX
#define __GAME_MATRIX

#include "LPC17xx.h"

#define LENGTH 28
#define HEIGTH 31
#define RATIO 8 // Every point in the matrix is represented as 8x8pixels in the real board

#define SIDE_PADDING 8 // #pixel dist from the side edge
#define UPPER_PADDING 32 // #pixel dist from the upper edge

// Items represented in the game matrix as this number codes
#define VOID 0
#define WALL 1
#define STANDARD_PILL 2
#define POWER_PILL 3
#define TP_LEFT 4
#define TP_RIGHT 5
#define PACMAN 9

#define PACMAN_INITIAL_X 14
#define PACMAN_INITIAL_Y 14

#define NUM_POWER_PILLS 6

extern uint8_t board[HEIGTH][LENGTH];

// Functions to align coordinates from matrix[y][x] to real board
uint16_t alignCoordX (uint16_t x);
uint16_t alignCoordY (uint16_t y);

#endif /* end __GAME_MATRIX */