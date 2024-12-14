#import "game_state.h"

int countdown = MAX_TIME_SECONDS;

void updateCountdown() {
	countdown--;
	if(countdown == 0) {
		Draw_Game_Over_Screen();
		disable_timer(0);
	} else {
		Draw_Time_Left();
	}
}