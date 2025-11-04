#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <stdio.h>
#include <windows.h>
#include "game.h"

extern char screenBuffer[HEIGHT + 4][WIDTH + 1];
extern char prevBuffer[HEIGHT + 4][WIDTH + 1];
extern int colorBuffer[HEIGHT + 4][WIDTH + 1];
extern int prevColorBuffer[HEIGHT + 4][WIDTH + 1];

// 함수 선언
void gotoxy(int x, int y);
void hideCursor();
void setColor(int color);
void clearBuffer();
void drawToBuffer(int x, int y, char c, int color);
void renderBuffer();
void drawGame(GameState* game);
void drawBorder();
void drawPlatforms(GameState* game);
void drawEnemies(GameState* game);
void drawCoins(GameState* game);
void drawParticles(GameState* game);
void drawPlayer(GameState* game);
void drawHUD(GameState* game);

#endif