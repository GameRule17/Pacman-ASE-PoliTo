/*----------------------------------------------------------------------------
 * Name:    Can.c
 * Purpose: CAN interface for for LPC17xx with MCB1700
 * Note(s): see also http://www.port.de/engl/canprod/sv_req_form.html
 *----------------------------------------------------------------------------
 * This file is part of the uVision/ARM development tools.
 * This software may only be used under the terms of a valid, current,
 * end user licence from KEIL for a compatible version of KEIL software
 * development tools. Nothing else gives you the right to use this software.
 *
 * This software is supplied "AS IS" without warranties of any kind.
 *
 * Copyright (c) 2009 Keil - An ARM Company. All rights reserved.
 *----------------------------------------------------------------------------*/

#include "CAN.h"                      /* LPC17xx CAN adaption layer */

extern uint8_t icr ; 		 //icr and result must be global in order to work with both real and simulated landtiger.
extern uint32_t result;
extern CAN_msg CAN_TxMsg;    /* CAN message for sending */
extern CAN_msg CAN_RxMsg;    /* CAN message for receiving */                                

uint16_t CAN_countdown;
uint8_t CAN_numLives;
uint16_t CAN_score;

/*----------------------------------------------------------------------------
  CAN interrupt handler
 *----------------------------------------------------------------------------*/
void CAN_IRQHandler (void)  {

  /* check CAN controller 1 */
	icr = 0;
	icr = (LPC_CAN1->ICR | icr) & 0xFF;               /* clear interrupts */
	
	if (icr & (1 << 0)) {                          		/* CAN Controller #1 meassage is received */
		CAN_rdMsg (1, &CAN_RxMsg);	                		/* Read the message */
		LPC_CAN1->CMR = (1 << 2);                    		/* Release receive buffer */
		
		// nothing to do
	}
	
	if (icr & (1 << 1)) {                         /* CAN Controller #1 meassage is transmitted */
		// do nothing in this example
	}
		
	/* check CAN controller 2 */
	icr = 0;
	icr = (LPC_CAN2->ICR | icr) & 0xFF;             /* clear interrupts */

	if (icr & (1 << 0)) {                          	/* CAN Controller #2 meassage is received */
		CAN_rdMsg (2, &CAN_RxMsg);	                		/* Read the message */
		LPC_CAN2->CMR = (1 << 2);                    		/* Release receive buffer */
		
		// Decode values
		CAN_countdown = CAN_RxMsg.data[0]; // 8 bit
		CAN_numLives = CAN_RxMsg.data[1]; // 8 bit
		CAN_score = (CAN_RxMsg.data[2] << 8); // 16 bit pt1
		CAN_score = CAN_score | CAN_RxMsg.data[3]; // 16 bit pt2
		
		// Draw new stats on screen
		drawPlayerStatsReceivedByCAN(CAN_countdown, CAN_numLives, CAN_score);
	}
	
	if (icr & (1 << 1)) {                         /* CAN Controller #2 meassage is transmitted */
		// do nothing in this example
	}
}
