#define _CRT_SECURE_NO_WARNINGS
#include "game.h"
#include "music.h" //[����] music ������� �߰�

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

void initEnemies(GameState* game) {
    game->enemyCount = 14;

    game->enemies[0].x = 11;
    game->enemies[0].y = HEIGHT - 5;
    game->enemies[0].velocityX = 1;
    game->enemies[0].active = 1;
    game->enemies[0].type = 0;
    game->enemies[0].homingTimer = 0;
    game->enemies[0].homingDuration = 0;
    game->enemies[0].respawnTimer = 0;
    game->enemies[0].initialX = 11;
    game->enemies[0].initialY = HEIGHT - 5;
    game->enemies[0].initialVelocityX = 1;

    game->enemies[1].x = 33;
    game->enemies[1].y = HEIGHT - 7;
    game->enemies[1].velocityX = -1;
    game->enemies[1].active = 1;
    game->enemies[1].type = 0;
    game->enemies[1].homingTimer = 0;
    game->enemies[1].homingDuration = 0;
    game->enemies[1].respawnTimer = 0;
    game->enemies[1].initialX = 33;
    game->enemies[1].initialY = HEIGHT - 7;
    game->enemies[1].initialVelocityX = -1;

    game->enemies[2].x = 18;
    game->enemies[2].y = HEIGHT - 9;
    game->enemies[2].velocityX = 2;
    game->enemies[2].active = 1;
    game->enemies[2].type = 1;
    game->enemies[2].homingTimer = 0;
    game->enemies[2].homingDuration = 0;
    game->enemies[2].respawnTimer = 0;
    game->enemies[2].initialX = 18;
    game->enemies[2].initialY = HEIGHT - 9;
    game->enemies[2].initialVelocityX = 2;

    game->enemies[3].x = 38;
    game->enemies[3].y = HEIGHT - 9;
    game->enemies[3].velocityX = -1;
    game->enemies[3].active = 1;
    game->enemies[3].type = 1;
    game->enemies[3].homingTimer = 0;
    game->enemies[3].homingDuration = 0;
    game->enemies[3].respawnTimer = 0;
    game->enemies[3].initialX = 38;
    game->enemies[3].initialY = HEIGHT - 9;
    game->enemies[3].initialVelocityX = -1;

    game->enemies[4].x = 58;
    game->enemies[4].y = HEIGHT - 9;
    game->enemies[4].velocityX = 2;
    game->enemies[4].active = 1;
    game->enemies[4].type = 1;
    game->enemies[4].homingTimer = 0;
    game->enemies[4].homingDuration = 0;
    game->enemies[4].respawnTimer = 0;
    game->enemies[4].initialX = 58;
    game->enemies[4].initialY = HEIGHT - 9;
    game->enemies[4].initialVelocityX = 2;

    game->enemies[5].x = 8;
    game->enemies[5].y = HEIGHT - 11;
    game->enemies[5].velocityX = 1;
    game->enemies[5].active = 1;
    game->enemies[5].type = 0;
    game->enemies[5].homingTimer = 0;
    game->enemies[5].homingDuration = 0;
    game->enemies[5].respawnTimer = 0;
    game->enemies[5].initialX = 8;
    game->enemies[5].initialY = HEIGHT - 11;
    game->enemies[5].initialVelocityX = 1;

    game->enemies[6].x = 28;
    game->enemies[6].y = HEIGHT - 11;
    game->enemies[6].velocityX = -2;
    game->enemies[6].active = 1;
    game->enemies[6].type = 1;
    game->enemies[6].homingTimer = 0;
    game->enemies[6].homingDuration = 0;
    game->enemies[6].respawnTimer = 0;
    game->enemies[6].initialX = 28;
    game->enemies[6].initialY = HEIGHT - 11;
    game->enemies[6].initialVelocityX = -2;

    game->enemies[7].x = 48;
    game->enemies[7].y = HEIGHT - 11;
    game->enemies[7].velocityX = 1;
    game->enemies[7].active = 1;
    game->enemies[7].type = 1;
    game->enemies[7].homingTimer = 0;
    game->enemies[7].homingDuration = 0;
    game->enemies[7].respawnTimer = 0;
    game->enemies[7].initialX = 48;
    game->enemies[7].initialY = HEIGHT - 11;
    game->enemies[7].initialVelocityX = 1;

    game->enemies[8].x = 68;
    game->enemies[8].y = HEIGHT - 11;
    game->enemies[8].velocityX = -2;
    game->enemies[8].active = 1;
    game->enemies[8].type = 1;
    game->enemies[8].homingTimer = 0;
    game->enemies[8].homingDuration = 0;
    game->enemies[8].respawnTimer = 0;
    game->enemies[8].initialX = 68;
    game->enemies[8].initialY = HEIGHT - 11;
    game->enemies[8].initialVelocityX = -2;

    game->enemies[9].x = 38;
    game->enemies[9].y = HEIGHT - 13;
    game->enemies[9].velocityX = 2;
    game->enemies[9].active = 1;
    game->enemies[9].type = 1;
    game->enemies[9].homingTimer = 0;
    game->enemies[9].homingDuration = 0;
    game->enemies[9].respawnTimer = 0;
    game->enemies[9].initialX = 38;
    game->enemies[9].initialY = HEIGHT - 13;
    game->enemies[9].initialVelocityX = 2;

    game->enemies[10].x = 12;
    game->enemies[10].y = HEIGHT - 15;
    game->enemies[10].velocityX = 2;
    game->enemies[10].active = 1;
    game->enemies[10].type = 1;
    game->enemies[10].homingTimer = 0;
    game->enemies[10].homingDuration = 0;
    game->enemies[10].respawnTimer = 0;
    game->enemies[10].initialX = 12;
    game->enemies[10].initialY = HEIGHT - 15;
    game->enemies[10].initialVelocityX = 2;

    game->enemies[11].x = 27;
    game->enemies[11].y = HEIGHT - 17;
    game->enemies[11].velocityX = -2;
    game->enemies[11].active = 1;
    game->enemies[11].type = 1;
    game->enemies[11].homingTimer = 0;
    game->enemies[11].homingDuration = 0;
    game->enemies[11].respawnTimer = 0;
    game->enemies[11].initialX = 27;
    game->enemies[11].initialY = HEIGHT - 17;
    game->enemies[11].initialVelocityX = -2;

    game->enemies[12].x = 47;
    game->enemies[12].y = HEIGHT - 19;
    game->enemies[12].velocityX = 2;
    game->enemies[12].active = 1;
    game->enemies[12].type = 1;
    game->enemies[12].homingTimer = 0;
    game->enemies[12].homingDuration = 0;
    game->enemies[12].respawnTimer = 0;
    game->enemies[12].initialX = 47;
    game->enemies[12].initialY = HEIGHT - 19;
    game->enemies[12].initialVelocityX = 2;

    game->enemies[13].x = 67;
    game->enemies[13].y = HEIGHT - 21;
    game->enemies[13].velocityX = -2;
    game->enemies[13].active = 1;
    game->enemies[13].type = 1;
    game->enemies[13].homingTimer = 0;
    game->enemies[13].homingDuration = 0;
    game->enemies[13].respawnTimer = 0;
    game->enemies[13].initialX = 67;
    game->enemies[13].initialY = HEIGHT - 21;
    game->enemies[13].initialVelocityX = -2;
}

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

void updatePlayer(GameState* game) {
    Player* player = &game->player;

    player->velocityY += GRAVITY;
    if (player->velocityY > 10) player->velocityY = 10;

    player->y += player->velocityY;
    player->x += player->velocityX;

    if (player->x < 1) {
        player->x = 1;
        player->velocityX = 0;
    }
    if (player->x >= WIDTH - 1) {
        player->x = WIDTH - 2;
        player->velocityX = 0;
    }

    player->onGround = 0;

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

    if (player->invincibleTimer > 0) {
        player->invincibleTimer--;
        if (player->invincibleTimer == 0) {
            player->invincible = 0;
        }
    }

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
        if (game->enemies[i].active) {
            if (game->enemies[i].type == 1) {
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

            game->enemies[i].x += game->enemies[i].velocityX;

            if (game->enemies[i].x <= 2 || game->enemies[i].x >= WIDTH - 3) {
                game->enemies[i].velocityX *= -1;
            }

            int dx = abs(game->player.x - game->enemies[i].x);
            int dy = game->player.y - game->enemies[i].y;

            if (dx <= 1 && dy == -1 && game->player.velocityY > 0) {
                game->enemies[i].active = 0;
                game->enemies[i].respawnTimer = 300;
                game->player.velocityY = -4;
                if (game->enemies[i].type == 0) {
                    game->player.score += 100;
                }
                else {
                    game->player.score += 150;
                }
                for (int j = 0; j < 5; j++) {
                    addParticle(game, game->enemies[i].x, game->enemies[i].y, '*');
                }
            }
            else if (dx <= 1 && dy == 0 && !game->player.invincible) {
                int damage = (game->enemies[i].type == 0) ? 15 : 25;
                game->player.health -= damage;
                game->player.invincible = 1;
                game->player.invincibleTimer = 30;
                playSFX(SFX_HIT); //[����] �ǰ� ȿ���� ���
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
        else {
            if (game->enemies[i].respawnTimer > 0) {
                game->enemies[i].respawnTimer--;
                if (game->enemies[i].respawnTimer == 0) {
                    game->enemies[i].active = 1;
                    game->enemies[i].x = game->enemies[i].initialX;
                    game->enemies[i].y = game->enemies[i].initialY;
                    game->enemies[i].velocityX = game->enemies[i].initialVelocityX;
                    game->enemies[i].homingTimer = 0;
                    game->enemies[i].homingDuration = 0;
                }
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
                game->player.score += 50;
                addParticle(game, game->coins[i].x, game->coins[i].y, '+');
            }
        }
    }
}

void handleInput(GameState* game) {
    static int leftPressed = 0, rightPressed = 0;
    
    if (_kbhit()) {
        char key = _getch();

        if (key == 27) {
            game->gameOver = 1;
        }

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
                    game->player.velocityY = JUMP_POWER;
                    playSFX(SFX_JUMP); //[����] ���� ȿ���� �߻�
                    addParticle(game, game->player.x, game->player.y + 1, '.');
                }
            }
        }

        if (key == ' ') {
            if (game->player.onGround) {
                game->player.velocityY = JUMP_POWER;
                playSFX(SFX_JUMP);     // [����] ���� ȿ���� ���
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
                game->player.velocityY = JUMP_POWER;
                addParticle(game, game->player.x, game->player.y + 1, '.');
            }
        }

        if (key == 'r' || key == 'R') {
            initPlayer(&game->player);
            initPlatforms(game);
            initEnemies(game);
            initCoins(game);
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

void checkGameOver(GameState* game) {
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
            playSFX(SFX_DIE); //[����] ���� ȿ���� ���
            game->gameOver = 1;
        }
    }

    int allCoinsCollected = 1;
    for (int i = 0; i < game->coinCount; i++) {
        if (!game->coins[i].collected) {
            allCoinsCollected = 0;
            break;
        }
    }

    if (allCoinsCollected) {
        game->level++;
        game->player.score += 500;
        initPlatforms(game);
        initEnemies(game);
        initCoins(game);
        game->player.x = 5;
        game->player.y = HEIGHT - 3;
    }
}

void initGame(GameState* game) {
    game->gameOver = 0;
    game->level = 1;
    game->timer = 0;
    game->particleCount = 0;

    for (int i = 0; i < MAX_PARTICLES; i++) {
        game->particles[i].life = 0;
    }

    initPlayer(&game->player);
    initPlatforms(game);
    initEnemies(game);
    initCoins(game);
}