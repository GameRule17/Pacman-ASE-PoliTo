#import "GAME/drawing_func.h"

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

void Draw_Matrix(){
    int i, j, current_value;
	int x_pos, y_pos;
	
	setPacman();
	generatePowerPills();
 
    for(i = 0; i < HEIGTH; i++){
        for(j = 0; j < LENGTH; j++){
            current_value = board[i][j];
			x_pos = (j * RATIO) + SIDE_PADDING;
			y_pos = (i * RATIO) + UPPER_PADDING;
           
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
					Draw_Wall(x_pos, y_pos, Cyan);
				break;
				case TP_RIGHT:
					Draw_Wall(x_pos, y_pos, Cyan);
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

void Draw_Pacman_Move(int newX, int newY, int prevX, int prevY) {
	// Draw black on the previous position
	Draw_Circle((prevY * RATIO) + SIDE_PADDING, (prevX * RATIO) + UPPER_PADDING, PACMAN_RADIUS, Black);

    // Draw pacman on the new position
    Draw_Circle((newY * RATIO) + SIDE_PADDING, (newX * RATIO) + UPPER_PADDING, PACMAN_RADIUS, Yellow);
}
