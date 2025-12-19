#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include <string.h>
#include "game.h"
#include "graphics.h"
#include "ranking.h"
#include "music.h" 

void run();

// ================================================
// 메인 게임 루프 함수
// 게임 초기화, 실행, 종료 처리
// ================================================
void run() {
    GameState game;        // 게임 상태 구조체
    MinHeap rankings;      // 랭킹 Min Heap
    char playerName[50];   // 플레이어 이름

    srand(time(NULL));     // 랜덤 시드 초기화 (파티클, 몬스터 이동 등)
    hideCursor();          // 커서 숨기기
    system("cls");         // 화면 초기화

    setColor(14);
    printf("\n\n");
    printf("   ==========================================\n");
    printf("          PLATFORM JUMP GAME\n");
    printf("   ==========================================\n\n");
    setColor(15);
    printf("   Enter your name: ");
    scanf("%s", playerName);

    // 기존 랭킹 데이터 로드 (rankings.txt에서 읽기)
    loadRankings(&rankings);  // O(N log 10), N = 파일의 데이터 개수

    // 더블 버퍼링을 위한 버퍼 초기화
    memset(prevBuffer, 0, sizeof(prevBuffer));          // 이전 화면 버퍼 초기화
    memset(prevColorBuffer, 0, sizeof(prevColorBuffer)); // 이전 색상 버퍼 초기화

    // 게임 상태 초기화 (플레이어, 플랫폼, 몬스터, 코인)
    initGame(&game);
    strcpy(game.player.name, playerName);  // 플레이어 이름 설정
    
    // BGM 재생 시작 (MCI API 사용, 무한 반복)
    playBGM();

    // ================================================
    // 메인 게임 루프 (50ms = 20 FPS)
    // ================================================
    while (!game.gameOver) {
        handleInput(&game);        // 1. 키보드 입력 처리 (A/D/W/Space/ESC 등)
        updatePlayer(&game);       // 2. 플레이어 물리 업데이트 (중력, 충돌, 마찰)
        updateEnemies(&game);      // 3. 몬스터 AI 및 이동 (Type 0/1/2 각각 다른 패턴)
        updateCoins(&game);        // 4. 코인 수집 및 포탈 충돌 체크
        updateParticles(&game);    // 5. 파티클 효과 업데이트 (중력 적용)
        checkGameOver(&game);      // 6. 게임 오버 및 스테이지 클리어 체크
        drawGame(&game);           // 7. 화면 렌더링 (더블 버퍼링)

        game.timer++;              // 게임 타이머 증가 (프레임 카운트)
        Sleep(50);                 // 50ms 대기 = 20 FPS (1초에 20프레임)
    }

    // ================================================
    // 게임 종료 후 처리
    // ================================================
    stopBGM();  // BGM 정지
    
    // 랭킹 시스템: Min Heap에 삽입 (TOP 10만 유지)
    insertHeap(&rankings, game.player.name, game.player.score);  // O(log 10)
    saveRankings(&rankings);  // rankings.txt에 저장

    // 게임 오버 화면 출력
    system("cls");
    setColor(12);  // 빨간색
    printf("\n\n");
    printf("   ===================================\n");
    printf("          GAME OVER!\n");
    printf("   ===================================\n");
    setColor(15);  // 흰색
    printf("\n");
    printf("   Player: %s\n", game.player.name);              // 플레이어 이름
    printf("   Final Score: %d\n", game.player.score);        // 최종 점수
    printf("   Coins Collected: %d\n", game.player.coins);    // 수집한 코인 수
    printf("   Level Reached: %d\n", game.level);             // 도달한 레벨
    printf("\n");
    printf("   Press any key to see rankings...\n");
    _getch();

    // TOP 10 랭킹 표시 (Heap Sort 사용: O(10 log 10))
    displayRankings(&rankings, game.player.name, game.player.score);

    printf("\n   Press any key to exit...\n");
    _getch();  // 키 입력 대기
}

// ================================================
// 프로그램 진입점
// ================================================
int main() {
    run();  // 게임 실행
    return 0;
}
