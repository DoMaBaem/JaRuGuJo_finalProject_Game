#define _CRT_SECURE_NO_WARNINGS
#include "music.h"

// BGM 별칭 (Alias)
#define BGM_ALIAS L"BGM_Music"

static int bgmInitialized = 0;

// BGM 재생 함수 (무한 반복)
void playBGM(void) {
    wchar_t cmd[512];
    wchar_t errMsg[256];
    MCIERROR err;

    mciSendStringW(L"close " BGM_ALIAS, NULL, 0, NULL);

    swprintf(cmd, 512,
        L"open \"%ls\" alias %ls",
        L"C:\\Users\\ladde\\source\\repos\\JaRuGuJo_finalProject\\JaRuGuJo_finalProject\\mainstage.wav",
        BGM_ALIAS
    );

    err = mciSendStringW(cmd, NULL, 0, NULL);
    if (err) {
        mciGetErrorStringW(err, errMsg, 256);
        MessageBoxW(NULL, errMsg, L"MCI open error", MB_OK | MB_ICONERROR);
        return;
    }

    swprintf(cmd, 512, L"play %ls", BGM_ALIAS);
    err = mciSendStringW(cmd, NULL, 0, NULL);
    if (err) {
        mciGetErrorStringW(err, errMsg, 256);
        MessageBoxW(NULL, errMsg, L"MCI play error", MB_OK | MB_ICONERROR);
        return;
    }
    
    bgmInitialized = 1;
}

// BGM 무한 반복 업데이트 함수
void updateBGM(void) {
    if (!bgmInitialized) return;
    
    wchar_t cmd[128];
    wchar_t mode[64] = {0};

    swprintf(cmd, 128, L"status %ls mode", BGM_ALIAS);
    if (mciSendStringW(cmd, mode, 64, NULL) != 0) return;

    if (wcscmp(mode, L"stopped") == 0) {
        swprintf(cmd, 128, L"play %ls", BGM_ALIAS);
        mciSendStringW(cmd, NULL, 0, NULL);
    }
}


// BGM 정지 함수
void stopBGM() {
    wchar_t command[256];
    
    swprintf(command, 256, L"stop %ls", BGM_ALIAS);
    mciSendStringW(command, NULL, 0, NULL);
    
    swprintf(command, 256, L"close %ls", BGM_ALIAS);
    mciSendStringW(command, NULL, 0, NULL);
    
    bgmInitialized = 0;
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
