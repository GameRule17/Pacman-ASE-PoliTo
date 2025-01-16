/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           IRQ_timer.c
** Last modified Date:  2014-09-25
** Last Version:        V1.00
** Descriptions:        functions to manage T0 and T1 interrupts
** Correlated files:    timer.h
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#include "LPC17xx.h"
#include "timer.h"

/******************************************************************************
** Function name:		Timer0_IRQHandler
**
** Descriptions:		Timer/Counter 0 interrupt handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/
void TIMER0_IRQHandler (void)
{
	if(LPC_TIM0->IR & 1) {		// MR0 
		// your code
		// MR0 counts every SECOND
		
		updateCountdown();
		
		if (blinkyMode == BLINKY_FRIGHTENED_MODE) {
			timeBlinkyFrightened++;
			// If 10 seconds of frightened mode passed
			if (timeBlinkyFrightened == 10) {
				// Reset Blinky in chase mode
				timeBlinkyFrightened = 0;
				blinkyMode = BLINKY_CHASE_MODE;
			}
		}
		
		LPC_TIM0->IR = 1;			//clear interrupt flag
	}
	else if(LPC_TIM0->IR & 2){	// MR1
		// your code
		LPC_TIM0->IR = 2;			// clear interrupt flag 
	}
	else if(LPC_TIM0->IR & 4){	// MR2
		// your code	
		LPC_TIM0->IR = 4;			// clear interrupt flag 
	}
	else if(LPC_TIM0->IR & 8){	// MR3
		// your code	
		LPC_TIM0->IR = 8;			// clear interrupt flag 
	}
	return;
}

/******************************************************************************
** Function name:		Timer1_IRQHandler
**
** Descriptions:		Timer/Counter 1 interrupt handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/
void TIMER1_IRQHandler (void)
{
	if(LPC_TIM1->IR & 1) {		// MR0 
		// your code
		uint16_t threshold;
		uint8_t theyCollided = 0;
		static uint32_t blinkyTicksMovementCounter = BLINKY_INITIAL_TICKS_MOVEMENT;
		static uint32_t initialTicksNumber = BLINKY_INITIAL_TICKS_MOVEMENT;
		
		tryGenerationPowerPills();
		
		if (isBlinkyFreeFlag == 0) {
			freeBlinkyFromCage();
		} else {
			
			// Make Blinky faster and aggressive as the game progresses			
			if (blinkyTicksMovementCounter == 0) {
				moveBlinky();
				theyCollided = checkCollision();
				
				if (initialTicksNumber == 1) { // Blinky will always be a little slower than pacman
					blinkyTicksMovementCounter = 1;
				} else {
					initialTicksNumber--;
					blinkyTicksMovementCounter = initialTicksNumber;
				}
			} else {
				blinkyTicksMovementCounter--;
			}
		}
		
		if (theyCollided == 0) {
			movePacman(direction);
			checkCollision();
			theyCollided = 0;
		}
		
		// Sending player game stats through CAN 
		sendPlayerStatsUsingCAN(countdown, numLives, score);
		
		LPC_TIM1->IR = 1;			//clear interrupt flag
	}
	else if(LPC_TIM1->IR & 2) {	// MR1
		// your code
		LPC_TIM1->IR = 2;			// clear interrupt flag 
	}
	else if(LPC_TIM1->IR & 4) {	// MR2
		// your code	
		LPC_TIM1->IR = 4;			// clear interrupt flag 
	}
	else if(LPC_TIM1->IR & 8) {	// MR3
		// your code	
		LPC_TIM1->IR = 8;			// clear interrupt flag 
	}

	return;
}

/******************************************************************************
** Function name:		Timer2_IRQHandler
**
** Descriptions:		Timer/Counter 1 interrupt handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/
void TIMER2_IRQHandler (void)
{
	if(LPC_TIM2->IR & 1) {		// MR0 
		// your code
		
		playMusicSound(); // Background Game Music or Sound Effects
		
		LPC_TIM2->IR = 1;			//clear interrupt flag
	}
	else if(LPC_TIM2->IR & 2){	// MR1
		// your code
		LPC_TIM2->IR = 2;			// clear interrupt flag 
	}
	else if(LPC_TIM2->IR & 4){	// MR2
		// your code	
		LPC_TIM2->IR = 4;			// clear interrupt flag 
	}
	else if(LPC_TIM2->IR & 8){	// MR3
		// your code	
		LPC_TIM2->IR = 8;			// clear interrupt flag 
	}
	return;
}


/******************************************************************************
** Function name:		Timer3_IRQHandler
**
** Descriptions:		Timer/Counter 1 interrupt handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/
void TIMER3_IRQHandler (void)
{
	if(LPC_TIM3->IR & 1) {		// MR0 
		// your code
		playMusicSoundDuration(); // Background Game Music or Sound Effects
		
		LPC_TIM3->IR = 1;			//clear interrupt flag
	}
	else if(LPC_TIM3->IR & 2){	// MR1
		// your code	
		LPC_TIM3->IR = 2;			// clear interrupt flag 
	}
	else if(LPC_TIM3->IR & 4){	// MR2
		// your code	
		LPC_TIM3->IR = 4;			// clear interrupt flag 
	}
	else if(LPC_TIM3->IR & 8){	// MR3
		// your code	
		LPC_TIM3->IR = 8;			// clear interrupt flag 
	}
	return;
}



/******************************************************************************
**                            End Of File
******************************************************************************/

