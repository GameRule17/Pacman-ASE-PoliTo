#import "GAME/drawing_func.h"

/* **************************** FUNCTION PROTOTYPES **************************** */

void drawWall(uint16_t current_X, uint16_t current_Y, uint16_t color);
void drawPoint(uint16_t current_X, uint16_t current_Y, uint16_t color);
void drawCircle(int center_X, int center_Y, int radius, int color);
void drawHeart(int center_X, int center_Y, int size, int color);
void drawRectWithBorder(uint16_t x0, uint16_t y0, uint16_t length, uint16_t depth, uint16_t fill_color, uint16_t border_color);

void drawTitle();
void drawScore();
void drawTimeLeft();
void drawLives(uint16_t initialX, uint16_t initialY);
void drawPowerPill(uint16_t xCoord, uint16_t yCoord);
void drawBoard(uint16_t drawAllBoardFlag);
void drawPacmanMove(uint16_t newY, uint16_t newX, uint16_t prevY, uint16_t prevX);
void drawGameOverScreen();
void clearGameOverScreen();
void drawGameEndedScreen();
void drawPauseBox();
void drawVictoryScreen();

/* **************************** GLOBAL VARIABLES **************************** */

/* ******************** GENERIC DRAW FUNCTIONS ******************** */

void drawWall(uint16_t current_X, uint16_t current_Y, uint16_t color){
	uint16_t i, j;
 
	for(i = 0; i < RATIO; i++){
		for(j = 0; j < RATIO; j++){
			LCD_SetPoint(current_X + i, current_Y + j, color);
		}
	}
}

void drawPoint(uint16_t current_X, uint16_t current_Y, uint16_t color){
	LCD_SetPoint(current_X + RATIO/2, current_Y + RATIO/2, color);
}

void drawCircle(int center_X, int center_Y, int radius, int color){
    int x = 0;
    int y = radius;
    int d = 1 - radius;
	int fillY;

    while (x <= y) {
        for (fillY = center_Y - y; fillY <= center_Y + y; fillY++) {
            drawPoint(center_X + x, fillY, color);
            drawPoint(center_X - x, fillY, color);
        }
        for (fillY = center_Y - x; fillY <= center_Y + x; fillY++) {
            drawPoint(center_X + y, fillY, color);
            drawPoint(center_X - y, fillY, color);
        }

        if (d < 0) {
            d += 2 * x + 3;
        } else {
            d += 2 * (x - y) + 5;
            y--;
        }
        x++;
    }
}

void drawHeart(int center_X, int center_Y, int size, int color) {
    int radius = size / 2;
    int half_size = size / 2;

    drawCircle(center_X - radius, center_Y - radius / 2, radius, color);
    drawCircle(center_X + radius, center_Y - radius / 2, radius, color); 

    int x, y;
    for (y = 0; y < size; y++) { 
        for (x = -size+1 + y; x <= size - y - 1; x++) {
            drawPoint(center_X + x, center_Y + y, color);
        }
    }
}

void drawRectWithBorder(uint16_t x0, uint16_t y0, uint16_t length, uint16_t depth, uint16_t fill_color, uint16_t border_color) {
    uint16_t x1 = x0 + length - 1;
    uint16_t y1 = y0 + depth - 1;

    uint16_t i;

    LCD_DrawLine(x0, y0, x1, y0, border_color);
	
    for (i = y0 + 1; i < y1; i++) {
        LCD_DrawLine(x0, i, x0, i, border_color);
        LCD_DrawLine(x0 + 1, i, x1 - 1, i, fill_color);
        LCD_DrawLine(x1, i, x1, i, border_color);
    }
	
	LCD_DrawLine(x0, y1, x1, y1, border_color);
}

/* ******************** GAME DRAW FUNCTIONS ******************** */

void drawTitle() {
	GUI_Text(X_GAME_OVER_IN,Y_GAME_OVER_IN,(uint8_t *) "GAME OVER IN      SCORE", Blue, Black);
	
	GUI_Text(X_REMAINING_LIVES,Y_REMAINING_LIVES,(uint8_t *) "REMAINING LIVES", Blue, Black);
}

void drawScore() {
	/*
		Variable score is declared as int, but GUI_Text func requires a string as input
		Next code is used to convert the int value into uint16_t
	*/
	uint16_t score_conv_string[12];
	sprintf((char *)score_conv_string, "%d", score);
	
	GUI_Text(X_SCORE,Y_SCORE,(uint8_t *) score_conv_string, Blue, Black);
}

void drawTimeLeft() {
	uint16_t count_down_conv_string[12];
	sprintf((char *)count_down_conv_string, "%d    ", countdown);
	
	GUI_Text(X_TIME_LEFT,Y_TIME_LEFT,(uint8_t *) count_down_conv_string, Blue, Black);
}

void drawLives(uint16_t initialX, uint16_t initialY) {
	int nextHeartDistance = 16;
	int i = 0;
	
	for(i=0; i<MAX_NUM_LIVES; i++) {
		if (i<numLives) {
			// For the actual lives a red heart is showed
			drawHeart(initialX,initialY,7,Red);
		} else {
			// Otherwise a black heart is showed, to clear the screen
			drawHeart(initialX,initialY,7,Black);
		}
		initialX = initialX + nextHeartDistance;
	}
}

void drawPowerPill(uint16_t xCoord, uint16_t yCoord) {
	drawCircle(alignCoordX(xCoord), alignCoordY(yCoord), POWER_PILL_RADIUS, Magenta);
}

/*
	Main drawing function, depending on drawAllBoardFlag:
		when drawAllBoardFlag = 1 -> the ENTIRE board is drawn
			 drawAllBoardFlag = 0 -> only the box behind the pause is re-drawn
	this is done for optimizing purposes
*/

void drawBoard(uint16_t drawAllBoardFlag){
    uint16_t i, j, current_value;
	uint16_t x_pos, y_pos;
	uint16_t newStartingJ = 0, newStartingI = 0;
	uint16_t addPaddingI = 0;
	
	static uint8_t firstBoardGenerated = 0;
	
	drawTitle();
	drawScore();
	drawTimeLeft();
	drawLives(X_POSITION_LIVES_IN_GAME, Y_POSITION_LIVES_IN_GAME);
	
	if (firstBoardGenerated == 0) {
		setPacman();
		firstBoardGenerated = 1;
	}
	
	if (drawAllBoardFlag == 0) {
		newStartingJ = 7;
		newStartingI = 9;
		addPaddingI = 2;
	}
 
    for(i = newStartingI; i < HEIGTH - newStartingI - addPaddingI; i++){
        for(j = newStartingJ; j < LENGTH - newStartingJ; j++){
            current_value = board[i][j];
			x_pos = alignCoordX(j);
			y_pos = alignCoordY(i);
			
			if (drawAllBoardFlag == 0) {
				drawWall(x_pos, y_pos, Black);
			}
           
            switch(current_value){ 
                case WALL:
                    drawWall(x_pos, y_pos, Blue);
                break;
                case STANDARD_PILL:
                    drawPoint(x_pos, y_pos, Magenta);
				break;
				case POWER_PILL:
                    drawCircle(x_pos, y_pos, POWER_PILL_RADIUS, Magenta);
				break;
				case PACMAN:
					drawCircle(x_pos, y_pos, PACMAN_RADIUS, Yellow);
				break;
                default:
                break;
            }
        }
    }
}

void drawPacmanMove(uint16_t newY, uint16_t newX, uint16_t prevY, uint16_t prevX) {
	// Draw black on the previous position
	drawCircle(alignCoordX(prevX), alignCoordY(prevY), PACMAN_RADIUS, Black);
	
	// Draw pacman on the new position
    drawCircle(alignCoordX(newX), alignCoordY(newY), PACMAN_RADIUS, Yellow);
}


void drawGameOverScreen() {
	LCD_Clear(Black);
	
	GUI_Text(X_GAME_OVER,Y_GAME_OVER,(uint8_t *) "GAME OVER", Blue, Black);
	
	GUI_Text(X_REMAINING_LIVES_GAMEOVER,Y_REMAINING_LIVES_GAMEOVER,(uint8_t *) "REMAINING LIVES", Blue, Black);
	drawLives(X_POSITION_LIVES_IN_GAMEOVER, Y_POSITION_LIVES_IN_GAMEOVER);
	GUI_Text(X_PRESS_KEY1_TO_RESTART,Y_PRESS_KEY1_TO_RESTART,(uint8_t *) "Press KEY1 to Restart", Blue, Black);
}

void clearGameOverScreen() {
	// Only a rect over the Game Over texts is drawn
	drawRectWithBorder(35,130,170,100,Black,Black);
}

void drawGameEndedScreen() {
	LCD_Clear(Black);
	
	GUI_Text(X_GAME_OVER, Y_GAME_OVER,(uint8_t *) "GAME OVER", Blue, Black);
	GUI_Text(X_NO_REMAINING_LIVES, Y_NO_REMAINING_LIVES,(uint8_t *) "NO REMAINING LIVES", Blue, Black);
	GUI_Text(X_YOU_LOST, Y_YOU_LOST,(uint8_t *) "YOU LOST!", Blue, Black);
}

void drawPauseBox() {
	drawRectWithBorder(64, 104, 112, 88, Black, Red);
	// x and y were found simply testing different positions in order to look it pretty
	GUI_Text(X_GAME_PAUSED, Y_GAME_PAUSED,(uint8_t *) "GAME PAUSED", Red, Black);
	GUI_Text(X_PRESS_INT0, Y_PRESS_INT0,(uint8_t *) "Press INT0", Red, Black);
	GUI_Text(X_TO_RESUME, Y_TO_RESUME,(uint8_t *) "to resume", Red, Black);
}

void drawVictoryScreen() {
	LCD_Clear(Black);
	
	GUI_Text(X_VICTORY, Y_VICTORY,(uint8_t *) "VICTORY!", Blue, Black);
}
