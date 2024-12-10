#include "LPC17xx.h"
#include "GLCD.h" 
#include "AsciiLib.h"

#define NUM_ROWS 7
#define NUM_COLUMNS	7
#define WALL_WIDTH 6 
#define SQUARE_SIZE (MAX_X - (NUM_ROWS - 1) * WALL_WIDTH) / NUM_ROWS

void LCD_DrawRect( uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1 , uint16_t color ){
	LCD_DrawLine(x0, y0, x1, y0, color); //top 
	LCD_DrawLine(x1, y0, x1, y1, color); //right 
	LCD_DrawLine(x1, y1, x0, y1, color); //down 
	LCD_DrawLine(x0, y1, x0, y0, color); //left 
}

void LCD_DrawSquare( uint16_t x0, uint16_t y0, uint16_t len, uint16_t color ){
	LCD_DrawRect(x0, y0, x0+len, y0+len, color);
}

void LCD_FillRect( uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1 , uint16_t color ){
	uint16_t i;
	
	for(i=y0;i<y1;i++){
		LCD_DrawLine(x0, i, x1, i, color);
	}
}

void LCD_DrawCircle(uint16_t xc, uint16_t yc, uint16_t r, uint16_t color) {
    int x = 0;
    int y = r;
    int d = 3 - 2 * r; // Decision parameter

    while (x <= y) {
        // Disegna i punti simmetrici nei 4 quadranti
        LCD_SetPoint(xc + x, yc + y, color); // Quadrante 1
        LCD_SetPoint(xc - x, yc + y, color); // Quadrante 2
        LCD_SetPoint(xc + x, yc - y, color); // Quadrante 3
        LCD_SetPoint(xc - x, yc - y, color); // Quadrante 4
        LCD_SetPoint(xc + y, yc + x, color); // Quadrante 5
        LCD_SetPoint(xc - y, yc + x, color); // Quadrante 6
        LCD_SetPoint(xc + y, yc - x, color); // Quadrante 7
        LCD_SetPoint(xc - y, yc - x, color); // Quadrante 8

        if (d < 0) {
            d = d + 4 * x + 6;
        } else {
            d = d + 4 * (x - y) + 10;
            y--;
        }
        x++;
    }
}

void LCD_FillCircle(uint16_t xc, uint16_t yc, uint16_t r, uint16_t color) {
    int x = 0;
    int y = r;
    int d = 3 - 2 * r; // Decision parameter

    while (x <= y) {
        // Disegna linee orizzontali tra i punti simmetrici
        LCD_DrawLine(xc - x, yc + y, xc + x, yc + y, color); // Linea sopra
        LCD_DrawLine(xc - x, yc - y, xc + x, yc - y, color); // Linea sotto
        LCD_DrawLine(xc - y, yc + x, xc + y, yc + x, color); // Linea orizzontale sopra
        LCD_DrawLine(xc - y, yc - x, xc + y, yc - x, color); // Linea orizzontale sotto

        if (d < 0) {
            d = d + 4 * x + 6;
        } else {
            d = d + 4 * (x - y) + 10;
            y--;
        }
        x++;
    }
}

void Board_Init(){
	uint8_t i,j;

	for(i=0; i<NUM_ROWS; i++){
		for(j=0; j<NUM_COLUMNS; j++){
			uint16_t x = i * (SQUARE_SIZE + WALL_WIDTH);
      uint16_t y = j * (SQUARE_SIZE + WALL_WIDTH);

			LCD_DrawSquare(x, y, SQUARE_SIZE, Blue);
		}
	}
}

