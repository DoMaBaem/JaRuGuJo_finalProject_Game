#ifndef GAME_H
#define GAME_H

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include <string.h>

#define WIDTH 80
#define HEIGHT 25
#define GRAVITY 1
#define MAX_ENEMIES 15
#define MAX_COINS 40
#define MAX_PLATFORMS 25
#define MAX_PARTICLES 50
#define JUMP_POWER -3
#define RESPAWN_TIME 250  // 5초 (50ms * 250 = 12.5초) -> 100으로 조정하면 5초

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

typedef struct {
    int x, y;
    int width;
    int active;
} Platform;

typedef struct {
    int x, y;
    int velocityX;
    int active;
    int type;
    int homingTimer;
    int homingDuration;
    int respawnTimer;  // 리스폰 타이머 추가
    int isDead;        // 죽음 상태 추가
} Enemy;

typedef struct {
    int x, y;
    int collected;
} Coin;

typedef struct {
    int x, y;
    int velocityX, velocityY;
    int life;
    char symbol;
} Particle;

typedef struct {
    Player player;
    Platform platforms[MAX_PLATFORMS];
    Enemy enemies[MAX_ENEMIES];
    Coin coins[MAX_COINS];
    Particle particles[MAX_PARTICLES];
    int platformCount;
    int enemyCount;
    int coinCount;
    int particleCount;
    int gameOver;
    int level;
    int timer;
    int stageCleared;      // 스테이지 클리어 여부
    int targetScore;       // 스테이지 클리어 목표 점수
} GameState;

// 함수 선언
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
void checkStageCleared(GameState* game);
void nextStage(GameState* game);

#endif