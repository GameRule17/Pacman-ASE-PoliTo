#import "GAME/drawing_func.h"
#include <stdio.h> /*for sprintf*/

int firstBoardGenerated = 0;

/* ******************** GENERIC DRAW FUNCTIONS ******************** */

void Draw_Wall(int current_X, int current_Y, int color){
	int i, j;
 
	for(i = 0; i < RATIO; i++){
		for(j = 0; j < RATIO; j++){
			LCD_SetPoint(current_X + i, current_Y + j, color);
		}
	}
}

void Draw_Point(int current_X, int current_Y, int color){
	LCD_SetPoint(current_X + 4, current_Y + 4, color);
}

void Draw_Circle(int center_X, int center_Y, int radius, int color){
    int x = 0;
    int y = radius;
    int d = 1 - radius;
	int fillY;

    while (x <= y) {
        for (fillY = center_Y - y; fillY <= center_Y + y; fillY++) {
            Draw_Point(center_X + x, fillY, color);
            Draw_Point(center_X - x, fillY, color);
        }
        for (fillY = center_Y - x; fillY <= center_Y + x; fillY++) {
            Draw_Point(center_X + y, fillY, color);
            Draw_Point(center_X - y, fillY, color);
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

void Draw_Heart(int center_X, int center_Y, int size, int color) {
    int radius = size / 2;
    int half_size = size / 2;

    Draw_Circle(center_X - radius, center_Y - radius / 2, radius, color);
    Draw_Circle(center_X + radius, center_Y - radius / 2, radius, color); 

    int x, y;
    for (y = 0; y < size; y++) { 
        for (x = -size+1 + y; x <= size - y - 1; x++) {
            Draw_Point(center_X + x, center_Y + y, color);
        }
    }
}

void LCD_FillRectWithBorder(uint16_t x0, uint16_t y0, uint16_t length, uint16_t depth, uint16_t fill_color, uint16_t border_color) {
    uint16_t x1 = x0 + length - 1;
    uint16_t y1 = y0 + depth - 1;

    uint16_t i;

    LCD_DrawLine(x0, y0, x1, y0, border_color);
	
    for (i = y0 + 1; i < y1; i++) {
        LCD_DrawLine(x0, i, x0, i, border_color);
        LCD_DrawLine(x0 + 1, i, x1 - 1, i, fill_color);
        LCD_DrawLine(x1, i, x1, i, border_color);
    }
	
	LCD_DrawLine(x0, y1, x1, y1, border_color); // Linea inferiore
}

/* ******************** GAME DRAW FUNCTIONS ******************** */

void Draw_Title() {
	// x=20 y=4 were found simply testing different positions in order to look it pretty
	GUI_Text(20,4,(uint8_t *) "GAME OVER IN      SCORE", Blue, Black);
	
	// x=60 y=285 were found simply testing different positions in order to look it pretty
	GUI_Text(60,285,(uint8_t *) "REMAINING LIVES", Blue, Black);
}

void Draw_Score() {
	/*
		Variable score is declared as int, but GUI_Text func requires a string as input
		Next code is used to convert the int value into uint8_t
	*/
	uint8_t score_conv_string[12];
	sprintf((char *)score_conv_string, "%d", score);
	
	// x=170 y=16 were found simply testing different positions in order to look it pretty
	GUI_Text(170,16,(uint8_t *) score_conv_string, Blue, Black);
}

void Draw_Time_Left() {
	uint8_t count_down_conv_string[12];
	sprintf((char *)count_down_conv_string, "%d    ", countdown);
	
	GUI_Text(50,16,(uint8_t *) count_down_conv_string, Blue, Black);
}

void Draw_Lives(int initialX, int initialY) {
	int nextHeartDistance = 16;
	int i = 0;
	
	for(i=0; i<MAX_NUM_LIFES; i++) {
		if (i<num_lifes) {
			// For the actual lives a red heart is showed
			Draw_Heart(initialX,initialY,7,Red);
		} else {
			// Otherwise a black heart is showed, to clear the screen
			Draw_Heart(initialX,initialY,7,Black);
		}
		initialX = initialX + nextHeartDistance;
	}
}

void Draw_Board(int drawAllBoardFlag){
    int i, j, current_value;
	int x_pos, y_pos;
	int newStartingJ = 0, newStartingI = 0;
	int addPaddingI = 0;
	
	Draw_Title();
	Draw_Score();
	Draw_Time_Left();
	Draw_Lives(X_POSITION_LIVES_IN_GAME, Y_POSITION_LIVES_IN_GAME);
	
	if (firstBoardGenerated == 0) {
		setPacman();
		generatePowerPills();
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
				Draw_Wall(x_pos, y_pos, Black);
			}
           
            switch(current_value){ 
                case WALL:
                    Draw_Wall(x_pos, y_pos, Blue);
                break;
                case STANDARD_PILL:
                    Draw_Point(x_pos, y_pos, Magenta);
				break;
				case POWER_PILL:
                    Draw_Circle(x_pos, y_pos, POWER_PILL_RADIUS, Magenta);
				break;
				case TP_LEFT:
					//Draw_Wall(x_pos, y_pos, Cyan);
				break;
				case TP_RIGHT:
					//Draw_Wall(x_pos, y_pos, Cyan);
				break;
				case PACMAN:
					Draw_Circle(x_pos, y_pos, PACMAN_RADIUS, Yellow);
				break;
                default:
                break;
            }
        }
    }
}

void Draw_Pacman_Move(int newY, int newX, int prevY, int prevX) {
	// Draw black on the previous position
	Draw_Circle(alignCoordX(prevX), alignCoordY(prevY), PACMAN_RADIUS, Black);

    // Draw pacman on the new position
    Draw_Circle(alignCoordX(newX), alignCoordY(newY), PACMAN_RADIUS, Yellow);
}

void Draw_Game_Over_Screen() {
	LCD_Clear(Black);
	GUI_Text(85,130,(uint8_t *) "GAME OVER", Blue, Black);
	
	GUI_Text(60,150,(uint8_t *) "REMAINING LIVES", Blue, Black);
	Draw_Lives(X_POSITION_LIVES_IN_GAMEOVER, Y_POSITION_LIVES_IN_GAMEOVER);
	GUI_Text(40,200,(uint8_t *) "Press KEY1 to Restart", Blue, Black);
}

void Clear_Game_Over_Screen() {
	LCD_FillRectWithBorder(40,130,170,100,Black,Black);
}

void Draw_Game_Ended() {
	LCD_Clear(Black);
	GUI_Text(85, 130,(uint8_t *) "GAME OVER", Blue, Black);
	GUI_Text(47, 150,(uint8_t *) "NO REMAINING LIVES", Blue, Black);
	GUI_Text(86, 170,(uint8_t *) "YOU LOST!", Blue, Black);
}

void Draw_Pause_Box() {
	LCD_FillRectWithBorder(64, 104, 112, 88, Black, Red);
	GUI_Text(80, 118,(uint8_t *) "GAME PAUSE", Red, Black);
	GUI_Text(80, 150,(uint8_t *) "Press INT0", Red, Black);
	GUI_Text(82, 162,(uint8_t *) "to resume", Red, Black);
}

void Draw_Victory_Screen() {
	LCD_Clear(Black);
	GUI_Text(85, 130,(uint8_t *) "VICTORY!", Blue, Black);
}
