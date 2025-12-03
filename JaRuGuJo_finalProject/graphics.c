#define _CRT_SECURE_NO_WARNINGS
#include "graphics.h"

char screenBuffer[HEIGHT + 4][WIDTH + 1];
char prevBuffer[HEIGHT + 4][WIDTH + 1];
int colorBuffer[HEIGHT + 4][WIDTH + 1];
int prevColorBuffer[HEIGHT + 4][WIDTH + 1];

void gotoxy(int x, int y) {
    COORD coord = { x, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void hideCursor() {
    CONSOLE_CURSOR_INFO info = { 100, FALSE };
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
}

void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void clearBuffer() {
    for (int y = 0; y < HEIGHT + 4; y++) {
        for (int x = 0; x < WIDTH; x++) {
            screenBuffer[y][x] = ' ';
            colorBuffer[y][x] = 7;
        }
        screenBuffer[y][WIDTH] = '\0';
    }
}

void drawToBuffer(int x, int y, char c, int color) {
    if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT + 4) {
        screenBuffer[y][x] = c;
        colorBuffer[y][x] = color;
    }
}

void renderBuffer() {
    for (int y = 0; y < HEIGHT + 4; y++) {
        for (int x = 0; x < WIDTH; x++) {
            if (screenBuffer[y][x] != prevBuffer[y][x] || colorBuffer[y][x] != prevColorBuffer[y][x]) {
                setColor(colorBuffer[y][x]);
                gotoxy(x, y);
                printf("%c", screenBuffer[y][x]);
                prevBuffer[y][x] = screenBuffer[y][x];
                prevColorBuffer[y][x] = colorBuffer[y][x];
            }
        }
    }
}

void drawBorder() {
    for (int x = 0; x < WIDTH; x++) {
        drawToBuffer(x, 0, '#', 8);
        drawToBuffer(x, HEIGHT, '#', 8);
    }
    for (int y = 0; y <= HEIGHT; y++) {
        drawToBuffer(0, y, '#', 8);
        drawToBuffer(WIDTH - 1, y, '#', 8);
    }
}

void drawPlatforms(GameState* game) {
    for (int i = 0; i < game->platformCount; i++) {
        if (game->platforms[i].active) {
            for (int x = 0; x < game->platforms[i].width; x++) {
                drawToBuffer(game->platforms[i].x + x, game->platforms[i].y, '=', 6);
            }
        }
    }
}

void drawEnemies(GameState* game) {
    for (int i = 0; i < game->enemyCount; i++) {
        if (game->enemies[i].active) {
            if (game->enemies[i].type == 0) {
                drawToBuffer(game->enemies[i].x, game->enemies[i].y, 'M', 12);
            } else if (game->enemies[i].type == 1) {
                drawToBuffer(game->enemies[i].x, game->enemies[i].y, 'W', 13);
            } else if (game->enemies[i].type == 2) {
                drawToBuffer(game->enemies[i].x, game->enemies[i].y, 'X', 5);
            }
        }
    }
}

void drawCoins(GameState* game) {
    for (int i = 0; i < game->coinCount; i++) {
        if (!game->coins[i].collected) {
            drawToBuffer(game->coins[i].x, game->coins[i].y, '$', 14);
        }
    }
    
    // 포탈 그리기
    if (game->portal.active && !game->inHiddenStage) {
        drawToBuffer(game->portal.x, game->portal.y, '@', 10); // 초록색 @
    }
}

void drawParticles(GameState* game) {
    for (int i = 0; i < MAX_PARTICLES; i++) {
        if (game->particles[i].life > 0) {
            char sym = game->particles[i].symbol;
            if ((sym == '*' || sym == '+' || sym == '!' || sym == '.') &&
                game->particles[i].x > 0 && game->particles[i].x < WIDTH - 1 &&
                game->particles[i].y > 0 && game->particles[i].y < HEIGHT) {
                drawToBuffer(game->particles[i].x, game->particles[i].y, sym, 7);
            }
        }
    }
}

void drawPlayer(GameState* game) {
    int color = (game->player.invincible && (game->player.invincibleTimer % 4 < 2)) ? 15 : 11;
    if (game->player.direction == 'R') {
        drawToBuffer(game->player.x, game->player.y, '>', color);
    }
    else {
        drawToBuffer(game->player.x, game->player.y, '<', color);
    }
}

void drawHUD(GameState* game) {
    char hud1[WIDTH + 20];
    char hud2[WIDTH + 20];

    int healthColor = game->player.health > 50 ? 10 : (game->player.health > 25 ? 14 : 12);

    if (game->inHiddenStage) {
        sprintf(hud1, "HIDDEN STAGE! Time: %d  Score: %d  Coins: %d",
            game->hiddenStageTimer / 20, game->player.score, game->player.coins);
    } else {
        sprintf(hud1, "Score: %d  Coins: %d  Health: %d  Lives: %d  Level: %d",
            game->player.score, game->player.coins, game->player.health,
            game->player.lives, game->level);
    }
    sprintf(hud2, "[A/D] Move [W/SPC] Jump [R] Restart [ESC] Quit | M:-15HP W:-25HP X:-30HP");

    for (int i = 0; hud1[i] != '\0' && i < WIDTH - 2; i++) {
        drawToBuffer(2 + i, HEIGHT + 1, hud1[i], healthColor);
    }
    for (int i = 0; hud2[i] != '\0' && i < WIDTH - 2; i++) {
        drawToBuffer(2 + i, HEIGHT + 2, hud2[i], 8);
    }
}

void drawGame(GameState* game) {
    clearBuffer();
    drawBorder();
    drawPlatforms(game);
    drawCoins(game);
    drawEnemies(game);
    drawParticles(game);
    drawPlayer(game);
    drawHUD(game);
    if (game->stageCleared) {
        char msg1[] = "STAGE CLEAR!";
        char msg2[] = "Press > to next stage";
        int x1 = (WIDTH - strlen(msg1)) / 2;
        int x2 = (WIDTH - strlen(msg2)) / 2;
        int y = HEIGHT / 2;
        for (int i = 0; msg1[i] != '\0'; i++) {
            drawToBuffer(x1 + i, y, msg1[i], 14);
        }
        for (int i = 0; msg2[i] != '\0'; i++) {
            drawToBuffer(x2 + i, y + 2, msg2[i], 11);
        }
    }
    renderBuffer();
}