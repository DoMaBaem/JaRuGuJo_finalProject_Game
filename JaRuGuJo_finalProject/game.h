#ifndef GAME_H
#define GAME_H

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include <string.h>

// ================================================
// 게임 상수 정의
// ================================================
#define WIDTH 80
#define HEIGHT 25
#define GRAVITY 1
#define MAX_ENEMIES 15
#define MAX_COINS 60
#define MAX_PLATFORMS 25
#define MAX_PARTICLES 50
#define JUMP_POWER -3

// ================================================
// 플레이어 구조체
// ================================================
typedef struct {
    int x, y;
    int velocityY;
    int velocityX;
    int onGround;
    int health;
    int score;
    int coins;
    int lives;
    int invincible;
    int invincibleTimer;
    char direction;
    char name[50];
} Player;

// ================================================
// 플랫폼 구조체
// ================================================
typedef struct {
    int x, y;
    int width;
    int active;
} Platform;

// ================================================
// 몬스터 구조체
// Type 0: 일반 몬스터, Type 1: 추적 몬스터, Type 2: 비행 몬스터
// ================================================
typedef struct {
    int x, y;
    int velocityX;
    int velocityY;
    int active;
    int type;
    int homingTimer;
    int homingDuration;
    int respawnTimer;
    int spawnX;
    int spawnY;
} Enemy;

// ================================================
// 코인 구조체
// ================================================
typedef struct {
    int x, y;
    int collected;
} Coin;

// ================================================
// 포탈 구조체
// ================================================
typedef struct {
    int x, y;
    int active;
} Portal;

// ================================================
// 파티클 구조체
// ================================================
typedef struct {
    int x, y;
    int velocityX, velocityY;
    int life;
    char symbol;
} Particle;

// ================================================
// 게임 상태 구조체
// ================================================
typedef struct {
    Player player;
    Platform platforms[MAX_PLATFORMS];
    Enemy enemies[MAX_ENEMIES];
    Coin coins[MAX_COINS];
    Particle particles[MAX_PARTICLES];
    Portal portal;
    int platformCount;
    int enemyCount;
    int coinCount;
    int particleCount;
    int gameOver;
    int level;
    int timer;
    int stageCleared;
    int inHiddenStage;
    int hiddenStageTimer;
    int returnLevel;
    Coin savedCoins[MAX_COINS];
    int savedCoinCount;
} GameState;

// ================================================
// 함수 선언
// ================================================
void initGame(GameState* game);
void initPlayer(Player* player);
void initPlatforms(GameState* game);
void initEnemies(GameState* game);
void initCoins(GameState* game);
void updatePlayer(GameState* game);
void updateEnemies(GameState* game);
void updateCoins(GameState* game);
void updateParticles(GameState* game);
void handleInput(GameState* game);
void checkGameOver(GameState* game);
void addParticle(GameState* game, int x, int y, char symbol);
void initStage2(GameState* game);
void nextStage(GameState* game);
void initHiddenStage(GameState* game);
void returnFromHiddenStage(GameState* game);

#endif
