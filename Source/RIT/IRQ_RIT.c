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
#include "GAME/general_utils.h"

/******************************************************************************
** Function name:		RIT_IRQHandler
**
** Descriptions:		REPETITIVE INTERRUPT TIMER handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/

// Gestione del de bouncing per i 3 pulsanti
volatile int down_0 = 0;
volatile int down_1 = 0;
volatile int down_2 = 0;
// fine gestione de bouncing

void RIT_IRQHandler (void)
{			
/*************************INT0***************************/
if(down_0 !=0){
	down_0++;
	if((LPC_GPIO2->FIOPIN & (1<<10)) == 0){
		switch(down_0){
			case 2:
				// your code here
				break;
			default:
				break;
		}
	}
	else {	/* button released */
		down_0=0;			
		NVIC_EnableIRQ(EINT0_IRQn);							 /* disable Button interrupts			*/
		LPC_PINCON->PINSEL4    |= (1 << 20);     /* External interrupt 0 pin selection */
	}
} // end INT0

/*************************KEY1***************************/
if(down_1 !=0){
	down_1++;
	if((LPC_GPIO2->FIOPIN & (1<<11)) == 0){
		switch(down_1){
			case 2:
				// your code here
				break;
			default:
				break;
		}
	}
	else {	/* button released */
		down_1=0;			
		NVIC_EnableIRQ(EINT1_IRQn);							 /* disable Button interrupts			*/
		LPC_PINCON->PINSEL4    |= (1 << 22);     /* External interrupt 0 pin selection */
	}
} // end KEY1

/*************************KEY2***************************/
if(down_2 !=0){
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
		LPC_PINCON->PINSEL4    |= (1 << 24);     /* External interrupt 0 pin selection */
	}
} // end KEY2

/*************************JOYSTICK-UP***************************/
	static int J_up = 0;
	
	if((LPC_GPIO1->FIOPIN & (1<<29)) == 0){	
		/* Joytick UP pressed */
		J_up++;
		switch(J_up){
			case 1:
				// your code here
				LCD_DrawSquare(50,50,10,White);
			
			
				break;
			case 60:	//3sec = 3000ms/ 50ms = 60
				// potential other code here
				break;
			default:
				// potential other code here
				break;
		}
	}
	else{
			J_up=0;
	} // end JOYSTICK-UP
	
/*************************JOYSTICK-DOWN***************************/
	static int J_down = 0;
	
	if((LPC_GPIO1->FIOPIN & (1<<26)) == 0){	
		/* Joytick DOWN pressed */
		J_down++;
		switch(J_down){
			case 1:
				// your code here
			
				LCD_DrawSquare(50,50,10,Red);
				break;
			case 60:	//3sec = 3000ms/ 50ms = 60
				// potential other code here
				break;
			default:
				// potential other code here
				break;
		}
	}
	else{
			J_down=0;
	} // end JOYSTICK-DOWN
	
/*************************JOYSTICK-SX***************************/
	
/*************************JOYSTICK-DX***************************/
	
/*************************JOYSTICK-PRESSED***************************/
	
	reset_RIT();
  LPC_RIT->RICTRL |= 0x1;	/* clear interrupt flag */
	
  return;
}

/******************************************************************************
**                            End Of File
******************************************************************************/
