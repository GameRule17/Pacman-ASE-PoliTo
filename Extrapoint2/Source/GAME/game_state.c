#import "game_state.h"

/* **************************** FUNCTION PROTOTYPES **************************** */
void startGame();
void setGamePause();
void removeGamePause();
void updateCountdown();
void removeOneLife();
void updateScore(uint16_t addValue);
void checkVictory();

/* **************************** GLOBAL VARIABLES **************************** */

uint16_t countdown = MAX_TIME_SECONDS;
uint16_t numLives = INITIAL_numLives;
uint16_t score = 0;
uint16_t gamePause = 1;

uint8_t isBlinkyFreeFlag = 0;
uint8_t blinkyMode = BLINKY_CHASE_MODE;
uint8_t timeBlinkyFrightened = 0;
uint8_t blinkySpeed = BLINKY_INITIAL_SPEED;

/* ******************** GAME STATE FUNCTIONS ******************** */
void startGame() {
	drawBoard(1);
	setGamePause();
}

void setGamePause() {
	disable_timer(0);
	disable_timer(1);
	gamePause = 1;
	drawPauseBox();
}

void removeGamePause() {
	enable_timer(0);
	enable_timer(1);
	gamePause = 0;
	drawBoard(0);
}

void updateCountdown() {
	countdown--;
	if(countdown == 0) {
		disable_timer(0);
		disable_timer(1);
		disable_RIT(); // Disable using all types of buttons
		drawGameEndedScreen(); // Game ended
	} else {
		//drawTimeLeft();
		// This is now done through CAN
	}
}

void removeOneLife() {
	numLives--;
	if(numLives == 0) {
		// Game ended
		gamePause = 1;
		disable_timer(0);
		disable_timer(1);
		disable_RIT(); // Disable using all types of buttons
		drawGameEndedScreen();
	} else {
		soundToPlay = SOUND_LIFE_LOSED;
		//drawLives(X_POSITION_LIVES_IN_GAME, Y_POSITION_LIVES_IN_GAME);
		// This is now done through CAN
	}
}

void updateScore(uint16_t addValue) {
	static uint16_t threshold = 1000;
	
	score = score + addValue;
	
	// To manage adding a new life every 1000 points obtained
	if (score >= threshold) {
		numLives = numLives + 1;
		soundToPlay = SOUND_LIFE_GAINED;
		//drawLives(X_POSITION_LIVES_IN_GAME, Y_POSITION_LIVES_IN_GAME);
		// This is now done through CAN
		threshold = threshold + 1000;
	}
	
	//drawScore();
	// This is now done through CAN
}

void checkVictory() {
	static uint16_t num_eated_pills = 0;
	
	num_eated_pills++;
	if (num_eated_pills == MAX_NUM_PILLS) {
		disable_timer(0);
		disable_timer(1);
		disable_RIT(); // Disable using all types of buttons
		drawVictoryScreen();
	}
}
