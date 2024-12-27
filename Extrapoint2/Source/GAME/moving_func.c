#include "GAME/moving_func.h"

/* **************************** FUNCTION PROTOTYPES **************************** */
void setPacman();
void setBlinky();
void changeSRand();
void tryGenerationPowerPills();
uint16_t movePacman(uint16_t direction);
int calculateWeightedDistance(uint16_t pacman_X, uint16_t pacman_Y, uint16_t blinky_X, uint16_t blinky_Y);
void moveBlinky();
void freeBlinkyFromCage();
uint8_t checkCollision();

/* **************************** GLOBAL VARIABLES **************************** */

uint16_t pacman_x = PACMAN_INITIAL_X;
uint16_t pacman_y = PACMAN_INITIAL_Y;

uint16_t blinky_x = BLINKY_INITIAL_X;
uint16_t blinky_y = BLINKY_INITIAL_Y;

uint16_t direction = DIRECTION_STOP;
uint8_t previousBlinkyCellValue = STANDARD_PILL;

/* **************************** FUNCTION DEFINED **************************** */

void setPacman() {
	board[pacman_y][pacman_x] = PACMAN;
}

void setBlinky() {
	blinky_x = BLINKY_INITIAL_X;
	blinky_y = BLINKY_INITIAL_Y;
	board[blinky_y][blinky_x] = BLINKY;
	isBlinkyFreeFlag = 0; // Need to do free Blinky animation
}

void changeSRand() {
	srand(get_timer_value(1) ^ get_timer_value(2) ^ get_timer_value(3) ^ get_RIT_value() ^ MAGIC_RANDOM_NUMBER);
}

void tryGenerationPowerPills() {
	uint16_t xCoord, yCoord;
	static uint16_t numPowerPillsGenerated = 0;
	
	int temp = (get_timer_value(1) ^ get_RIT_value()) % 101;
	
	if((temp <= PROBABILITY_TRESHOLD_PILLS) && (numPowerPillsGenerated < NUM_POWER_PILLS)) {
		changeSRand();
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
	uint16_t newBoardValue;
	uint8_t sumToScore;
	uint8_t flagPillEated = 0;
	
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
		
		newBoardValue = board[new_Y][new_X];

		// Check if the new position is valid == no walls and no out of matrix's bounds
		if (new_Y >= 0 && new_Y < HEIGTH && 
			new_X >= 0 && new_X < LENGTH && 
			newBoardValue != WALL &&
			newBoardValue != CAGE_DOOR) {
			
			// Update matrix's values
			switch(newBoardValue){
				case TP_LEFT:
					// Teleport from LEFT to RIGHT
					new_X = new_X+LENGTH-2;
				break;
				case TP_RIGHT:
					// Teleport from RIGHT to LEFT
					new_X = new_X-LENGTH+2;
				break;
				case STANDARD_PILL:
					sumToScore = 10;
					flagPillEated = 1;
				break;
				case POWER_PILL:
					sumToScore = 50;
					soundToPlay = SOUND_SUPER_PILL_EATED;
					blinkyMode = BLINKY_FRIGHTENED_MODE;
					timeBlinkyFrightened = 0;
					flagPillEated = 1;
				break;
				default:
				break;
			}
			
			board[new_Y][new_X] = PACMAN; // Set new position
			board[prev_Y][prev_X] = VOID; // Null previous position
			
			// Now draw also the move on the display
			drawPacmanMove(new_Y, new_X, prev_Y, prev_X);
			
			// If a pill is eaten, update the new score and check victory
			if (flagPillEated == 1) {
				updateScore(sumToScore);
				checkVictory();
				flagPillEated = 0;
			}
			
			pacman_y = new_Y;
			pacman_x = new_X;
			
			return 1; // Movement done
		} else {
			// If a WALL is encountered, it's useless to continue trying going through it
			// Better stopping pacman movement
			direction = DIRECTION_STOP;
		}
	}
	
    return 0; // Movement not completed
}

/*
	Heuristic used to calculate distance between Pacman and Blinky
	it uses both manhattan and euclidean distance with balanced weights.
	In my opinion, it was too heavy to implement an A* search.
*/

int calculateWeightedDistance(uint16_t pacman_X, uint16_t pacman_Y, uint16_t blinky_X, uint16_t blinky_Y) {
	int manhattan = abs(pacman_X - blinky_X) + abs(pacman_Y - blinky_Y);
    double euclidean = sqrt(pow((pacman_X - blinky_X), 2) + pow((pacman_Y - blinky_Y), 2));
    return 0.5 * manhattan + 0.5 * euclidean; // Balanced weights
}

void freeBlinkyFromCage() {
	static int i = -30; // Blinky stays 3 second stopped before exiting the cage
	switch(i) {
		case 0:
			// Move 1 cell up blinky
			board[blinky_y][blinky_x] = VOID;
			board[blinky_y-1][blinky_x] = BLINKY;
			drawBlinkyMove(blinky_y-1, blinky_x, blinky_y, blinky_x, VOID);
			blinky_y--;
			i++;
		break;
		case 1:
			// Open cage
			board[CAGE_DOOR_1_Y][CAGE_DOOR_1_X] = VOID;
			board[CAGE_DOOR_2_Y][CAGE_DOOR_2_X] = VOID;
			drawElementOnBoard(CAGE_DOOR_1_X, CAGE_DOOR_1_Y, VOID);
			drawElementOnBoard(CAGE_DOOR_2_X, CAGE_DOOR_2_Y, VOID);
			i++;
		break;
		case 2:
			// Move 1 cell up blinky
			board[blinky_y][blinky_x] = VOID;
			board[blinky_y-1][blinky_x] = BLINKY;
			drawBlinkyMove(blinky_y-1, blinky_x, blinky_y, blinky_x, VOID);
			blinky_y--;
			i++;
		break;
		case 3:
			// Move 1 cell up blinky
			board[blinky_y][blinky_x] = VOID;
			board[blinky_y-1][blinky_x] = BLINKY;
			drawBlinkyMove(blinky_y-1, blinky_x, blinky_y, blinky_x, CAGE_DOOR);
			blinky_y--;
			i++;
		break;
		case 4:
			// Close cage
			board[CAGE_DOOR_1_Y][CAGE_DOOR_1_X] = CAGE_DOOR;
			board[CAGE_DOOR_2_Y][CAGE_DOOR_2_X] = CAGE_DOOR;
			drawElementOnBoard(CAGE_DOOR_1_X, CAGE_DOOR_1_Y, CAGE_DOOR);
			drawElementOnBoard(CAGE_DOOR_2_X, CAGE_DOOR_2_Y, CAGE_DOOR);
			i++;
		break;
		case 5:
			// Blinky is now free
			isBlinkyFreeFlag = 1;
			// Reset
			i = -30;
		break;
		default:
			// Wait 3 seconds and start exit animation
			i++;
		break;
	}
}

void moveBlinky() {
	uint16_t bestX;
	uint16_t bestY;
	int localWeightedDistance;
	uint16_t bestWeightedDistance = 999;
	uint16_t worstWeightedDistance = 0;
	
	uint8_t i;
	
	static uint16_t previousX = 0;
	static uint16_t previousY = 0;
	
	uint16_t vectorOfMovements[4][2] = {
		{blinky_x, blinky_y+1}, // -> Down move
		{blinky_x+1, blinky_y}, // -> Right move
		{blinky_x, blinky_y-1}, // -> Up move
		{blinky_x-1, blinky_y}, // -> Left move
	};
	
	/*
		Check for all the possible combination of movements
		if they are valid == no walls and no out of matrix's bounds
		For the one valid, calculate the Weighted Distance and save the best coords 
	*/
	for (i = 0; i<4; i++) {
		
		uint16_t iX = vectorOfMovements[i][0];
		uint16_t iY = vectorOfMovements[i][1];
		
		if (iY >= 0 && iY < HEIGTH &&        // No out of HEIGTH bounds
			iX >= 0 && iX < LENGTH &&        // No out of LENGTH bounds
			board[iY][iX] != WALL &&         // Wall not encountered
			board[iY][iX] != CAGE_DOOR &&    // Cage-door is like a wall
			// In this implementation Blinky can't use teleports
			!(iY == TP_LEFT_ENTRANCE_Y && iX == TP_LEFT_ENTRANCE_X) &&
			!(iY == TP_RIGHT_ENTRANCE_Y && iX == TP_RIGHT_ENTRANCE_X)) {
			
			localWeightedDistance = calculateWeightedDistance(pacman_x, pacman_y, iX, iY);
			
			if (blinkyMode == BLINKY_CHASE_MODE) {
				/* In CHASE MODE the optimal movement is the lowest distance */
				
				// This is done to prefer every other movement besides going back in the previous position
				// If no other movement is available, then Blinky will move back
				if (previousX == iX && previousY == iY) {
					localWeightedDistance = localWeightedDistance + 100; // Negative factor
				}
				
				if (localWeightedDistance < bestWeightedDistance) {
					bestWeightedDistance = localWeightedDistance;
					bestX = iX;
					bestY = iY;
				}
			} else {
				/* In FRIGHTENED MODE the optimal movement is the highest distance */
				
				// This is done to prefer every other movement besides going back in the previous position
				// If no other movement is available, then Blinky will move back
				if (previousX == iX && previousY == iY) {
					localWeightedDistance = localWeightedDistance - 100; // Negative factor
				}
				
				if (localWeightedDistance >= worstWeightedDistance) {
					worstWeightedDistance = localWeightedDistance;
					bestX = iX;
					bestY = iY;
				}
			}
		}	
	}
	
	// Draw the move
	drawBlinkyMove(bestY, bestX, blinky_y, blinky_x, previousBlinkyCellValue);
		
	// Save the move on the matrix board
	board[blinky_y][blinky_x] = previousBlinkyCellValue;	// Restore previous position value
	previousBlinkyCellValue = board[bestY][bestX]; 			// Save position value for next movement
	board[bestY][bestX] = BLINKY; 							// Set new blinky's position
	
	previousX = blinky_x;
	previousY = blinky_y;
	
	blinky_y = bestY;
	blinky_x = bestX;
}

uint8_t checkCollision() {
	// Check if Pacman and Blinky collide
	if (blinky_y == pacman_y && blinky_x == pacman_x) {
		// Set new Blinky's position on board
		setBlinky();
		// Reset Pacman position to resolve overlap of objects
		board[pacman_y][pacman_x] = PACMAN;
		// Update previousBlinkyCellValue 
		previousBlinkyCellValue = board[CAGE_EXIT_Y][CAGE_EXIT_X];
		
		// Draw Pacman and Blinky with new position
		drawBlinkyMove(BLINKY_INITIAL_Y, BLINKY_INITIAL_X, blinky_y, blinky_x, VOID);
		drawElementOnBoard(pacman_x, pacman_y, PACMAN);
		
		if (blinkyMode == BLINKY_CHASE_MODE) {
			removeOneLife();
		} else {
			updateScore(100);
			blinkyMode = BLINKY_CHASE_MODE;
		}
		return 1; // There was a collision
	}
	return 0; // No collision happened
}