/****************************************Copyright (c)****************************************************
**                                      
**                                 http://www.powermcu.com
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               main.c
** Descriptions:            The GLCD application function
**
**--------------------------------------------------------------------------------------------------------
** Created by:              AVRman
** Created date:            2010-11-7
** Version:                 v1.0
** Descriptions:            The original version
**
**--------------------------------------------------------------------------------------------------------
** Modified by:             Paolo Bernardi
** Modified date:           03/01/2020
** Version:                 v2.0
** Descriptions:            basic program for LCD and Touch Panel teaching
**
*********************************************************************************************************/



	/* System Defines */
	
#include "LPC17xx.h"

#ifdef SIMULATOR
extern uint8_t ScaleFlag; // <- ScaleFlag needs to visible in order for the emulator to find the symbol (can be placed also inside system_LPC17xx.h but since it is RO, it needs more work)
//int const is_simulator = 1;
#endif


	/* Hardware Imports */

#include "GLCD/GLCD.h" 
#include "TouchPanel/TouchPanel.h"
#include "led/led.h"
#include "timer/timer.h"


	/* User Imports */
#include "GAME/drawing_func.h"
	
int main(void)
{
	/* Area Init */
	
	// System
	SystemInit();
	
	// Display
	LCD_Initialization();
	LCD_Clear(Black);
	
	// TouchScreen
	//TP_Init();
	//if (!is_simulator)
	//	TouchPanel_Calibrate();
	
	// Led
	//LED_init();
	
	// Buttons
	BUTTON_init();
	
	// Joystick
	joystick_init();
	
	// RIT
	init_RIT(0x004C4B40);					// 50ms
	enable_RIT();
	
	// Timers
	LPC_SC -> PCONP |= (1 << 22);  			// Turn ON TIMER2 (anche da Wizard del System)
	LPC_SC -> PCONP |= (1 << 23);  			// Turn ON TIMER3 (anche da Wizard del System)
	
	// ADC
	//ADC_init();
	
	
	/* Area Timers */
	
	// t * f = count
	// f = 25Mhz	=> 25'000'000 Hz
	// t = richiesta del problema
	
	//init_timer(timer_num, Prescaler, MatchReg, SRImatchReg, TimerInterval);
	
		//TIMER0 - COUNTDOWN TIMER
	// MR0 is used as UPDATE for every SECOND PASSED
	// SRImatchReg set as 1 -> INTERRUPT
	init_timer(0, 0, 0, 3, 0x17D7840); // 1*25000000=0x17D7840
	enable_timer(0);
	
		//TIMER1 - PACMAN MOVES TIMER
	// Every 200ms pacman moves, if one of the flags UP/DOWN/LEFT/RIGHT is =1
	init_timer(1, 0, 0, 3, 0x4C4B40); // 0,2*25000000=0x4C4B40
	enable_timer(1);
	
		//TIMER2
	//init_timer(2, 0, 0, 3, 0x);
	//enable_timer(2);
	
		//TIMER3
	//init_timer(3, 0, 0, 3, 0x);
	//enable_timer(3);
	
	
	/* Area Code */
	Draw_Board();
	
	
	/* Area Loop */
	
	LPC_SC->PCON |= 0x1;					/* power-down mode */
	LPC_SC->PCON &= ~(0x2);						
	
	while (1) {
		__ASM("wfi");
	}
	
}

/*********************************************************************************************************
      END FILE
*********************************************************************************************************/
