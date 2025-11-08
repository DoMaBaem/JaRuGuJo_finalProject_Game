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
#include "music.h" //[수정]music 헤더파일 추가

void run();

void run() {
    GameState game;
    MaxHeap rankings;
    char playerName[50];

    srand(time(NULL));
    hideCursor();
    system("cls");

    setColor(14);
    printf("\n\n");
    printf("   ==========================================\n");
    printf("          PLATFORM JUMP GAME\n");
    printf("   ==========================================\n\n");
    setColor(15);
    printf("   Enter your name: ");
    scanf("%s", playerName);

    loadRankings(&rankings);

    memset(prevBuffer, 0, sizeof(prevBuffer));
    memset(prevColorBuffer, 0, sizeof(prevColorBuffer));

    initGame(&game);
    strcpy(game.player.name, playerName);
    
    playBGM();  //[수정]게임 루프 시작 전 배경음 재생 시작

    while (!game.gameOver) {
        handleInput(&game);
        updatePlayer(&game);
        updateEnemies(&game);
        updateCoins(&game);
        updateParticles(&game);
        checkGameOver(&game);
        drawGame(&game);

        game.timer++;
        Sleep(50);
    }

    stopBGM(); //[수정]게임 루프 종료 후 배경음 재생 중지
    insertHeap(&rankings, game.player.name, game.player.score);
    saveRankings(&rankings);

    system("cls");
    setColor(12);
    printf("\n\n");
    printf("   ===================================\n");
    printf("          GAME OVER!\n");
    printf("   ===================================\n");
    setColor(15);
    printf("\n");
    printf("   Player: %s\n", game.player.name);
    printf("   Final Score: %d\n", game.player.score);
    printf("   Coins Collected: %d\n", game.player.coins);
    printf("   Level Reached: %d\n", game.level);
    printf("\n");
    printf("   Press any key to see rankings...\n");
    _getch();

    displayRankings(&rankings, game.player.name, game.player.score);

    printf("\n   Press any key to exit...\n");
    _getch();
}

int main() {
    run();
    return 0;
}
