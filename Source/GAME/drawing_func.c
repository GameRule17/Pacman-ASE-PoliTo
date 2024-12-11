#import "GAME/game_matrix.h"
#import "GLCD.h"

void Draw_Wall(int current_X, int current_Y){
	int i, j;
 
	for(i = 0; i < RATIO; i++){
		for(j = 0; j < RATIO; j++){
			LCD_SetPoint(current_X + i, current_Y + j, Blue);
		}
	}
}

void Draw_Point(int current_X, int current_Y){
	int i, j;
 
	LCD_SetPoint(current_X + 4, current_Y + 4, Magenta);
}

void Draw_Matrix(){
	int i, j, current_value;
 
	for(i = 0; i < HEIGTH; i++){
		for(j = 0; j < LENGTH; j++){
			current_value = board[i][j];
		   
			switch(current_value){ 
				case 1:
					// +8 = #pixel dist from the side edge
					// +32 = #pixel dist from the upper edge
					Draw_Wall((j * 8) + 8, (i * 8) + 32);
				break;
				case 2:
					Draw_Point((j * 8) + 8, (i * 8) + 32);
				default:
				break;
			}
		}
	}
}