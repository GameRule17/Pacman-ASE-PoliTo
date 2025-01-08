#include "music.h"

#define RIT_SEMIMINIMA 8
#define RIT_MINIMA 16
#define RIT_INTERA 32
#define UPTICKS 1

const NOTE backgroundMusic[] = {
	// PACMAN MUSIC 
	// 1
	{c3,	time_semicroma},
	{pause,	time_semicroma},
	{c4,	time_semicroma},
	{pause,	time_semicroma},
	{g3,	time_semicroma},
	{pause,	time_semicroma},
	{e3,	time_semicroma},
	{pause,	time_semicroma},
	{c4,	time_semicroma},
	{g3,	time_semicroma},
	{pause,	time_croma},
	{e3,	time_croma},
	{pause,	time_croma},
	{c3,	time_semicroma}, //c3s
	{pause,	time_semicroma},
	{c4,	time_semicroma}, //c4s
	{pause,	time_semicroma},
	{a3b,	time_semicroma},
	{pause,	time_semicroma},
	{f3,	time_semicroma},
	{pause,	time_semicroma},
	{c4,	time_semicroma}, //c4s
	{a3b,	time_semicroma},
	{pause,	time_croma},
	{f3,	time_croma},
	{pause,	time_croma},
	{c3,	time_semicroma},
	{pause,	time_semicroma},
	{c4,	time_semicroma},
	{g3,	time_semicroma},
	{pause,	time_semicroma},
	{e3,	time_semicroma},
	{pause,	time_semicroma},
	{c4,	time_semicroma},
	{g3,	time_semicroma},
	{pause,	time_croma},
	{e3,	time_croma},
	{pause,	time_croma},
	{e3,	time_semicroma},
	{f3,	time_semicroma},
	{f3,	time_semicroma}, //f3s
	{pause,	time_semicroma},
	{f3,	time_semicroma}, //f3s
	{g3,	time_semicroma},
	{a3b,	time_semicroma},
	{pause,	time_semicroma},
	{a3b,	time_semicroma},
	{a3,	time_semicroma},
	{a3,	time_semicroma}, //a3s
	{pause,	time_semicroma},
	{c4,	time_croma},
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

void playSoundEffect(uint8_t sound) {
    static uint8_t currentSound = SOUND_BACKGROUND_MUSIC;
    static uint16_t currentNote = 0;
    static uint16_t ticks = 0;
    uint16_t length;
    const NOTE *effect;

    if (currentSound != sound) {
        currentSound = sound;
        currentNote = 0;
        ticks = 0;
    }

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
            break;
        case SOUND_LIFE_GAINED:
            effect = gainLifeSound;
            length = gainLifeSoundSize;
            break;
        default:
            return;
    }

    if (!isNotePlaying()) {
        ++ticks;
        if (ticks == UPTICKS) {
            ticks = 0;
            playNote(effect[currentNote++]);
        }
    }

    if (currentNote >= length) {
        currentNote = 0;
        ticks = 0;

        if (currentSound != SOUND_BACKGROUND_MUSIC) {
            currentSound = SOUND_BACKGROUND_MUSIC;
			soundToPlay = SOUND_BACKGROUND_MUSIC;
        }
    }
}

