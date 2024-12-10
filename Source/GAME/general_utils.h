#include "LPC17xx.h"
#include "GLCD.h" 
#include "AsciiLib.h"

void LCD_DrawRect(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1 , uint16_t color);
void LCD_DrawSquare(uint16_t x0, uint16_t y0, uint16_t len, uint16_t color);
void LCD_FillRect(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1 , uint16_t color);
void LCD_DrawCircle(uint16_t xc, uint16_t yc, uint16_t r, uint16_t color);
void LCD_FillCircle(uint16_t xc, uint16_t yc, uint16_t r, uint16_t color);