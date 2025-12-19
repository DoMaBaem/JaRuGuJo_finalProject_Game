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
void showMenu(MinHeap* rankings);

void showMenu(MinHeap* rankings) {
    int selected = 0;

    while (1) {
        system("cls");
        setColor(14);
        printf("\n\n");
        printf("   ==========================================\n");
        printf("          PLATFORM JUMP GAME\n");
        printf("   ==========================================\n\n");
        setColor(15);

        if (selected == 0) {
            setColor(11);
            printf("   >> 1. START GAME\n");
            setColor(15);
            printf("      2. VIEW RANKINGS\n");
            printf("      3. EXIT\n");
        }
        else if (selected == 1) {
            setColor(15);
            printf("      1. START GAME\n");
            setColor(11);
            printf("   >> 2. VIEW RANKINGS\n");
            setColor(15);
            printf("      3. EXIT\n");
        }
        else {
            setColor(15);
            printf("      1. START GAME\n");
            printf("      2. VIEW RANKINGS\n");
            setColor(11);
            printf("   >> 3. EXIT\n");
            setColor(15);
        }

        printf("\n   Use W/S to navigate, ENTER to select\n");

        char key = _getch();
        if (key == 'w' || key == 'W') {
            selected--;
            if (selected < 0) selected = 2;
        }
        else if (key == 's' || key == 'S') {
            selected++;
            if (selected > 2) selected = 0;
        }
        else if (key == 13) {
            if (selected == 0) {
                return;
            }
            else if (selected == 1) {
                system("cls");
                displayRankings(rankings, "", 0);
                printf("\n   Press any key to return to menu...\n");
                _getch();
            }
            else {
                exit(0);
            }
        }
    }
}

void run() {
    GameState game;
    MinHeap rankings;
    char playerName[50];
    int playAgain = 1;

    srand(time(NULL));
    hideCursor();

    loadRankings(&rankings);

    // WAV 파일 존재 확인
    FILE* fp = fopen("mainstage.wav", "r");
    if (fp == NULL) {
        printf("\n [경고] mainstage.wav 파일을 찾을 수 없습니다! 폴더를 확인하세요.\n");
        _getch();
    } else {
        fclose(fp);
    }

    while (playAgain) {
        system("cls");
        setColor(14);
        printf("\n\n");
        printf("   ==========================================\n");
        printf("          PLATFORM JUMP GAME\n");
        printf("   ==========================================\n\n");
        setColor(15);
        printf("   Enter your name: ");
        scanf("%s", playerName);

        showMenu(&rankings);

        memset(prevBuffer, 0, sizeof(prevBuffer));
        memset(prevColorBuffer, 0, sizeof(prevColorBuffer));

        initGame(&game);
        strcpy(game.player.name, playerName);

        playBGM();

        while (!game.gameOver) {
            handleInput(&game);

            if (game.stageCleared && _kbhit()) {
                char key = _getch();
                if (key == 'n' || key == 'N') {
                    nextStage(&game);
                }
            }

            updatePlayer(&game);
            updateEnemies(&game);
            updateCoins(&game);
            updateParticles(&game);
            checkGameOver(&game);
            drawGame(&game);

            game.timer++;
            Sleep(50);
        }

        stopBGM();
        
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
        printf("   Stage Reached: %d\n", game.level);
        printf("\n");
        printf("   Press any key to see rankings...\n");
        _getch();

        displayRankings(&rankings, game.player.name, game.player.score);

        printf("\n   Play again? (Y/N): ");
        char choice = _getch();
        if (choice != 'y' && choice != 'Y') {
            playAgain = 0;
        }
    }
}

int main() {
    run();
    return 0;
}
