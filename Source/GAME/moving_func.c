#include "GAME/moving_func.h"

int pacman_x = PACMAN_INITIAL_X;
int pacman_y = PACMAN_INITIAL_Y;

int direction = 0;

void setPacman() {
	board[pacman_y][pacman_x] = PACMAN;
}

void generatePowerPills() {
	int randX, randY;
	int numPowerPills = 0;
	
	// Repeat until 6 standard pills aren't converted into power pills
	while (numPowerPills < NUM_POWER_PILLS) {
		randX = rand() % LENGTH; // Generating random X value from 0 to LENGTH=28
		randY = rand() % HEIGTH; // Generating random Y value from 0 to LENGTH=31
		
		// Check if that cell is a standard pill
		if (board[randY][randX] == STANDARD_PILL) {
			board[randY][randX] = POWER_PILL;
			numPowerPills++;
		}	
	}
}

// Function that moves Pacman
int movePacman(int direction) {
	int new_Y, prev_Y, new_X, prev_X;
	int new_board_value;
	
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

    // Check if the new position is valid 
	// (no walls and no out of matrix's bounds
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
				addNewValueScore(10);
				// Draw the new score
				Draw_Score();
			break;
			case POWER_PILL:
				addNewValueScore(50);
				// Draw the new score
				Draw_Score();
			break;
			default:
			break;
			
		}
		
		board[new_Y][new_X] = PACMAN; // Set new position
		
		// Now draw also the move on the display
		Draw_Pacman_Move(new_Y, new_X, prev_Y, prev_X);
		
		pacman_y = new_Y;
		pacman_x = new_X;
		
        return 1; // Movement done
    } else {
		// If a WALL is encountered, it's useless to continue trying going through it
		// Better stopping pacman movement
		direction = 0;
	}

    return 0; // Movement not completed
}

