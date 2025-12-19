#define _CRT_SECURE_NO_WARNINGS
#include "graphics.h"

// ================================================
// 더블 버퍼링을 위한 버퍼 배열
// ================================================
char screenBuffer[HEIGHT + 4][WIDTH + 1];      // 현재 프레임 버퍼
char prevBuffer[HEIGHT + 4][WIDTH + 1];        // 이전 프레임 버퍼
int colorBuffer[HEIGHT + 4][WIDTH + 1];        // 현재 프레임 색상
int prevColorBuffer[HEIGHT + 4][WIDTH + 1];    // 이전 프레임 색상

// ================================================
// 커서 위치 이동
// ================================================
void gotoxy(int x, int y) {
    COORD coord = { x, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// ================================================
// 커서 숨기기 (깨끗한 화면 표시)
// ================================================
void hideCursor() {
    CONSOLE_CURSOR_INFO info = { 100, FALSE };
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
}

// ================================================
// 콘솔 텍스트 색상 설정
// ================================================
void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

// ================================================
// 화면 버퍼 초기화 (공백과 기본 색상)
// ================================================
void clearBuffer() {
    for (int y = 0; y < HEIGHT + 4; y++) {
        for (int x = 0; x < WIDTH; x++) {
            screenBuffer[y][x] = ' ';  // 공백으로 초기화
            colorBuffer[y][x] = 7;     // 회색 (7)
        }
        screenBuffer[y][WIDTH] = '\0'; // 문자열 종료
    }
}

// ================================================
// 버퍼에 문자 그리기 (경계 체크 포함)
// ================================================
void drawToBuffer(int x, int y, char c, int color) {
    if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT + 4) {
        screenBuffer[y][x] = c;      // 문자 저장
        colorBuffer[y][x] = color;   // 색상 저장
    }
}

// ================================================
// 더블 버퍼링: 변경된 부분만 렌더링
// 깜박임 방지 및 성능 최적화
// ================================================
void renderBuffer() {
    for (int y = 0; y < HEIGHT + 4; y++) {
        for (int x = 0; x < WIDTH; x++) {
            // 이전 프레임과 비교하여 변경된 부분만 출력
            if (screenBuffer[y][x] != prevBuffer[y][x] || colorBuffer[y][x] != prevColorBuffer[y][x]) {
                setColor(colorBuffer[y][x]);  // 색상 설정
                gotoxy(x, y);                  // 커서 이동
                printf("%c", screenBuffer[y][x]); // 문자 출력
                prevBuffer[y][x] = screenBuffer[y][x];         // 이전 버퍼 갱신
                prevColorBuffer[y][x] = colorBuffer[y][x];     // 이전 색상 갱신
            }
        }
    }
}

// ================================================
// 게임 화면 테두리 그리기
// ================================================
void drawBorder() {
    // 상단과 하단 테두리
    for (int x = 0; x < WIDTH; x++) {
        drawToBuffer(x, 0, '#', 8);      // 상단
        drawToBuffer(x, HEIGHT, '#', 8); // 하단
    }
    // 좌측과 우측 테두리
    for (int y = 0; y <= HEIGHT; y++) {
        drawToBuffer(0, y, '#', 8);          // 좌측
        drawToBuffer(WIDTH - 1, y, '#', 8);  // 우측
    }
}

// ================================================
// 플랫폼 그리기 ('=' 문자, 갈색)
// ================================================
void drawPlatforms(GameState* game) {
    for (int i = 0; i < game->platformCount; i++) {
        if (game->platforms[i].active) {
            // 플랫폼 너비만큼 '=' 문자 그리기
            for (int x = 0; x < game->platforms[i].width; x++) {
                drawToBuffer(game->platforms[i].x + x, game->platforms[i].y, '=', 6);
            }
        }
    }
}

// ================================================
// 몬스터 그리기
// Type 0: 'M' (빨간색), Type 1: 'W' (파란색), Type 2: 'X' (보라색)
// ================================================
void drawEnemies(GameState* game) {
    for (int i = 0; i < game->enemyCount; i++) {
        if (game->enemies[i].active) {
            if (game->enemies[i].type == 0) {
                drawToBuffer(game->enemies[i].x, game->enemies[i].y, 'M', 12); // 일반 몬스터
            } else if (game->enemies[i].type == 1) {
                drawToBuffer(game->enemies[i].x, game->enemies[i].y, 'W', 13); // 추적 몬스터
            } else if (game->enemies[i].type == 2) {
                drawToBuffer(game->enemies[i].x, game->enemies[i].y, 'X', 5);  // 비행 몬스터
            }
        }
    }
}

// ================================================
// 코인 및 포탈 그리기
// ================================================
void drawCoins(GameState* game) {
    // 코인 그리기 ('$' 문자, 노란색)
    for (int i = 0; i < game->coinCount; i++) {
        if (!game->coins[i].collected) {
            drawToBuffer(game->coins[i].x, game->coins[i].y, '$', 14);
        }
    }
    
    // 포탈 그리기 ('@' 문자, 초록색) - 히든 스테이지 진입용
    if (game->portal.active && !game->inHiddenStage) {
        drawToBuffer(game->portal.x, game->portal.y, '@', 10);
    }
}

// ================================================
// 파티클 효과 그리기
// '*': 몬스터 처치, '+': 코인 획듍, '!': 피격, '.': 점프
// ================================================
void drawParticles(GameState* game) {
    for (int i = 0; i < MAX_PARTICLES; i++) {
        if (game->particles[i].life > 0) { // 생명이 남은 파티클만
            char sym = game->particles[i].symbol;
            // 유효한 파티클 심볼이고 화면 내에 있으면 그리기
            if ((sym == '*' || sym == '+' || sym == '!' || sym == '.') &&
                game->particles[i].x > 0 && game->particles[i].x < WIDTH - 1 &&
                game->particles[i].y > 0 && game->particles[i].y < HEIGHT) {
                drawToBuffer(game->particles[i].x, game->particles[i].y, sym, 7);
            }
        }
    }
}

// ================================================
// 플레이어 그리기 ('>' 또는 '<', 방향에 따라)
// 무적 상태일 때 깜박임 효과
// ================================================
void drawPlayer(GameState* game) {
    // 무적 상태일 때 깜박임 (4프레임마다 색상 변경)
    int color = (game->player.invincible && (game->player.invincibleTimer % 4 < 2)) ? 15 : 11;
    if (game->player.direction == 'R') {
        drawToBuffer(game->player.x, game->player.y, '>', color); // 오른쪽 향할 때
    }
    else {
        drawToBuffer(game->player.x, game->player.y, '<', color); // 왼쪽 향할 때
    }
}

// ================================================
// HUD (상단 정보 표시창) 그리기
// 점수, 코인, 체력, 생명, 레벨 정보 표시
// ================================================
void drawHUD(GameState* game) {
    char hud1[WIDTH + 20];
    char hud2[WIDTH + 20];

    // 체력에 따른 색상 변경 (초록 > 노랑 > 빨간)
    int healthColor = game->player.health > 50 ? 10 : (game->player.health > 25 ? 14 : 12);

    // 히든 스테이지일 때 타이머 표시
    if (game->inHiddenStage) {
        sprintf(hud1, "HIDDEN STAGE! Time: %d  Score: %d  Coins: %d",
            game->hiddenStageTimer / 20, game->player.score, game->player.coins);
    } else {
        // 일반 스테이지 정보 표시
        sprintf(hud1, "Score: %d  Coins: %d  Health: %d  Lives: %d  Level: %d",
            game->player.score, game->player.coins, game->player.health,
            game->player.lives, game->level);
    }
    // 조작법 및 몬스터 데미지 정보
    sprintf(hud2, "[A/D] Move [W/SPC] Jump [R] Restart [ESC] Quit | M:-15HP W:-25HP X:-30HP");

    for (int i = 0; hud1[i] != '\0' && i < WIDTH - 2; i++) {
        drawToBuffer(2 + i, HEIGHT + 1, hud1[i], healthColor);
    }
    for (int i = 0; hud2[i] != '\0' && i < WIDTH - 2; i++) {
        drawToBuffer(2 + i, HEIGHT + 2, hud2[i], 8);
    }
}

// ================================================
// 전체 게임 화면 그리기 (메인 렌더링 함수)
// ================================================
void drawGame(GameState* game) {
    clearBuffer();           // 버퍼 초기화
    drawBorder();            // 테두리 그리기
    drawPlatforms(game);     // 플랫폼 그리기
    drawCoins(game);         // 코인 및 포탈 그리기
    drawEnemies(game);       // 몬스터 그리기
    drawParticles(game);     // 파티클 효과 그리기
    drawPlayer(game);        // 플레이어 그리기
    drawHUD(game);           // HUD 그리기
    
    // 스테이지 클리어 메시지 표시
    if (game->stageCleared) {
        char msg1[] = "STAGE CLEAR!";
        char msg2[] = "Press > to next stage";
        int x1 = (WIDTH - strlen(msg1)) / 2;  // 중앙 정렬
        int x2 = (WIDTH - strlen(msg2)) / 2;
        int y = HEIGHT / 2;
        for (int i = 0; msg1[i] != '\0'; i++) {
            drawToBuffer(x1 + i, y, msg1[i], 14);      // 노란색
        }
        for (int i = 0; msg2[i] != '\0'; i++) {
            drawToBuffer(x2 + i, y + 2, msg2[i], 11);  // 하늘색
        }
    }
    renderBuffer(); // 더블 버퍼링으로 화면에 출력
}