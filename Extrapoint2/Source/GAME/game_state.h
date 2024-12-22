#ifndef __GAME_STATE
#define __GAME_STATE

#import "GAME/drawing_func.h"

#define MAX_TIME_SECONDS 60
#define INITIAL_NUM_LIFES 1
#define MAX_NUM_LIFES 4
#define MAX_NUM_PILLS 240

#define BLINKY_CHASE_MODE 0
#define BLINKY_FRIGHTENED_MODE 1
#define BLINKY_INITIAL_SPEED 40 // From 40 to 100

extern uint16_t countdown;
extern uint16_t num_lifes;
extern uint16_t score;
extern uint16_t game_pause;
extern uint8_t blinkyMode;
extern uint8_t isBlinkyFreeFlag;
extern uint8_t timeBlinkyFrightened;
extern uint8_t blinkySpeed;

void startGame();
void setGamePause();
void removeGamePause();
void updateCountdown();
void removeOneLife();
void updateScore(uint16_t addValue);
void checkVictory();

#endif /* end __GAME_STATE */