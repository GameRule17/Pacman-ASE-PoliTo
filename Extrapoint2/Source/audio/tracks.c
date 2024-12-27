#include "music.h"

#define RIT_SEMIMINIMA 8
#define RIT_MINIMA 16
#define RIT_INTERA 32
#define UPTICKS 1

const NOTE backgroundMusic[] = {
	// PACMAN MUSIC 
	// 1
	{b1, time_croma},
	{b2, time_croma},
	{f2d, time_croma},
	{e2b, time_croma},
	{b2, time_semicroma},
	{f2d, time_croma+time_semicroma},
	{e2b, time_semiminima},
	{c2, time_croma},
	{c3, time_croma},
	{g2, time_croma},
	{e2, time_croma},
	{c3, time_semicroma},
	{g2, time_croma+time_semicroma},
	{e2, time_semiminima},
	
	// 2
	{b1, time_croma},
	{b2, time_croma},
	{f2d, time_croma},
	{e2b, time_croma},
	{b2, time_semicroma},
	{f2d, time_croma+time_semicroma},
	{e2b, time_semiminima},
	{e2, time_semicroma},
	{e2, time_semicroma},
	{f2, time_croma},
	{f2, time_semicroma},
	{f2d, time_semicroma},
	{g2, time_croma},
	{g2, time_semicroma},
	{a2b, time_semicroma},
	{b2, time_semiminima}
};

const uint16_t backgroundMusicSize = sizeof(backgroundMusic) / sizeof(backgroundMusic[0]);

const NOTE superPillEatedSound[] = {
    {g2, time_biscroma},
    {a2, time_biscroma},
    {b2, time_biscroma},
    {c3, time_biscroma},
    {d3, time_biscroma},
    {e3, time_biscroma},
    {f3, time_biscroma},
    {g3, time_biscroma},
    {pause, time_croma} 
};

const uint16_t superPillEatedSoundSize = sizeof(superPillEatedSound) / sizeof(superPillEatedSound[0]);

const NOTE loseLifeSound[] = {
    {e3, time_croma},
    {d3, time_biscroma},
    {c3, time_biscroma},
    {a2, time_biscroma},
    {g2, time_semicroma},
    {pause, time_croma}  
};

const uint16_t loseLifeSoundSize = sizeof(loseLifeSound) / sizeof(loseLifeSound[0]);

const NOTE gainLifeSound[] = {
    {c3, time_biscroma},
    {e3, time_biscroma},
    {g3, time_biscroma},
    {c4, time_biscroma},
    {pause, time_croma}
};

const uint16_t gainLifeSoundSize = sizeof(gainLifeSound) / sizeof(gainLifeSound[0]);

uint8_t soundToPlay = SOUND_BACKGROUND_MUSIC;

//void playSoundEffect(uint8_t sound) {
//    static uint16_t currentNote = 0;
//    static uint16_t ticks = 0;
//	uint16_t length;
//	const NOTE *effect;
//	
//	switch(sound) {
//		case SOUND_BACKGROUND_MUSIC:
//			effect = backgroundMusic;
//			length = backgroundMusicSize;
//		break;
//		case SOUND_SUPER_PILL_EATED:
//			effect = superPillEatedSound;
//			length = superPillEatedSoundSize;
//		break;
//		case SOUND_LIFE_LOSED:
//			effect = loseLifeSound;
//			length = loseLifeSoundSize;
//		case SOUND_LIFE_GAINED:
//			effect = gainLifeSound;
//			length = gainLifeSoundSize;
//		default:
//		break;
//	}

//    if (!isNotePlaying()) {
//        ++ticks;
//        if (ticks == UPTICKS) {
//            ticks = 0;
//            playNote(effect[currentNote++]);
//        }
//    }

//    if (currentNote >= length) {
//		// Restart backgound music
//        currentNote = 0;
//		ticks = 0;
//		soundToPlay = SOUND_BACKGROUND_MUSIC;
//    }
//}

void playSoundEffect(uint8_t sound) {
    static uint8_t currentSound = SOUND_BACKGROUND_MUSIC;
    static uint16_t currentNote = 0;
    static uint16_t ticks = 0;
    uint16_t length;
    const NOTE *effect;

    // Cambia traccia se necessario
    if (currentSound != sound) {
        currentSound = sound;
        currentNote = 0;
        ticks = 0;
    }

    // Seleziona la traccia attuale
    switch (currentSound) {
        case SOUND_BACKGROUND_MUSIC:
            effect = backgroundMusic;
            length = backgroundMusicSize;
            break;
        case SOUND_SUPER_PILL_EATED:
            effect = superPillEatedSound;
            length = superPillEatedSoundSize;
            break;
        case SOUND_LIFE_LOSED:
            effect = loseLifeSound;
            length = loseLifeSoundSize;
            break; // Manca il break nel codice originale
        case SOUND_LIFE_GAINED:
            effect = gainLifeSound;
            length = gainLifeSoundSize;
            break;
        default:
            return; // Uscita se il suono è sconosciuto
    }

    // Riproduci la nota successiva
    if (!isNotePlaying()) {
        ++ticks;
        if (ticks == UPTICKS) {
            ticks = 0;
            playNote(effect[currentNote++]);
        }
    }

    // Reset della traccia quando finisce
    if (currentNote >= length) {
        currentNote = 0;
        ticks = 0;

        // Torna alla musica di sottofondo dopo un effetto
        if (currentSound != SOUND_BACKGROUND_MUSIC) {
            currentSound = SOUND_BACKGROUND_MUSIC;
			soundToPlay = SOUND_BACKGROUND_MUSIC;
        }
    }
}

