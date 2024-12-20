#include "GAME/moving_func.h"

/* **************************** FUNCTION PROTOTYPES **************************** */
void setPacman();
void tryGenerationPowerPills();
uint16_t movePacman(uint16_t direction);


/* **************************** GLOBAL VARIABLES **************************** */

uint16_t pacman_x = PACMAN_INITIAL_X;
uint16_t pacman_y = PACMAN_INITIAL_Y;

uint16_t direction = 0;

/* **************************** FUNCTION DEFINED **************************** */

void setPacman() {
	board[pacman_y][pacman_x] = PACMAN;
}

void tryGenerationPowerPills() {
	int xCoord, yCoord;
	
	static uint16_t numPowerPillsGenerated = 0;
	
	int temp = (get_timer_value(1) ^ get_RIT_value()) % 101;
	
	if((temp <= PROBABILITY_TRESHOLD) && (numPowerPillsGenerated < NUM_POWER_PILLS)) {
		srand(get_timer_value(1) ^ get_RIT_value() ^ MAGIC_RANDOM_NUMBER);
		xCoord = rand() % LENGTH;
		yCoord = rand() % HEIGTH;
		
		if(board[yCoord][xCoord] == STANDARD_PILL) {
			board[yCoord][xCoord] = POWER_PILL;
			drawPowerPill(xCoord, yCoord);
			numPowerPillsGenerated++;
		}
	}
}

uint16_t movePacman(uint16_t direction) {
	uint16_t new_Y, prev_Y, new_X, prev_X;
	uint16_t new_board_value;
	uint8_t sum_to_score;
	uint8_t flag_pill_eated = 0;
	
	// Pacman moves if and only if the game is NOT in PAUSE mode
	if(game_pause == 0) {
		prev_Y = pacman_y;
		new_Y = pacman_y;
		prev_X = pacman_x;
		new_X = pacman_x;

		switch (direction) {
			case J_UP_KEY: // Up joystick key pressed
				new_Y = prev_Y-1;
				break;
			case J_DOWN_KEY: // Down joystick key pressed
				new_Y = prev_Y+1;
				break;
			case J_LEFT_KEY: // Left joystick key pressed
				new_X = prev_X-1;
				break;
			case J_RIGHT_KEY: // Right joystick key pressed
				new_X = prev_X+1;
				break;
			default:
				return 0; // Invalid direction
		}
		
		new_board_value = board[new_Y][new_X];

		// Check if the new position is valid == no walls and no out of matrix's bounds
		if (new_Y >= 0 && new_Y < HEIGTH && new_X >= 0 && new_X < LENGTH && new_board_value != WALL) {
			
			// Update matrix's values
			switch(new_board_value){
				case TP_LEFT:
					// Teleport from LEFT to RIGHT
					new_X = new_X+LENGTH-2;
				break;
				case TP_RIGHT:
					// Teleport from RIGHT to LEFT
					new_X = new_X-LENGTH+2;
				break;
				case STANDARD_PILL:
					sum_to_score = 10;
					flag_pill_eated = 1;
				break;
				case POWER_PILL:
					sum_to_score = 50;
					flag_pill_eated = 1;
				break;
				default:
				break;
			}
			
			board[new_Y][new_X] = PACMAN; // Set new position
			board[prev_Y][prev_X] = VOID; // Null previous position
			
			// Now draw also the move on the display
			drawPacmanMove(new_Y, new_X, prev_Y, prev_X);
			
			// If a pill is eaten, update the new score and check victory
			if (flag_pill_eated == 1) {
				// Update and draw the new score 
				updateScore(sum_to_score);
				drawScore();
				
				checkVictory();
				flag_pill_eated = 0;
			}
			
			pacman_y = new_Y;
			pacman_x = new_X;
			
			return 1; // Movement done
		} else {
			// If a WALL is encountered, it's useless to continue trying going through it
			// Better stopping pacman movement
			direction = 0;
		}
	}
	
    return 0; // Movement not completed
}

