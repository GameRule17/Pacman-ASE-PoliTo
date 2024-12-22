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
#include "timer/timer.h"

	/* User Imports */
#import "GAME/game_state.h"
	
int main(void)
{
	/* Area Init */
	
	// System
	SystemInit();
	
	// Display
	LCD_Initialization();
	LCD_Clear(Black);
	
	// Buttons
	BUTTON_init();
	
	// Joystick
	joystick_init();
	
	// RIT
	init_RIT(0x004C4B40);					// 50ms
	enable_RIT();
	
	// Timers
	LPC_SC -> PCONP |= (1 << 22);  			// Turn ON TIMER2 
	LPC_SC -> PCONP |= (1 << 23);  			// Turn ON TIMER3 
	
	/* Area Timers */
	
		//TIMER0 - COUNTDOWN TIMER
	// MR0 is used as UPDATE for every SECOND PASSED
	init_timer(0, 0, 0, 3, 0x17D7840); // 1*25000000=0x17D7840
	//enable_timer(0);
	
		//TIMER1 - PACMAN MOVEMENT TIMER
	// Every 100ms pacman moves, if flag movement is set
	init_timer(1, 0, 0, 3, 0x2625A0); // 0,1*25000000=0x2625A0
	//enable_timer(1);
	
		//TIMER2
	//init_timer(2, 0, 0, 3, 0x);
	//enable_timer(2);
	
		//TIMER3
	//init_timer(3, 0, 0, 3, 0x);
	//enable_timer(3);
	
	
	/* Area Code */
	startGame();
	
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
