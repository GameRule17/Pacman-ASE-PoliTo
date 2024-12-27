#include "music.h"

const uint16_t SinTable[45] = {
	410, 467, 523, 576, 627, 673, 714, 749, 778,
	799, 813, 819, 817, 807, 789, 764, 732, 694, 
	650, 602, 550, 495, 438, 381, 324, 270, 217,
	169, 125, 87 , 55 , 30 , 12 , 2  , 0  , 6  ,   
	20 , 41 , 70 , 105, 146, 193, 243, 297, 353
};

void playMusicSound() {
	static int sineticks=0;
	/* DAC management */	
	static int currentValue; 
	currentValue = SinTable[sineticks];
//	currentValue -= 410;
//	currentValue /= 1;
//	currentValue += 410;
	LPC_DAC->DACR = currentValue <<6;
	sineticks++;
	if(sineticks==45) sineticks=0;
}

void playMusicSoundDuration() {
	LPC_TIM2->TCR = 0;
}
