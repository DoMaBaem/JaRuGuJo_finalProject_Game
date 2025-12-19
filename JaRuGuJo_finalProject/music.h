#ifndef MUSIC_H
#define MUSIC_H

#include <windows.h>
#include <mmsystem.h>
#include <stdio.h>

#pragma comment(lib, "winmm.lib")

typedef enum {
    SFX_JUMP,
    SFX_HIT,
    SFX_DIE
} SoundEffectType;

void playBGM();
void stopBGM();
void playSFX(SoundEffectType type);

#endif
