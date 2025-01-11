/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           IRQ_RIT.c
** Last modified Date:  2014-09-25
** Last Version:        V1.00
** Descriptions:        functions to manage T0 and T1 interrupts
** Correlated files:    RIT.h
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#include "LPC17xx.h"
#include "RIT.h"
#include "GAME/moving_func.h"

	/* Global Variables for De-Bouncing */
volatile int down_0 = 0;
volatile int down_1 = 0;
volatile int down_2 = 0;

	/* Joystick and Key usage Global Variables */
volatile int J_up = 0;
volatile int J_down = 0;
volatile int J_right = 0;
volatile int J_left = 0;
volatile int J_click = 0;

volatile int enableKey1Usage = 0;
volatile int enableInt0Usage = 1;

void enableKEY1() {
	enableKey1Usage = 1;
}

void disableKEY1() {
	enableKey1Usage = 0;
}

void enableINT0() {
	enableInt0Usage = 1;
}

void disableINT0() {
	enableInt0Usage = 0;
}


/******************************************************************************
** Function name:		RIT_IRQHandler
**
** Descriptions:		REPETITIVE INTERRUPT TIMER handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/
void RIT_IRQHandler(void) 
{			
		
	if(down_0 !=0) {			/* INT0 */
		down_0++;
		if((LPC_GPIO2->FIOPIN & (1<<10)) == 0){
			switch(down_0) {
				case 2:
					// your code here
					
					if(enableInt0Usage == 1) {
						if(gamePause == 1) {
							removeGamePause();
						} else {
							setGamePause();
						}
					}
				
					break;
				default:
					break;
			}
		}
		else {	/* button released */
			down_0=0;			
			NVIC_EnableIRQ(EINT0_IRQn);							 /* disable Button interrupts			*/
			LPC_PINCON->PINSEL4    |= (1 << 20);     			 /* External interrupt 0 pin selection   */
		}
	} 	// end INT0

	/////////////////////////////////////
	
	if(down_1 !=0) {			/* KEY1 */
		down_1++;
		if((LPC_GPIO2->FIOPIN & (1<<11)) == 0){
			switch(down_1){
				case 2:
					// your code here
					
					if (enableKey1Usage == 1) {
						restartGame();
						disableKEY1();
					}
				
					break;
				default:
					break;
			}
		}
		else {	/* button released */
			down_1=0;			
			NVIC_EnableIRQ(EINT1_IRQn);							 /* disable Button interrupts			*/
			LPC_PINCON->PINSEL4    |= (1 << 22);     			 /* External interrupt 0 pin selection   */
		}
	}	// end KEY1
	
	/////////////////////////////////////

	if(down_2 !=0) {			/* KEY2 */
		down_2++;
		if((LPC_GPIO2->FIOPIN & (1<<12)) == 0){
			switch(down_2){
				case 2:
					// your code here
					break;
				default:
					break;
			}
		}
		else {	/* button released */
			down_2=0;		
			NVIC_EnableIRQ(EINT2_IRQn);							 /* disable Button interrupts			*/
			LPC_PINCON->PINSEL4    |= (1 << 24);     			 /* External interrupt 0 pin selection  */
		}
	}	// end KEY2
	
	/////////////////////////////////////

	if((LPC_GPIO1->FIOPIN & (1<<29)) == 0) {		/* Joystick UP */
		/* Joytick UP pressed */
		J_up++;
		switch(J_up){
			case 1:
				// your code here
				direction = J_UP_KEY;			
				break;
			default:
				// potential other code here
				break;
		}
	}
	else {
		J_up=0;
	}	// end Joystick UP
	
	/////////////////////////////////////
	
	if((LPC_GPIO1->FIOPIN & (1<<26)) == 0) {		/* Joystick DOWN */
		/* Joytick DOWN pressed */
		J_down++;
		switch(J_down){
			case 1:
				// your code here
				direction = J_DOWN_KEY;
				break;
			default:
				// potential other code here
				break;
		}
	}
	else{
		J_down=0;
	}	// end Joystick DOWN

	/////////////////////////////////////

	if((LPC_GPIO1->FIOPIN & (1<<28)) == 0) {		/* Joystick RIGHT */
		/* Joytick RIGHT pressed */
		J_right++;
		switch(J_right){
			case 1:
				// your code here
				direction = J_RIGHT_KEY;	
				break;
			default:
				// potential other code here
				break;
		}
	}
	else {
		J_right=0;
	}	// end Joystick RIGHT
	
	/////////////////////////////////////

	if((LPC_GPIO1->FIOPIN & (1<<27)) == 0) {		/* Joystick LEFT */
		/* Joytick LEFT pressed */
		J_left++;
		switch(J_left){
			case 1:
				// your code here
				direction = J_LEFT_KEY;
				break;
			default:
				// potential other code here
				break;
		}
	}
	else {
		J_left=0;
	}	// end Joystick LEFT
	
	/////////////////////////////////////

	if((LPC_GPIO1->FIOPIN & (1<<25)) == 0) {		/* Joystick CLICK */
		/* Joytick CLICK pressed */
		J_click++;
		switch(J_click){
			case 1:
				// your code here
				break;
			default:
				// potential other code here
				break;
		}
	}
	else {
		J_click=0;
	}	// end Joystick CLICK
	
	/////////////////////////////////////
	
	reset_RIT();
	LPC_RIT->RICTRL |= 0x1;	/* clear interrupt flag */
	
	return;
}


/******************************************************************************
**                            End Of File
******************************************************************************/
