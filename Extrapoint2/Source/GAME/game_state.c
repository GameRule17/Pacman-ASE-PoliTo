#import "game_state.h"

/* **************************** FUNCTION PROTOTYPES **************************** */
void setGamePause();
void removeGamePause();
void restartGame();
void updateCountdown();
void updateScore(uint16_t addValue);
void checkVictory();

/* **************************** GLOBAL VARIABLES **************************** */

uint16_t countdown = MAX_TIME_SECONDS;
uint16_t num_lifes = INITIAL_NUM_LIFES;
uint16_t score = 0;
uint16_t threshold = 1000;
uint16_t game_pause = 1;
uint16_t num_eated_pills = 0;
uint8_t pacman_movement_completed = 0;

/* ******************** GAME STATE FUNCTIONS ******************** */

void setGamePause() {
	disable_timer(0);
	disable_timer(1);
	game_pause = 1;
	drawPauseBox();
}

void removeGamePause() {
	enable_timer(0);
	enable_timer(1);
	game_pause = 0;
	drawBoard(0);
}

void restartGame() {
	clearGameOverScreen();
	drawBoard(1);
	setGamePause();
	enableINT0();
	countdown = MAX_TIME_SECONDS; // Reset countdown statistic
	drawTimeLeft();
}

void updateCountdown() {
	countdown--;
	if(countdown == 0) {
		disable_timer(0);
		disable_timer(1);
		num_lifes--;
		if(num_lifes == 0) {
			disable_RIT(); // Disable using all types of buttons
			drawGameEndedScreen(); // Game ended with no more lives left
		} else {
			disableINT0(); // No sense of pausing the game in game over screen
			enableKEY1(); // Make possible to click KEY1 to restart the game
			drawGameOverScreen(); // Game ended with at least 1 life left
		}
	} else {
		drawTimeLeft();
	}
}

void updateScore(uint16_t addValue) {
	score = score + addValue;
	
	// To manage adding a new life every 1000 points obtained
	if (score >= threshold) {
		num_lifes = num_lifes + 1;
		drawLives(X_POSITION_LIVES_IN_GAME, Y_POSITION_LIVES_IN_GAME);
		threshold = threshold + 1000;
	}
}

void checkVictory() {
	num_eated_pills++;
	if (num_eated_pills == MAX_NUM_PILLS) {
		disable_timer(0);
		disable_timer(1);
		disable_RIT(); // Disable using all types of buttons
		drawVictoryScreen();
	}
}
