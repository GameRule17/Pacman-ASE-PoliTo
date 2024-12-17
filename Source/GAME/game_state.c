#import "game_state.h"

int countdown = MAX_TIME_SECONDS;
int num_lifes = INITIAL_NUM_LIFES;
int score = 0;
int threshold = 1000;
int game_pause = 1;
int num_eated_pills = 0;

/* ******************** TESTING PURPOSE FUNCTIONS ******************** */
//void countStandardPills() {
//	int i, j;
//	for(i = 0; i < HEIGTH; i++){
//        for(j = 0; j < LENGTH; j++){
//			if(board[i][j] == STANDARD_PILL) {
//				num_standard_pills++;
//			}
//		}
//	}
//}

/* ******************** GAME STATE FUNCTIONS ******************** */

void setGamePause() {
	game_pause = 1;
	Draw_Pause_Box();
	disable_timer(0);
	disable_timer(1);
}

void removeGamePause() {
	game_pause = 0;
	Draw_Board(0);
	enable_timer(0);
	enable_timer(1);
}

void restartGame() {
	Clear_Game_Over_Screen();
	Draw_Board(1);
	setGamePause();
	enableINT0();
	// reset all game statistics
}

void updateCountdown() {
	countdown--;
	if(countdown == 0) {
		disable_timer(0);
		num_lifes--;
		if(num_lifes == -1) {
			disable_RIT(); // Disable using all types of buttons
			Draw_Game_Ended(); // Because game ended with no more lives left
		} else {
			Draw_Game_Over_Screen(); // Game ended with at least 1 life left
			enableKEY1(); // Make possible to click KEY1 to restart the game
			disableINT0(); // No sense of pausing the game in game over screen
		}
	} else {
		Draw_Time_Left();
	}
}

void updateScoreAndCheckVictory(int addValue) {
	score = score + addValue;
	
	// To manage adding a new life every 1000 points obtained
	if (score >= threshold) {
		num_lifes = num_lifes + 1;
		Draw_Lives(X_POSITION_LIVES_IN_GAME, Y_POSITION_LIVES_IN_GAME);
		threshold = threshold + 1000;
	}
	
	// Check Victory
	num_eated_pills++;
	if (num_eated_pills == MAX_NUM_PILLS) {
		game_pause = 1;
		disable_RIT(); // Disable using all types of buttons
		Draw_Victory_Screen();
	}
}

