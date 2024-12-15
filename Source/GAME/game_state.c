#import "game_state.h"

int countdown = MAX_TIME_SECONDS;
int num_lifes = INITIAL_NUM_LIFES;
int score = 0;
int threshold = 1000;

void updateCountdown() {
	countdown--;
	if(countdown == 0) {
		disable_timer(0);
		num_lifes--;
		if(num_lifes == -1) {
			Draw_Game_Ended();
		} else {
			Draw_Game_Over_Screen();
		}
	} else {
		Draw_Time_Left();
	}
}

void addNewValueScore(int addValue) {
	score = score + addValue;
	
	// To manage adding a new life every 1000 points obtained
	if (score >= threshold) {
		num_lifes = num_lifes + 1;
		Draw_Lives(X_POSITION_LIVES_IN_GAME, Y_POSITION_LIVES_IN_GAME);
		threshold = threshold + 1000;
	}
}

