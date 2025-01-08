#include "CAN.h"

void sendPlayerStatsUsingCAN(uint16_t countdown, uint8_t numLives, uint16_t score) {
	// Sending player game stats through CAN 
	// From CAN1 to CAN2
	CAN_TxMsg.data[0] = countdown;
	CAN_TxMsg.data[1] = numLives;
	CAN_TxMsg.data[2] = (score & 0xFF00) >> 8;
	CAN_TxMsg.data[3] = score & 0xFF;
	
	CAN_TxMsg.len = 4;
	CAN_TxMsg.id = 2;
	CAN_TxMsg.format = STANDARD_FORMAT;
	CAN_TxMsg.type = DATA_FRAME;
	CAN_wrMsg (1, &CAN_TxMsg);               /* transmit message */
}

void drawPlayerStatsReceivedByCAN(uint16_t CAN_countdown, uint8_t CAN_numLives, uint16_t CAN_score) {
	uint16_t conv_string[12];
	
	if(gamePause == 0) {
		drawScore(CAN_score);
		
		drawTimeLeft(CAN_countdown);
		
		drawLives(CAN_numLives, X_POSITION_LIVES_IN_GAME, Y_POSITION_LIVES_IN_GAME);
	}
}