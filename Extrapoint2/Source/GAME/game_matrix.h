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
#define CAGE_DOOR 6
#define BLINKY 8
#define PACMAN 9

#define PACMAN_INITIAL_X 6
#define PACMAN_INITIAL_Y 26

#define BLINKY_INITIAL_X 14
#define BLINKY_INITIAL_Y 14

#define NUM_POWER_PILLS 6

#define CAGE_DOOR_1_X 13
#define CAGE_DOOR_1_Y 12
#define CAGE_DOOR_2_X 14
#define CAGE_DOOR_2_Y 12
#define CAGE_EXIT_X 14
#define CAGE_EXIT_Y 11
#define TP_LEFT_ENTRANCE_X 2
#define TP_LEFT_ENTRANCE_Y 16
#define TP_RIGHT_ENTRANCE_X 25
#define TP_RIGHT_ENTRANCE_Y 16

extern uint8_t board[HEIGTH][LENGTH];

// Functions to align coordinates from matrix[y][x] to real board
uint16_t alignCoordX (uint16_t x);
uint16_t alignCoordY (uint16_t y);

#endif /* end __GAME_MATRIX */