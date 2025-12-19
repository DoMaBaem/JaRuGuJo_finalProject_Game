#define _CRT_SECURE_NO_WARNINGS
#include "music.h"

// BGM 별칭 (Alias)
#define BGM_ALIAS "BGM_Music"

// BGM 재생 함수 (무한 반복)
void playBGM() {
    // 기존 BGM이 있다면 닫기
    mciSendString("close " BGM_ALIAS, NULL, 0, NULL);

    // BGM 파일 열기
    if (mciSendString("open \"bgm.mp3\" type mpegvideo alias " BGM_ALIAS, NULL, 0, NULL) != 0) {
        printf("Error: Cannot open BGM file.\n");
        return;
    }

    // BGM 무한 반복 재생
    mciSendString("play " BGM_ALIAS " repeat", NULL, 0, NULL);
}

// BGM 정지 함수
void stopBGM() {
    mciSendString("stop " BGM_ALIAS, NULL, 0, NULL);
    mciSendString("close " BGM_ALIAS, NULL, 0, NULL);
}

// 효과음 재생 함수
void playSFX(SoundEffectType type) {
    const char* soundPath;

    switch (type) {
    case SFX_JUMP:
        soundPath = "jump.wav";
        break;
    case SFX_HIT:
        soundPath = "hit.wav";
        break;
    case SFX_DIE:
        soundPath = "die.wav";
        break;
    default:
        return;
    }

    PlaySound(soundPath, NULL, SND_FILENAME | SND_ASYNC | SND_NODEFAULT);
}
