#define _CRT_SECURE_NO_WARNINGS
#include "music.h"

// BGM 별칭 (Alias)
#define BGM_ALIAS "BGM_Music"

// BGM 재생 함수 (무한 반복)
void playBGM() {
    wchar_t command[256];
    
    // 기존 BGM이 있다면 닫기
    swprintf(command, 256, L"close %hs", BGM_ALIAS);
    mciSendStringW(command, NULL, 0, NULL);

    // BGM 파일 열기 (ANSI → 유니코드 변환)
    swprintf(command, 256, L"open \".\\mainstage.wav\" type waveaudio alias %hs", BGM_ALIAS);
    if (mciSendStringW(command, NULL, 0, NULL) != 0) {
        printf("Error: Cannot open BGM file.\n");
        return;
    }

    // BGM 무한 반복 재생
    swprintf(command, 256, L"play %hs repeat", BGM_ALIAS);
    mciSendStringW(command, NULL, 0, NULL);
}

// BGM 정지 함수
void stopBGM() {
    wchar_t command[256];
    
    swprintf(command, 256, L"stop %hs", BGM_ALIAS);
    mciSendStringW(command, NULL, 0, NULL);
    
    swprintf(command, 256, L"close %hs", BGM_ALIAS);
    mciSendStringW(command, NULL, 0, NULL);
}

// 효과음 재생 함수
void playSFX(SoundEffectType type) {
    const char* soundPath;

    switch (type) {
    case SFX_JUMP:
        soundPath = "jump.wav";
        break;
    case SFX_HIT:
        soundPath = "hitsound.wav";
        break;
    case SFX_DIE:
        soundPath = "deadsound.wav";
        break;
    default:
        return;
    }

    // ANSI → 유니코드 변환
    wchar_t filename[100];
    swprintf(filename, 100, L"%hs", soundPath);
    PlaySoundW(filename, NULL, SND_FILENAME | SND_ASYNC | SND_NODEFAULT);
}
