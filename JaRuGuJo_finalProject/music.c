#define _CRT_SECURE_NO_WARNINGS
#include "music.h"

// BGM 파일의 별칭 (Alias)
// MCI 명령어에서 이 별칭을 사용해 미디어를 제어합니다.
#define BGM_ALIAS "BGM_Music" 

// --- BGM 관련 함수 구현 (MCI API 사용) ---

// 배경 음악 재생을 시작하고 루프 설정을 시도하는 함수
void playBGM() {
    // 1. 기존에 열려있는 BGM 별칭이 있다면 닫고 재설정
    // 오류가 발생해도 무시 (아직 열려있지 않은 경우)
    mciSendString("close " BGM_ALIAS, NULL, 0, NULL);

    // 2. BGM 파일 (예: bgm.mp3 또는 bgm.wav)을 열고 별칭을 지정
    // "mpegvideo" 타입은 mp3와 같은 압축 파일에 유용하며, "wait" 플래그를 사용하지 않아 비동기 처리
    if (mciSendString("open \"bgm.mp3\" type mpegvideo alias " BGM_ALIAS, NULL, 0, NULL) != 0) {
        // 파일을 찾지 못하거나 열지 못했을 경우
        printf("Error: Cannot open BGM file.\n");
        return;
    }

    // 3. BGM을 무한 반복(repeat)하여 재생 (비동기 처리)
    mciSendString("play " BGM_ALIAS " repeat", NULL, 0, NULL);
}

// 배경 음악 재생을 중지하는 함수
void stopBGM() {
    // 1. 재생 중인 BGM을 정지
    mciSendString("stop " BGM_ALIAS, NULL, 0, NULL);
    // 2. MCI 인스턴스를 닫아 메모리 해제
    mciSendString("close " BGM_ALIAS, NULL, 0, NULL);
}


// --- 효과음 관련 함수 구현 (PlaySound API 사용) ---

// 효과음을 재생하는 함수 (점프, 피격, 죽음)
void playSFX(SoundEffectType type) {
    const char* soundPath;

    // 1. 재생할 효과음 파일 경로 설정
    switch (type) {
    case SFX_JUMP:
        // S_ASYNC: 비동기 재생 (다음 코드 즉시 실행, 지연 없음)
        // S_NODEFAULT: 파일을 찾지 못해도 기본 Windows 소리를 재생하지 않음
        soundPath = "jump.wav";
        break;
    case SFX_HIT:
        soundPath = "hit.wav";
        break;
    case SFX_DIE:
        soundPath = "die.wav";
        break;
    default:
        return; // 정의되지 않은 타입은 무시
    }

    // 2. PlaySound를 사용하여 효과음 재생
    // S_ASYNC | S_NODEFAULT 플래그를 사용해 중복 재생을 시도하고 다른 작업 방해를 최소화
    // PlaySound는 매번 파일에 접근하므로, PlaySound("jump.wav", ...)를 연달아 호출하면 중복 재생 효과
    PlaySound(soundPath, NULL, SND_FILENAME | SND_ASYNC | SND_NODEFAULT);
}