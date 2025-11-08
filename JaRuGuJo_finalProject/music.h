#ifndef MUSIC_H
#define MUSIC_H

#include <windows.h>
#include <mmsystem.h>
#include <stdio.h>

// 링커에게 winmm.lib 라이브러리 사용을 명시적으로 알려줌 (사운드 API 사용을 위해 필수)
#pragma comment(lib, "winmm.lib")

// --- 효과음 유형 정의 ---
typedef enum {
    SFX_JUMP,   // 점프 시 효과음
    SFX_HIT,    // 적에게 맞았을 때 효과음
    SFX_DIE     // 생명 소진 또는 게임 오버 시 효과음
} SoundEffectType;

// --- 함수 선언 ---

// BGM (배경 음악)을 초기화하고 반복 재생 시작
void playBGM();

// BGM 재생을 멈춤
void stopBGM();

// 효과음을 재생. PlaySound 함수를 사용하여 중복 재생 및 지연 없이 처리
void playSFX(SoundEffectType type);

#endif // MUSIC_H
