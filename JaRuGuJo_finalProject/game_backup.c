#define _CRT_SECURE_NO_WARNINGS
#include "game.h"
#include "music.h" //[����] music �������?�߰�

void initPlayer(Player* player) {
    player->x = 5;
    player->y = HEIGHT - 3;
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
    game->platformCount = 24;
    
    // ?�탈 ?�정 (?�랫??22 ??
    game->portal.x = 47;
    game->portal.y = HEIGHT - 19;
    game->portal.active = 1;

    game->platforms[0].x = 1;
    game->platforms[0].y = HEIGHT - 2;
    game->platforms[0].width = WIDTH - 2;
    game->platforms[0].active = 1;

    game->platforms[1].x = 5;
    game->platforms[1].y = HEIGHT - 4;
    game->platforms[1].width = 10;
    game->platforms[1].active = 1;

    game->platforms[2].x = 12;
    game->platforms[2].y = HEIGHT - 4;
    game->platforms[2].width = 10;
    game->platforms[2].active = 1;

    game->platforms[3].x = 25;
    game->platforms[3].y = HEIGHT - 4;
    game->platforms[3].width = 10;
    game->platforms[3].active = 1;

    game->platforms[4].x = 32;
    game->platforms[4].y = HEIGHT - 4;
    game->platforms[4].width = 10;
    game->platforms[4].active = 1;

    game->platforms[5].x = 45;
    game->platforms[5].y = HEIGHT - 4;
    game->platforms[5].width = 10;
    game->platforms[5].active = 1;

    game->platforms[6].x = 52;
    game->platforms[6].y = HEIGHT - 4;
    game->platforms[6].width = 10;
    game->platforms[6].active = 1;

    game->platforms[7].x = 65;
    game->platforms[7].y = HEIGHT - 4;
    game->platforms[7].width = 10;
    game->platforms[7].active = 1;

    game->platforms[8].x = 10;
    game->platforms[8].y = HEIGHT - 6;
    game->platforms[8].width = 10;
    game->platforms[8].active = 1;

    game->platforms[9].x = 30;
    game->platforms[9].y = HEIGHT - 6;
    game->platforms[9].width = 10;
    game->platforms[9].active = 1;

    game->platforms[10].x = 50;
    game->platforms[10].y = HEIGHT - 6;
    game->platforms[10].width = 10;
    game->platforms[10].active = 1;

    game->platforms[11].x = 70;
    game->platforms[11].y = HEIGHT - 6;
    game->platforms[11].width = 8;
    game->platforms[11].active = 1;

    game->platforms[12].x = 15;
    game->platforms[12].y = HEIGHT - 8;
    game->platforms[12].width = 10;
    game->platforms[12].active = 1;

    game->platforms[13].x = 35;
    game->platforms[13].y = HEIGHT - 8;
    game->platforms[13].width = 10;
    game->platforms[13].active = 1;

    game->platforms[14].x = 55;
    game->platforms[14].y = HEIGHT - 8;
    game->platforms[14].width = 10;
    game->platforms[14].active = 1;

    game->platforms[15].x = 5;
    game->platforms[15].y = HEIGHT - 10;
    game->platforms[15].width = 10;
    game->platforms[15].active = 1;

    game->platforms[16].x = 25;
    game->platforms[16].y = HEIGHT - 10;
    game->platforms[16].width = 10;
    game->platforms[16].active = 1;

    game->platforms[17].x = 45;
    game->platforms[17].y = HEIGHT - 10;
    game->platforms[17].width = 10;
    game->platforms[17].active = 1;

    game->platforms[18].x = 65;
    game->platforms[18].y = HEIGHT - 10;
    game->platforms[18].width = 10;
    game->platforms[18].active = 1;

    game->platforms[19].x = 35;
    game->platforms[19].y = HEIGHT - 12;
    game->platforms[19].width = 12;
    game->platforms[19].active = 1;

    game->platforms[20].x = 10;
    game->platforms[20].y = HEIGHT - 14;
    game->platforms[20].width = 6;
    game->platforms[20].active = 1;

    game->platforms[21].x = 25;
    game->platforms[21].y = HEIGHT - 16;
    game->platforms[21].width = 5;
    game->platforms[21].active = 1;

    game->platforms[22].x = 45;
    game->platforms[22].y = HEIGHT - 18;
    game->platforms[22].width = 6;
    game->platforms[22].active = 1;

    game->platforms[23].x = 65;
    game->platforms[23].y = HEIGHT - 20;
    game->platforms[23].width = 5;
    game->platforms[23].active = 1;
}

// ================================================
// Stage 1 몬스터 초기화 (14개)
// Type 0: 일반 몬스터, Type 1: 추적 몬스터
// ================================================
void initEnemies(GameState* game) {
    game->enemyCount = 14;

    game->enemies[0].x = 11;
    game->enemies[0].y = HEIGHT - 5;
    game->enemies[0].velocityX = 1;
    game->enemies[0].velocityY = 0;
    game->enemies[0].active = 1;
    game->enemies[0].type = 0;
    game->enemies[0].homingTimer = 0;
    game->enemies[0].homingDuration = 0;
    game->enemies[0].respawnTimer = 0;
    game->enemies[0].spawnX = 11;
    game->enemies[0].spawnY = HEIGHT - 5;

    int positions[][2] = {{33, HEIGHT-7}, {18, HEIGHT-9}, {38, HEIGHT-9}, {58, HEIGHT-9}, {8, HEIGHT-11}, {28, HEIGHT-11}, {48, HEIGHT-11}, {68, HEIGHT-11}, {38, HEIGHT-13}, {12, HEIGHT-15}, {27, HEIGHT-17}, {47, HEIGHT-19}, {67, HEIGHT-21}};
    int velocities[] = {-1, 2, -1, 2, 1, -2, 1, -2, 2, 2, -2, 2, -2};
    int types[] = {0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1};
    
    for (int i = 1; i < 14; i++) {
        game->enemies[i].x = positions[i-1][0];
        game->enemies[i].y = positions[i-1][1];
        game->enemies[i].velocityX = velocities[i-1];
        game->enemies[i].velocityY = 0;
        game->enemies[i].active = 1;
        game->enemies[i].type = types[i-1];
        game->enemies[i].homingTimer = 0;
        game->enemies[i].homingDuration = 0;
        game->enemies[i].respawnTimer = 0;
        game->enemies[i].spawnX = positions[i-1][0];
        game->enemies[i].spawnY = positions[i-1][1];
    }
}

// ================================================
// Stage 1 코인 초기화 (38개)
// ================================================
void initCoins(GameState* game) {
    game->coinCount = 38;

    game->coins[0].x = 10;
    game->coins[0].y = HEIGHT - 5;
    game->coins[0].collected = 0;

    game->coins[1].x = 13;
    game->coins[1].y = HEIGHT - 5;
    game->coins[1].collected = 0;

    game->coins[2].x = 20;
    game->coins[2].y = HEIGHT - 7;
    game->coins[2].collected = 0;

    game->coins[3].x = 23;
    game->coins[3].y = HEIGHT - 7;
    game->coins[3].collected = 0;

    game->coins[4].x = 30;
    game->coins[4].y = HEIGHT - 9;
    game->coins[4].collected = 0;

    game->coins[5].x = 33;
    game->coins[5].y = HEIGHT - 9;
    game->coins[5].collected = 0;

    game->coins[6].x = 40;
    game->coins[6].y = HEIGHT - 7;
    game->coins[6].collected = 0;

    game->coins[7].x = 43;
    game->coins[7].y = HEIGHT - 7;
    game->coins[7].collected = 0;

    game->coins[8].x = 50;
    game->coins[8].y = HEIGHT - 5;
    game->coins[8].collected = 0;

    game->coins[9].x = 53;
    game->coins[9].y = HEIGHT - 5;
    game->coins[9].collected = 0;

    game->coins[10].x = 60;
    game->coins[10].y = HEIGHT - 7;
    game->coins[10].collected = 0;

    game->coins[11].x = 63;
    game->coins[11].y = HEIGHT - 7;
    game->coins[11].collected = 0;

    game->coins[12].x = 70;
    game->coins[12].y = HEIGHT - 9;
    game->coins[12].collected = 0;

    game->coins[13].x = 73;
    game->coins[13].y = HEIGHT - 9;
    game->coins[13].collected = 0;

    game->coins[14].x = 15;
    game->coins[14].y = HEIGHT - 11;
    game->coins[14].collected = 0;

    game->coins[15].x = 18;
    game->coins[15].y = HEIGHT - 11;
    game->coins[15].collected = 0;

    game->coins[16].x = 35;
    game->coins[16].y = HEIGHT - 11;
    game->coins[16].collected = 0;

    game->coins[17].x = 38;
    game->coins[17].y = HEIGHT - 11;
    game->coins[17].collected = 0;

    game->coins[18].x = 55;
    game->coins[18].y = HEIGHT - 11;
    game->coins[18].collected = 0;

    game->coins[19].x = 58;
    game->coins[19].y = HEIGHT - 11;
    game->coins[19].collected = 0;

    game->coins[20].x = 25;
    game->coins[20].y = HEIGHT - 13;
    game->coins[20].collected = 0;

    game->coins[21].x = 28;
    game->coins[21].y = HEIGHT - 13;
    game->coins[21].collected = 0;

    game->coins[22].x = 45;
    game->coins[22].y = HEIGHT - 13;
    game->coins[22].collected = 0;

    game->coins[23].x = 48;
    game->coins[23].y = HEIGHT - 13;
    game->coins[23].collected = 0;

    game->coins[24].x = 65;
    game->coins[24].y = HEIGHT - 13;
    game->coins[24].collected = 0;

    game->coins[25].x = 68;
    game->coins[25].y = HEIGHT - 13;
    game->coins[25].collected = 0;

    game->coins[26].x = 35;
    game->coins[26].y = HEIGHT - 15;
    game->coins[26].collected = 0;

    game->coins[27].x = 39;
    game->coins[27].y = HEIGHT - 15;
    game->coins[27].collected = 0;

    game->coins[28].x = 7;
    game->coins[28].y = HEIGHT - 5;
    game->coins[28].collected = 0;

    game->coins[29].x = 17;
    game->coins[29].y = HEIGHT - 5;
    game->coins[29].collected = 0;

    game->coins[30].x = 27;
    game->coins[30].y = HEIGHT - 5;
    game->coins[30].collected = 0;

    game->coins[31].x = 37;
    game->coins[31].y = HEIGHT - 5;
    game->coins[31].collected = 0;

    game->coins[32].x = 47;
    game->coins[32].y = HEIGHT - 5;
    game->coins[32].collected = 0;

    game->coins[33].x = 57;
    game->coins[33].y = HEIGHT - 5;
    game->coins[33].collected = 0;

    game->coins[34].x = 67;
    game->coins[34].y = HEIGHT - 5;
    game->coins[34].collected = 0;

    game->coins[35].x = 72;
    game->coins[35].y = HEIGHT - 7;
    game->coins[35].collected = 0;

    game->coins[36].x = 8;
    game->coins[36].y = HEIGHT - 11;
    game->coins[36].collected = 0;

    game->coins[37].x = 28;
    game->coins[37].y = HEIGHT - 11;
    game->coins[37].collected = 0;
}

// ================================================
// 파티클 시스템
// ================================================
void addParticle(GameState* game, int x, int y, char symbol) {
    for (int i = 0; i < MAX_PARTICLES; i++) {
        if (game->particles[i].life <= 0) {
            game->particles[i].x = x;
            game->particles[i].y = y;
            game->particles[i].velocityX = (rand() % 3) - 1;
            game->particles[i].velocityY = -(rand() % 3 + 1);
            game->particles[i].life = 10;
            game->particles[i].symbol = symbol;
            break;
        }
    }
}

void updateParticles(GameState* game) {
    for (int i = 0; i < MAX_PARTICLES; i++) {
        if (game->particles[i].life > 0) {
            game->particles[i].x += game->particles[i].velocityX;
            game->particles[i].y += game->particles[i].velocityY;
            game->particles[i].velocityY++;
            game->particles[i].life--;
        }
    }
}

// ================================================
// 플레이어 업데이트
// ================================================
void updatePlayer(GameState* game) {
    Player* player = &game->player;

    // 중력 적용
    player->velocityY += GRAVITY;
    if (player->velocityY > 10) player->velocityY = 10;

    player->y += player->velocityY;
    player->x += player->velocityX;

    // 화면 경계 체크
    if (player->x < 1) {
        player->x = 1;
        player->velocityX = 0;
    }
    if (player->x >= WIDTH - 1) {
        player->x = WIDTH - 2;
        player->velocityX = 0;
    }

    player->onGround = 0;

    // 플랫폼 충돌 검사
    for (int i = 0; i < game->platformCount; i++) {
        if (game->platforms[i].active) {
            int onPlatformX = (player->x >= game->platforms[i].x && player->x < game->platforms[i].x + game->platforms[i].width);
            
            if (onPlatformX) {
                if (player->y == game->platforms[i].y && player->velocityY >= 0) {
                    player->velocityY = 0;
                    player->onGround = 1;
                }
                else if (player->y > game->platforms[i].y && player->y <= game->platforms[i].y + 1 && player->velocityY > 0) {
                    player->y = game->platforms[i].y;
                    player->velocityY = 0;
                    player->onGround = 1;
                }
            }
        }
    }

    // 낙사 처리
    if (player->y >= HEIGHT - 1) {
        player->lives--;
        if (player->lives > 0) {
            player->health = 100;
            player->x = 5;
            player->y = HEIGHT - 3;
            player->velocityY = 0;
            player->velocityX = 0;
        }
        else {
            player->health = 0;
        }
    }

    // 무적 시간 처리
    if (player->invincibleTimer > 0) {
        player->invincibleTimer--;
        if (player->invincibleTimer == 0) {
            player->invincible = 0;
        }
    }

    // 마찰력 적용
    if (!player->invincible || player->invincibleTimer < 20) {
        if (player->onGround && player->velocityX != 0) {
            player->velocityX = (int)(player->velocityX * 0.8);
        } else if (!player->onGround) {
            player->velocityX = (int)(player->velocityX * 0.95);
        }
    }
    else {
        player->velocityX = (int)(player->velocityX * 0.8);
    }
}

void updateEnemies(GameState* game) {
    for (int i = 0; i < game->enemyCount; i++) {
        if (!game->enemies[i].active && game->enemies[i].respawnTimer > 0) {
            game->enemies[i].respawnTimer--;
            if (game->enemies[i].respawnTimer == 0) {
                game->enemies[i].active = 1;
                game->enemies[i].x = game->enemies[i].spawnX;
                game->enemies[i].y = game->enemies[i].spawnY;
            }
        }
        
        if (game->enemies[i].active) {
            if (game->enemies[i].type == 2) {
                game->enemies[i].x += game->enemies[i].velocityX;
                game->enemies[i].y += game->enemies[i].velocityY;
                if (game->enemies[i].x <= 2 || game->enemies[i].x >= WIDTH - 3) {
                    game->enemies[i].velocityX *= -1;
                }
                if (game->enemies[i].y <= 1 || game->enemies[i].y >= HEIGHT - 1) {
                    game->enemies[i].velocityY *= -1;
                }
            } else if (game->enemies[i].type == 1) {
                int speed = abs(game->enemies[i].velocityX);
                if (game->enemies[i].homingDuration > 0) {
                    game->enemies[i].homingDuration--;
                    if (game->player.x > game->enemies[i].x) {
                        game->enemies[i].velocityX = speed;
                    }
                    else if (game->player.x < game->enemies[i].x) {
                        game->enemies[i].velocityX = -speed;
                    }
                } else {
                    game->enemies[i].homingTimer++;
                    if (game->enemies[i].homingTimer >= 120) {
                        game->enemies[i].homingDuration = 80;
                        game->enemies[i].homingTimer = 0;
                    }
                }
            }

            if (game->enemies[i].type != 2) {
                game->enemies[i].x += game->enemies[i].velocityX;
                if (game->enemies[i].x <= 2 || game->enemies[i].x >= WIDTH - 3) {
                    game->enemies[i].velocityX *= -1;
                }
            }

            int dx = abs(game->player.x - game->enemies[i].x);
            int dy = game->player.y - game->enemies[i].y;

            if (dx <= 1 && dy == -1 && game->player.velocityY > 0) {
                game->enemies[i].active = 0;
                game->enemies[i].respawnTimer = 100;
                game->player.velocityY = -4;
                if (game->enemies[i].type == 0) {
                    game->player.score += 100;
                } else if (game->enemies[i].type == 1) {
                    game->player.score += 150;
                } else {
                    game->player.score += 200;
                }
                for (int j = 0; j < 5; j++) {
                    addParticle(game, game->enemies[i].x, game->enemies[i].y, '*');
                }
            }
            else if (dx <= 1 && dy == 0 && !game->player.invincible) {
                int damage = (game->enemies[i].type == 0) ? 15 : (game->enemies[i].type == 1) ? 25 : 30;
                game->player.health -= damage;
                game->player.invincible = 1;
                game->player.invincibleTimer = 30;
                playSFX(SFX_HIT); //[����] �ǰ� ȿ���� ���?
                if (game->player.x < game->enemies[i].x) {
                    game->player.velocityX = -2;
                }
                else {
                    game->player.velocityX = 2;
                }
                game->player.velocityY = -2;
                for (int j = 0; j < 3; j++) {
                    addParticle(game, game->player.x, game->player.y, '!');
                }
            }
        }
    }
}

// ================================================
// 코인 및 포탈 업데이트
// ================================================
void updateCoins(GameState* game) {
    // 코인 수집 검사
    for (int i = 0; i < game->coinCount; i++) {
        if (!game->coins[i].collected) {
            if (abs(game->player.x - game->coins[i].x) <= 1 &&
                abs(game->player.y - game->coins[i].y) <= 1 &&
                game->coins[i].y <= game->player.y) {
                game->coins[i].collected = 1;
                game->player.coins++;
                game->player.score += 50;
                addParticle(game, game->coins[i].x, game->coins[i].y, '+');
            }
        }
    }
    
    // ?�탈 충돌 검??
    if (game->portal.active && !game->inHiddenStage) {
        if (abs(game->player.x - game->portal.x) <= 1 &&
            abs(game->player.y - game->portal.y) <= 1) {
            initHiddenStage(game);
        }
    }
    
    // ?�든 ?�테?��? ?�?�머
    if (game->inHiddenStage) {
        game->hiddenStageTimer--;
        if (game->hiddenStageTimer <= 0) {
            returnFromHiddenStage(game);
        }
    }
}

// ================================================
// 키보드 입력 처리
// ================================================
void handleInput(GameState* game) {
    static int leftPressed = 0, rightPressed = 0;
    
    if (_kbhit()) {
        char key = _getch();

        // ESC: 게임 종료
        if (key == 27) {
            game->gameOver = 1;
        }

        // 방향키 입력
        if (key == -32) {
            key = _getch();
            if (key == 75) {
                leftPressed = 1;
                game->player.direction = 'L';
            }
            if (key == 77) {
                rightPressed = 1;
                game->player.direction = 'R';
            }
            if (key == 72) {
                if (game->player.onGround) {
                    int jumpPower = game->inHiddenStage ? -5 : JUMP_POWER;
                    game->player.velocityY = jumpPower;
                    playSFX(SFX_JUMP); //[����] ���� ȿ���� �߻�
                    addParticle(game, game->player.x, game->player.y + 1, '.');
                }
            }
            if (key == 80) {
                if (game->player.onGround) {
                    game->player.y += 2;
                }
            }
        }

        if (key == ' ') {
            if (game->player.onGround) {
                int jumpPower = game->inHiddenStage ? -5 : JUMP_POWER;
                game->player.velocityY = jumpPower;
                playSFX(SFX_JUMP);     // [����] ���� ȿ���� ���?
                addParticle(game, game->player.x, game->player.y + 1, '.');
            }
        }

        if (key == 'a' || key == 'A') {
            leftPressed = 1;
            game->player.direction = 'L';
        }
        
        if (key == 'd' || key == 'D') {
            rightPressed = 1;
            game->player.direction = 'R';
        }
        
        if (key == 'w' || key == 'W') {
            if (game->player.onGround) {
                int jumpPower = game->inHiddenStage ? -5 : JUMP_POWER;
                game->player.velocityY = jumpPower;
                addParticle(game, game->player.x, game->player.y + 1, '.');
            }
        }

        if (key == 'r' || key == 'R') {
            initPlayer(&game->player);
            if (game->level == 1) {
                initPlatforms(game);
                initEnemies(game);
                initCoins(game);
            } else {
                initStage2(game);
            }
        }
        
        if (key == ',' || key == '<') {
            if (game->level > 1) {
                game->level--;
                game->player.x = 5;
                game->player.y = HEIGHT - 3;
                if (game->level == 1) {
                    initPlatforms(game);
                    initEnemies(game);
                    initCoins(game);
                } else {
                    initStage2(game);
                }
            }
        }
        
        if (key == '.' || key == '>') {
            if (game->level < 2) {
                nextStage(game);
            }
        }
        
        if (key == '/' || key == '?') {
            if (!game->inHiddenStage) {
                initHiddenStage(game);
            }
        }
    }
    
    if (leftPressed) {
        game->player.velocityX = -1;
        leftPressed = 0;
    }
    if (rightPressed) {
        game->player.velocityX = 1;
        rightPressed = 0;
    }
}

// ================================================
// 게임 오버 및 스테이지 클리어 체크
// ================================================
void checkGameOver(GameState* game) {
    // 체력 0 이하 시 생명 감소
    if (game->player.health <= 0) {
        game->player.lives--;
        if (game->player.lives > 0) {
            game->player.health = 100;
            game->player.x = 5;
            game->player.y = HEIGHT - 3;
            game->player.velocityY = 0;
            game->player.velocityX = 0;
            game->player.invincible = 1;
            game->player.invincibleTimer = 60;
        }
        else {
            playSFX(SFX_DIE); //[����] ���� ȿ���� ���?
            game->gameOver = 1;
        }
    }

    // 모든 코인 수집 시 스테이지 클리어
    int allCoinsCollected = 1;
    for (int i = 0; i < game->coinCount; i++) {
        if (!game->coins[i].collected) {
            allCoinsCollected = 0;
            break;
        }
    }

    if (allCoinsCollected) {
        game->player.score += 500;
        game->stageCleared = 1;
        if (game->level < 2) {
            Sleep(1500);
            nextStage(game);
        } else {
            game->gameOver = 1;
        }
    }

}

// ================================================
// Stage 2 초기화
// 플랫폼: 20개, 몬스터: 12개 (Type 1: 8개, Type 2: 4개), 코인: 20개
// ================================================
void initStage2(GameState* game) {
    // 플랫폼 배치
    game->platformCount = 20;
    game->platforms[0].x = 1; game->platforms[0].y = HEIGHT - 2; game->platforms[0].width = 15; game->platforms[0].active = 1;
    game->platforms[1].x = 25; game->platforms[1].y = HEIGHT - 2; game->platforms[1].width = 15; game->platforms[1].active = 1;
    game->platforms[2].x = 50; game->platforms[2].y = HEIGHT - 2; game->platforms[2].width = 15; game->platforms[2].active = 1;
    game->platforms[3].x = 8; game->platforms[3].y = HEIGHT - 5; game->platforms[3].width = 8; game->platforms[3].active = 1;
    game->platforms[4].x = 22; game->platforms[4].y = HEIGHT - 6; game->platforms[4].width = 6; game->platforms[4].active = 1;
    game->platforms[5].x = 35; game->platforms[5].y = HEIGHT - 8; game->platforms[5].width = 8; game->platforms[5].active = 1;
    game->platforms[6].x = 50; game->platforms[6].y = HEIGHT - 7; game->platforms[6].width = 7; game->platforms[6].active = 1;
    game->platforms[7].x = 65; game->platforms[7].y = HEIGHT - 9; game->platforms[7].width = 6; game->platforms[7].active = 1;
    game->platforms[8].x = 12; game->platforms[8].y = HEIGHT - 10; game->platforms[8].width = 7; game->platforms[8].active = 1;
    game->platforms[9].x = 28; game->platforms[9].y = HEIGHT - 12; game->platforms[9].width = 8; game->platforms[9].active = 1;
    game->platforms[10].x = 45; game->platforms[10].y = HEIGHT - 13; game->platforms[10].width = 6; game->platforms[10].active = 1;
    game->platforms[11].x = 60; game->platforms[11].y = HEIGHT - 11; game->platforms[11].width = 7; game->platforms[11].active = 1;
    game->platforms[12].x = 5; game->platforms[12].y = HEIGHT - 15; game->platforms[12].width = 6; game->platforms[12].active = 1;
    game->platforms[13].x = 20; game->platforms[13].y = HEIGHT - 17; game->platforms[13].width = 5; game->platforms[13].active = 1;
    game->platforms[14].x = 35; game->platforms[14].y = HEIGHT - 18; game->platforms[14].width = 6; game->platforms[14].active = 1;
    game->platforms[15].x = 50; game->platforms[15].y = HEIGHT - 16; game->platforms[15].width = 5; game->platforms[15].active = 1;
    game->platforms[16].x = 65; game->platforms[16].y = HEIGHT - 19; game->platforms[16].width = 5; game->platforms[16].active = 1;
    game->platforms[17].x = 15; game->platforms[17].y = HEIGHT - 21; game->platforms[17].width = 6; game->platforms[17].active = 1;
    game->platforms[18].x = 40; game->platforms[18].y = HEIGHT - 22; game->platforms[18].width = 5; game->platforms[18].active = 1;
    game->platforms[19].x = 60; game->platforms[19].y = HEIGHT - 23; game->platforms[19].width = 5; game->platforms[19].active = 1;
    
    // Type 1 몬스터 배치 (추적 몬스터 8개)
    game->enemyCount = 12;
    int pos[][2] = {{10,HEIGHT-6},{25,HEIGHT-7},{38,HEIGHT-9},{52,HEIGHT-8},{67,HEIGHT-10},{15,HEIGHT-11},{30,HEIGHT-13},{47,HEIGHT-14}};
    int vel[] = {2,-2,2,-2,2,-2,2,-2};
    for (int i = 0; i < 8; i++) {
        game->enemies[i].x = pos[i][0]; game->enemies[i].y = pos[i][1]; game->enemies[i].velocityX = vel[i]; game->enemies[i].velocityY = 0;
        game->enemies[i].active = 1; game->enemies[i].type = 1; game->enemies[i].homingTimer = 0; game->enemies[i].homingDuration = 0;
        game->enemies[i].respawnTimer = 0; game->enemies[i].spawnX = pos[i][0]; game->enemies[i].spawnY = pos[i][1];
    }
    // Type 2 몬스터 배치 (비행 몬스터 4개)
    int dpos[][2] = {{20,HEIGHT-15},{45,HEIGHT-18},{60,HEIGHT-12},{35,HEIGHT-20}};
    int dvel[][2] = {{1,-1},{-1,1},{1,1},{-1,-1}};
    for (int i = 0; i < 4; i++) {
        game->enemies[8+i].x = dpos[i][0]; game->enemies[8+i].y = dpos[i][1];
        game->enemies[8+i].velocityX = dvel[i][0]; game->enemies[8+i].velocityY = dvel[i][1];
        game->enemies[8+i].active = 1; game->enemies[8+i].type = 2; game->enemies[8+i].homingTimer = 0; game->enemies[8+i].homingDuration = 0;
        game->enemies[8+i].respawnTimer = 0; game->enemies[8+i].spawnX = dpos[i][0]; game->enemies[8+i].spawnY = dpos[i][1];
    }
    
    // 코인 배치 (20개)
    game->coinCount = 20;
    int cpos[][2] = {{10,HEIGHT-6},{24,HEIGHT-7},{37,HEIGHT-9},{52,HEIGHT-8},{67,HEIGHT-10},{14,HEIGHT-11},{30,HEIGHT-13},{47,HEIGHT-14},{62,HEIGHT-12},{7,HEIGHT-16},{22,HEIGHT-18},{37,HEIGHT-19},{52,HEIGHT-17},{67,HEIGHT-20},{17,HEIGHT-22},{42,HEIGHT-23},{62,HEIGHT-24},{32,HEIGHT-13},{48,HEIGHT-14},{70,HEIGHT-10}};
    for (int i = 0; i < 20; i++) {
        game->coins[i].x = cpos[i][0]; game->coins[i].y = cpos[i][1]; game->coins[i].collected = 0;
    }
}

void initHiddenStage(GameState* game) {
    game->inHiddenStage = 1;
    game->hiddenStageTimer = 200; // 10�?(200?�레??
    game->returnLevel = game->level;
    
    // 간단???�랫??(바닥�?
    game->platformCount = 1;
    game->platforms[0].x = 1;
    game->platforms[0].y = HEIGHT - 2;
    game->platforms[0].width = WIDTH - 2;
    game->platforms[0].active = 1;
    
    // 몬스???�음
    game->enemyCount = 0;
    
    // 코인 50�?(많이!)
    for (int i = 0; i < MAX_COINS; i++) {
        game->coins[i].collected = 1;
    }
    game->coinCount = 50;
    for (int i = 0; i < 50; i++) {
        game->coins[i].x = 3 + (i % 25) * 3;
        game->coins[i].y = (i < 25) ? HEIGHT - 3 : HEIGHT - 7;
        game->coins[i].collected = 0;
    }
    
    // ?�탈 비활?�화
    game->portal.active = 0;
    
    // ?�레?�어 ?�치
    game->player.x = 5;
    game->player.y = HEIGHT - 3;
}

void returnFromHiddenStage(GameState* game) {
    game->inHiddenStage = 0;
    game->hiddenStageTimer = 0;
    game->level = game->returnLevel;
    
    if (game->level == 1) {
        initPlatforms(game);
        initEnemies(game);
        initCoins(game);
    } else {
        initStage2(game);
    }
    
    game->player.x = 5;
    game->player.y = HEIGHT - 3;
}

void nextStage(GameState* game) {
    game->stageCleared = 0;
    game->level++;
    game->player.x = 5;
    game->player.y = HEIGHT - 3;
    game->player.velocityX = 0;
    game->player.velocityY = 0;
    if (game->level == 2) {
        initStage2(game);
    } else {
        game->gameOver = 1;
    }
}

// ================================================
// 게임 전체 초기화
// ================================================
void initGame(GameState* game) {
    game->gameOver = 0;
    game->level = 1;
    game->timer = 0;
    game->particleCount = 0;
    game->stageCleared = 0;
    game->inHiddenStage = 0;
    game->hiddenStageTimer = 0;
    game->returnLevel = 1;

    for (int i = 0; i < MAX_PARTICLES; i++) {
        game->particles[i].life = 0;
    }

    initPlayer(&game->player);
    initPlatforms(game);
    initEnemies(game);
    initCoins(game);
}