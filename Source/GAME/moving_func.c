#include "GAME/moving_func.h"

int pacman_x = 14;
int pacman_y = 14;

void setPacman() {
	board[pacman_x][pacman_y] = PACMAN;
}

void generatePowerPills() {
	int randX, randY;
	int numPowerPills = 0;
	
	// Repeat ultil 6 standard pills aren't converted into power pills
	while (numPowerPills < NUM_POWER_PILLS) {
		randX = rand() % LENGTH; // Generating random X value from 0 to LENGTH=28
		randY = rand() % HEIGTH; // Generating random Y value from 0 to LENGTH=31
		
		// Check if that cell is a standard pill
		if (board[randX][randY] == STANDARD_PILL) {
			board[randX][randY] = POWER_PILL;
			numPowerPills++;
		}	
	}
}

// Function that moves Pacman
int movePacman(int direction) {
	int newX, prevX, newY, prevY;
	
	prevX = pacman_x;
	newX = pacman_x;
	prevY = pacman_y;
	newY = pacman_y;

    switch (direction) {
        case J_UP_KEY: // Up joystick key pressed
            newX = prevX-1;
            break;
        case J_DOWN_KEY: // Down joystick key pressed
            newX = prevX+1;
            break;
        case J_LEFT_KEY: // Left joystick key pressed
            newY = prevY-1;
            break;
        case J_RIGHT_KEY: // Right joystick key pressed
            newY = prevY+1;
            break;
        default:
            return 0; // Invalid direction
    }

    // Check if the new position is valid 
	// (no walls and no out of matrix's bounds
    if (newX >= 0 && newX < HEIGTH && newY >= 0 && newY < LENGTH && board[newX][newY] != WALL) {
        // Update matrix's values
        board[prevX][prevY] = VOID; // Free old position
		
		switch(board[newX][newY]){
			case TP_LEFT:
				newY = newY+LENGTH-2;
				board[newX][newY] = PACMAN; // Set new position
			break;
			case TP_RIGHT:
				newY = newY-LENGTH+2;
				board[newX][newY] = PACMAN; // Set new position
			break;
			default:
				board[newX][newY] = PACMAN; // Set new position
			break;
			
		}
		
		// Now draw also the move on the display
		Draw_Pacman_Move(newX, newY, prevX, prevY);
		
		pacman_x = newX;
		pacman_y = newY;
		
        return 1; // Movement done
    }

    return 0; // Movement not completed
}

