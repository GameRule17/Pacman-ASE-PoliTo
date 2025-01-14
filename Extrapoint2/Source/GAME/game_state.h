#ifndef __GAME_STATE
#define __GAME_STATE

#import "GAME/drawing_func.h"
#import "audio/music.h"

#define MAX_TIME_SECONDS 60
#define INITIAL_NUMLIVES 1
#define MAX_NUMLIVES 4
#define MAX_NUM_PILLS 240

#define BLINKY_CHASE_MODE 0
#define BLINKY_FRIGHTENED_MODE 1
#define BLINKY_INITIAL_TICKS_MOVEMENT 20

extern uint16_t countdown;
extern uint16_t numLives;
extern uint16_t score;
extern uint16_t gamePause;
extern uint8_t blinkyMode;
extern uint8_t isBlinkyFreeFlag;
extern uint8_t timeBlinkyFrightened;

void startGame();
void setGamePause();
void removeGamePause();
void updateCountdown();
void removeOneLife();
void updateScore(uint16_t addValue);
void checkVictory();

#endif /* end __GAME_STATE */