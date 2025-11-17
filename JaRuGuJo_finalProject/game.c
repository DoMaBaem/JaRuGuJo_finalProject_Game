#define _CRT_SECURE_NO_WARNINGS
#include "game.h"

void initGame(GameState* game) {
    game->gameOver = 0;
    game->level = 1;
    game->timer = 0;
    game->stageCleared = 0;
    game->targetScore = 500;  // 1스테이지 목표 점수

    initPlayer(&game->player);
    initPlatforms(game);
    initEnemies(game);
    initCoins(game);
    game->particleCount = 0;

    for (int i = 0; i < MAX_PARTICLES; i++) {
        game->particles[i].life = 0;
    }
}

void initPlayer(Player* player) {
    player->x = 10;
    player->y = HEIGHT - 5;
    player->velocityY = 0;
    player->velocityX = 0;
    player->onGround = 0;
    player->health = 100;
    player->score = 0;
    player->coins = 0;
    player->lives = 3;
    player->invincible = 0;
    player->invincibleTimer = 0;
    player->direction = 'R';
}

void initPlatforms(GameState* game) {
    game->platformCount = 0;

    // 바닥
    game->platforms[game->platformCount].x = 1;
    game->platforms[game->platformCount].y = HEIGHT - 1;
    game->platforms[game->platformCount].width = WIDTH - 2;
    game->platforms[game->platformCount].active = 1;
    game->platformCount++;

    // 레벨에 따라 플랫폼 증가
    int numPlatforms = 5 + (game->level - 1) * 2;
    if (numPlatforms > 20) numPlatforms = 20;

    // 점프력 -3, 중력 1 = 약 4~5칸 높이 점프 가능
    // 플랫폼 간 최대 높이 차이를 3칸으로 제한
    for (int i = 0; i < numPlatforms; i++) {
        int attempts = 0;
        int validPosition = 0;

        while (!validPosition && attempts < 50) {
            int newX = 10 + (rand() % 60);
            int newY = HEIGHT - 10 + (rand() % 7);  // 바닥에서 3~9칸 위
            int newWidth = 5 + (rand() % 8);

            // 다른 플랫폼과 너무 가까운지 체크
            validPosition = 1;
            for (int j = 0; j < game->platformCount; j++) {
                // x 좌표가 겹치고 y 좌표 차이가 3 이하면 skip
                if (abs(newX - game->platforms[j].x) < 15 &&
                    abs(newY - game->platforms[j].y) < 3) {
                    validPosition = 0;
                    break;
                }
            }

            if (validPosition) {
                game->platforms[game->platformCount].x = newX;
                game->platforms[game->platformCount].y = newY;
                game->platforms[game->platformCount].width = newWidth;
                game->platforms[game->platformCount].active = 1;
                game->platformCount++;
            }

            attempts++;
        }
    }
}

void initEnemies(GameState* game) {
    // 레벨에 따라 적 수 증가
    game->enemyCount = 3 + (game->level - 1);
    if (game->enemyCount > MAX_ENEMIES) game->enemyCount = MAX_ENEMIES;

    for (int i = 0; i < game->enemyCount; i++) {
        game->enemies[i].x = 20 + (rand() % 50);
        game->enemies[i].y = 5 + (rand() % 10);
        game->enemies[i].velocityX = (rand() % 2 == 0) ? 1 : -1;
        game->enemies[i].active = 1;
        game->enemies[i].type = rand() % 2;
        game->enemies[i].homingTimer = 0;
        game->enemies[i].homingDuration = 100 + (rand() % 100);
        game->enemies[i].isDead = 0;
        game->enemies[i].respawnTimer = 0;
    }
}

void initCoins(GameState* game) {
    // 레벨에 따라 코인 수 증가
    game->coinCount = 10 + (game->level - 1) * 3;
    if (game->coinCount > MAX_COINS) game->coinCount = MAX_COINS;

    for (int i = 0; i < game->coinCount; i++) {
        game->coins[i].x = 5 + (rand() % (WIDTH - 10));
        game->coins[i].y = 3 + (rand() % (HEIGHT - 5));
        game->coins[i].collected = 0;
    }
}

void addParticle(GameState* game, int x, int y, char symbol) {
    for (int i = 0; i < MAX_PARTICLES; i++) {
        if (game->particles[i].life <= 0) {
            game->particles[i].x = x;
            game->particles[i].y = y;
            game->particles[i].velocityX = (rand() % 5) - 2;
            game->particles[i].velocityY = -(rand() % 3) - 1;
            game->particles[i].life = 10 + (rand() % 10);
            game->particles[i].symbol = symbol;
            break;
        }
    }
}

void updatePlayer(GameState* game) {
    Player* p = &game->player;

    if (p->invincible) {
        p->invincibleTimer--;
        if (p->invincibleTimer <= 0) {
            p->invincible = 0;
        }
    }

    p->velocityY += GRAVITY;
    if (p->velocityY > 5) p->velocityY = 5;

    p->x += p->velocityX;
    p->y += p->velocityY;

    if (p->x < 2) p->x = 2;
    if (p->x > WIDTH - 3) p->x = WIDTH - 3;

    p->onGround = 0;

    for (int i = 0; i < game->platformCount; i++) {
        if (game->platforms[i].active) {
            if (p->y >= game->platforms[i].y - 1 &&
                p->y <= game->platforms[i].y + 1 &&
                p->x >= game->platforms[i].x &&
                p->x < game->platforms[i].x + game->platforms[i].width) {

                if (p->velocityY > 0) {
                    p->y = game->platforms[i].y - 1;
                    p->velocityY = 0;
                    p->onGround = 1;
                }
            }
        }
    }

    if (p->y >= HEIGHT - 1) {
        p->y = HEIGHT - 1;
        p->velocityY = 0;
        p->onGround = 1;
    }

    p->velocityX = 0;
}

void updateEnemies(GameState* game) {
    for (int i = 0; i < game->enemyCount; i++) {
        Enemy* e = &game->enemies[i];

        // 죽은 적의 리스폰 처리
        if (e->isDead) {
            e->respawnTimer++;
            if (e->respawnTimer >= RESPAWN_TIME) {
                // 리스폰
                e->x = 20 + (rand() % 50);
                e->y = 5 + (rand() % 10);
                e->velocityX = (rand() % 2 == 0) ? 1 : -1;
                e->active = 1;
                e->isDead = 0;
                e->respawnTimer = 0;
                e->homingTimer = 0;

                // 리스폰 파티클 효과
                for (int j = 0; j < 5; j++) {
                    addParticle(game, e->x, e->y, '*');
                }
            }
            continue;
        }

        if (!e->active) continue;

        e->x += e->velocityX;

        if (e->x <= 2 || e->x >= WIDTH - 3) {
            e->velocityX = -e->velocityX;
        }

        if (e->type == 1) {
            e->homingTimer++;
            if (e->homingTimer < e->homingDuration) {
                if (game->player.x > e->x) e->velocityX = 1;
                else if (game->player.x < e->x) e->velocityX = -1;
            }
            else {
                if (e->homingTimer > e->homingDuration + 100) {
                    e->homingTimer = 0;
                }
            }
        }

        // 플레이어가 적을 밟았는지 체크
        if (game->player.y < e->y &&
            game->player.y + 1 >= e->y &&
            abs(game->player.x - e->x) <= 1 &&
            game->player.velocityY > 0) {

            // 적 죽음 처리
            e->active = 0;
            e->isDead = 1;
            e->respawnTimer = 0;

            game->player.velocityY = JUMP_POWER;
            game->player.score += 50;

            // 죽음 파티클 효과
            for (int j = 0; j < 8; j++) {
                addParticle(game, e->x, e->y, '*');
            }
        }
        // 적과 충돌
        else if (abs(game->player.x - e->x) <= 1 &&
            abs(game->player.y - e->y) <= 1 &&
            !game->player.invincible) {

            int damage = (e->type == 0) ? 15 : 25;
            game->player.health -= damage;
            game->player.invincible = 1;
            game->player.invincibleTimer = 50;

            for (int j = 0; j < 5; j++) {
                addParticle(game, game->player.x, game->player.y, '!');
            }
        }
    }
}

void updateCoins(GameState* game) {
    for (int i = 0; i < game->coinCount; i++) {
        if (!game->coins[i].collected) {
            if (abs(game->player.x - game->coins[i].x) <= 1 &&
                abs(game->player.y - game->coins[i].y) <= 1) {

                game->coins[i].collected = 1;
                game->player.coins++;
                game->player.score += 10;

                for (int j = 0; j < 3; j++) {
                    addParticle(game, game->coins[i].x, game->coins[i].y, '+');
                }
            }
        }
    }
}

void updateParticles(GameState* game) {
    for (int i = 0; i < MAX_PARTICLES; i++) {
        if (game->particles[i].life > 0) {
            game->particles[i].x += game->particles[i].velocityX;
            game->particles[i].y += game->particles[i].velocityY;
            game->particles[i].velocityY += 1;
            game->particles[i].life--;
        }
    }
}

void handleInput(GameState* game) {
    if (_kbhit()) {
        char key = _getch();

        if (key == 27) {  // ESC
            game->gameOver = 1;
        }
        else if (key == 'a' || key == 'A') {
            game->player.velocityX = -2;
            game->player.direction = 'L';
        }
        else if (key == 'd' || key == 'D') {
            game->player.velocityX = 2;
            game->player.direction = 'R';
        }
        else if ((key == 'w' || key == 'W' || key == ' ') && game->player.onGround) {
            game->player.velocityY = JUMP_POWER;
            game->player.onGround = 0;
        }
        else if (key == 'r' || key == 'R') {
            // 게임 재시작 (같은 레벨)
            initPlayer(&game->player);
            initPlatforms(game);
            initEnemies(game);
            initCoins(game);
            game->timer = 0;
        }
    }
}

void checkStageCleared(GameState* game) {
    if (game->player.score >= game->targetScore && !game->stageCleared) {
        game->stageCleared = 1;
    }
}

void nextStage(GameState* game) {
    game->level++;
    game->targetScore = game->targetScore + 300 + (game->level * 100);
    game->stageCleared = 0;

    // 체력 보너스
    game->player.health += 20;
    if (game->player.health > 100) game->player.health = 100;

    initPlatforms(game);
    initEnemies(game);
    initCoins(game);

    // 플레이어 위치 리셋
    game->player.x = 10;
    game->player.y = HEIGHT - 5;
    game->player.velocityY = 0;
}

void checkGameOver(GameState* game) {
    if (game->player.health <= 0) {
        game->player.lives--;

        if (game->player.lives > 0) {
            game->player.health = 100;
            game->player.x = 10;
            game->player.y = HEIGHT - 5;
            game->player.velocityY = 0;
            game->player.invincible = 1;
            game->player.invincibleTimer = 100;
        }
        else {
            game->gameOver = 1;
        }
    }

    checkStageCleared(game);
}