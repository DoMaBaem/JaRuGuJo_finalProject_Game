# 코드 세부 설명 문서

## 목차
1. [game.c - 게임 로직](#gamec---게임-로직)
2. [graphics.c - 렌더링](#graphicsc---렌더링)
3. [ranking.c - 랭킹 시스템](#rankingc---랭킹-시스템)
4. [music.c - 사운드](#musicc---사운드)

---

## game.c - 게임 로직

### initPlayer() - 플레이어 초기화
```c
void initPlayer(Player* player) {
    player->x = 5;                    // 시작 x 좌표
    player->y = HEIGHT - 3;           // 시작 y 좌표 (바닥에서 3칸 위)
    player->velocityY = 0;            // 수직 속도 초기화
    player->velocityX = 0;            // 수평 속도 초기화
    player->onGround = 0;             // 공중에 있는 상태
    player->health = 100;             // 체력 100
    player->score = 0;                // 점수 0
    player->coins = 0;                // 코인 개수 0
    player->lives = 3;                // 생명 3개
    player->invincible = 0;           // 무적 상태 아님
    player->invincibleTimer = 0;      // 무적 타이머 0
    player->direction = 'R';          // 오른쪽 방향
}
```

### updatePlayer() - 플레이어 업데이트 (핵심 물리 엔진)
```c
void updatePlayer(GameState* game) {
    Player* player = &game->player;
    
    // 중력 적용
    player->velocityY += GRAVITY;           // velocityY에 중력(1) 추가
    if (player->velocityY > 10)             // 최대 낙하 속도 제한
        player->velocityY = 10;
    
    // 위치 업데이트
    player->y += player->velocityY;         // y 좌표에 수직 속도 적용
    player->x += player->velocityX;         // x 좌표에 수평 속도 적용
    
    // 벽 충돌 처리
    if (player->x < 1) {                    // 왼쪽 벽
        player->x = 1;
        player->velocityX = 0;
    }
    if (player->x >= WIDTH - 1) {           // 오른쪽 벽
        player->x = WIDTH - 2;
        player->velocityX = 0;
    }
    
    player->onGround = 0;                   // 기본적으로 공중 상태
    
    // 플랫폼 충돌 검사
    for (int i = 0; i < game->platformCount; i++) {
        if (game->platforms[i].active) {
            // 플레이어가 플랫폼 x 범위 안에 있는지 확인
            int onPlatformX = (player->x >= game->platforms[i].x && 
                              player->x < game->platforms[i].x + game->platforms[i].width);
            
            if (onPlatformX) {
                // 플레이어가 플랫폼 위에 정확히 있고 하강 중일 때
                if (player->y == game->platforms[i].y && player->velocityY >= 0) {
                    player->velocityY = 0;      // 낙하 멈춤
                    player->onGround = 1;       // 땅에 있음
                }
                // 플레이어가 플랫폼을 약간 통과했을 때 (보정)
                else if (player->y > game->platforms[i].y && 
                        player->y <= game->platforms[i].y + 1 && 
                        player->velocityY > 0) {
                    player->y = game->platforms[i].y;  // 플랫폼 위로 보정
                    player->velocityY = 0;
                    player->onGround = 1;
                }
            }
        }
    }
    
    // 화면 아래로 떨어졌을 때
    if (player->y >= HEIGHT - 1) {
        player->lives--;                    // 생명 감소
        if (player->lives > 0) {
            // 리스폰
            player->health = 100;
            player->x = 5;
            player->y = HEIGHT - 3;
            player->velocityY = 0;
            player->velocityX = 0;
        } else {
            player->health = 0;             // 게임 오버
        }
    }
    
    // 무적 타이머 감소
    if (player->invincibleTimer > 0) {
        player->invincibleTimer--;
        if (player->invincibleTimer == 0) {
            player->invincible = 0;
        }
    }
    
    // 마찰력 적용 (속도 감소)
    if (!player->invincible || player->invincibleTimer < 20) {
        if (player->onGround && player->velocityX != 0) {
            player->velocityX = (int)(player->velocityX * 0.8);  // 땅에서 80% 감속
        } else if (!player->onGround) {
            player->velocityX = (int)(player->velocityX * 0.95); // 공중에서 95% 감속
        }
    } else {
        player->velocityX = (int)(player->velocityX * 0.8);
    }
}
```

### updateCoins() - 코인 수집 및 포탈 처리
```c
void updateCoins(GameState* game) {
    // 모든 코인 검사
    for (int i = 0; i < game->coinCount; i++) {
        if (!game->coins[i].collected) {
            // 플레이어와 코인의 거리 계산
            // x 거리 1 이하, y 거리 1 이하, 코인이 플레이어보다 위에 있을 때
            if (abs(game->player.x - game->coins[i].x) <= 1 &&
                abs(game->player.y - game->coins[i].y) <= 1 &&
                game->coins[i].y <= game->player.y) {
                
                game->coins[i].collected = 1;           // 코인 수집
                game->player.coins++;                   // 코인 개수 증가
                game->player.score += 50;               // 점수 50점 추가
                addParticle(game, game->coins[i].x, game->coins[i].y, '+');  // 파티클 생성
            }
        }
    }
    
    // 포탈 충돌 검사
    if (game->portal.active && !game->inHiddenStage) {
        if (abs(game->player.x - game->portal.x) <= 1 &&
            abs(game->player.y - game->portal.y) <= 1) {
            initHiddenStage(game);                      // 히든 스테이지 진입
        }
    }
    
    // 히든 스테이지 타이머
    if (game->inHiddenStage) {
        game->hiddenStageTimer--;                       // 타이머 감소
        if (game->hiddenStageTimer <= 0) {
            returnFromHiddenStage(game);                // 원래 스테이지로 복귀
        }
    }
}
```

### updateEnemies() - 몬스터 AI 및 충돌 처리
```c
void updateEnemies(GameState* game) {
    for (int i = 0; i < game->enemyCount; i++) {
        // 리스폰 타이머 처리
        if (!game->enemies[i].active && game->enemies[i].respawnTimer > 0) {
            game->enemies[i].respawnTimer--;
            if (game->enemies[i].respawnTimer == 0) {
                game->enemies[i].active = 1;            // 몬스터 재생성
                game->enemies[i].x = game->enemies[i].spawnX;
                game->enemies[i].y = game->enemies[i].spawnY;
            }
        }
        
        if (game->enemies[i].active) {
            // Type 2: 비행 몬스터 (대각선 이동)
            if (game->enemies[i].type == 2) {
                game->enemies[i].x += game->enemies[i].velocityX;
                game->enemies[i].y += game->enemies[i].velocityY;
                
                // 벽에 부딪히면 반사
                if (game->enemies[i].x <= 2 || game->enemies[i].x >= WIDTH - 3) {
                    game->enemies[i].velocityX *= -1;
                }
                if (game->enemies[i].y <= 1 || game->enemies[i].y >= HEIGHT - 1) {
                    game->enemies[i].velocityY *= -1;
                }
            }
            // Type 1: 추적 몬스터 (Homing)
            else if (game->enemies[i].type == 1) {
                int speed = abs(game->enemies[i].velocityX);
                
                if (game->enemies[i].homingDuration > 0) {
                    // 추적 모드 활성화 중
                    game->enemies[i].homingDuration--;
                    
                    // 플레이어 방향으로 이동
                    if (game->player.x > game->enemies[i].x) {
                        game->enemies[i].velocityX = speed;
                    } else if (game->player.x < game->enemies[i].x) {
                        game->enemies[i].velocityX = -speed;
                    }
                } else {
                    // 추적 타이머 증가
                    game->enemies[i].homingTimer++;
                    if (game->enemies[i].homingTimer >= 120) {
                        // 120프레임마다 80프레임 동안 추적
                        game->enemies[i].homingDuration = 80;
                        game->enemies[i].homingTimer = 0;
                    }
                }
            }
            
            // Type 0, 1: 좌우 이동
            if (game->enemies[i].type != 2) {
                game->enemies[i].x += game->enemies[i].velocityX;
                if (game->enemies[i].x <= 2 || game->enemies[i].x >= WIDTH - 3) {
                    game->enemies[i].velocityX *= -1;  // 방향 전환
                }
            }
            
            // 플레이어와의 충돌 검사
            int dx = abs(game->player.x - game->enemies[i].x);
            int dy = game->player.y - game->enemies[i].y;
            
            // 플레이어가 위에서 밟았을 때 (dy == -1: 플레이어가 1칸 위)
            if (dx <= 1 && dy == -1 && game->player.velocityY > 0) {
                game->enemies[i].active = 0;            // 몬스터 제거
                game->enemies[i].respawnTimer = 100;    // 100프레임 후 리스폰
                game->player.velocityY = -4;            // 플레이어 튕김
                
                // 점수 추가
                if (game->enemies[i].type == 0) {
                    game->player.score += 100;
                } else if (game->enemies[i].type == 1) {
                    game->player.score += 150;
                } else {
                    game->player.score += 200;
                }
                
                // 파티클 생성
                for (int j = 0; j < 5; j++) {
                    addParticle(game, game->enemies[i].x, game->enemies[i].y, '*');
                }
            }
            // 플레이어가 옆에서 충돌했을 때
            else if (dx <= 1 && dy == 0 && !game->player.invincible) {
                // 데미지 계산
                int damage = (game->enemies[i].type == 0) ? 15 : 
                            (game->enemies[i].type == 1) ? 25 : 30;
                
                game->player.health -= damage;          // 체력 감소
                game->player.invincible = 1;            // 무적 상태
                game->player.invincibleTimer = 30;      // 30프레임 무적
                playSFX(SFX_HIT);                       // 피격 사운드
                
                // 넉백 효과
                if (game->player.x < game->enemies[i].x) {
                    game->player.velocityX = -2;        // 왼쪽으로 밀림
                } else {
                    game->player.velocityX = 2;         // 오른쪽으로 밀림
                }
                game->player.velocityY = -2;            // 위로 튕김
                
                // 파티클 생성
                for (int j = 0; j < 3; j++) {
                    addParticle(game, game->player.x, game->player.y, '!');
                }
            }
        }
    }
}
```

### checkGameOver() - 게임 종료 및 스테이지 클리어 체크
```c
void checkGameOver(GameState* game) {
    // 체력이 0 이하일 때
    if (game->player.health <= 0) {
        game->player.lives--;                   // 생명 감소
        
        if (game->player.lives > 0) {
            // 생명이 남아있으면 리스폰
            game->player.health = 100;
            game->player.x = 5;
            game->player.y = HEIGHT - 3;
            game->player.velocityY = 0;
            game->player.velocityX = 0;
            game->player.invincible = 1;
            game->player.invincibleTimer = 60;  // 60프레임 무적
        } else {
            playSFX(SFX_DIE);                   // 죽음 사운드
            game->gameOver = 1;                 // 게임 오버
        }
    }
    
    // 모든 코인 수집 여부 확인
    int allCoinsCollected = 1;
    for (int i = 0; i < game->coinCount; i++) {
        if (!game->coins[i].collected) {
            allCoinsCollected = 0;
            break;
        }
    }
    
    // 모든 코인을 수집했고 아직 클리어 처리 안 했을 때
    if (allCoinsCollected && !game->stageCleared) {
        game->player.score += 500;              // 보너스 점수
        game->stageCleared = 1;                 // 스테이지 클리어 플래그
        
        if (game->level < 2) {
            Sleep(1500);                        // 1.5초 대기 (STAGE CLEAR 표시)
            nextStage(game);                    // 다음 스테이지로
        } else {
            game->gameOver = 1;                 // 마지막 스테이지면 게임 종료
        }
    }
}
```

---

## graphics.c - 렌더링

### drawToBuffer() - 버퍼에 문자 그리기
```c
void drawToBuffer(int x, int y, char c, int color) {
    // 화면 범위 내에 있을 때만 그리기
    if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT + 4) {
        screenBuffer[y][x] = c;         // 문자 저장
        colorBuffer[y][x] = color;      // 색상 저장
    }
}
```

### renderBuffer() - 더블 버퍼링 렌더링
```c
void renderBuffer() {
    for (int y = 0; y < HEIGHT + 4; y++) {
        for (int x = 0; x < WIDTH; x++) {
            // 이전 프레임과 비교하여 변경된 부분만 렌더링
            if (screenBuffer[y][x] != prevBuffer[y][x] || 
                colorBuffer[y][x] != prevColorBuffer[y][x]) {
                
                setColor(colorBuffer[y][x]);    // 색상 설정
                gotoxy(x, y);                   // 커서 이동
                printf("%c", screenBuffer[y][x]); // 문자 출력
                
                // 이전 버퍼 업데이트
                prevBuffer[y][x] = screenBuffer[y][x];
                prevColorBuffer[y][x] = colorBuffer[y][x];
            }
        }
    }
}
```

---

## ranking.c - 랭킹 시스템

### insertHeap() - Min Heap에 점수 삽입
```c
void insertHeap(MinHeap* heap, char* name, int score) {
    if (heap->size < TOP_K) {
        // 아직 10개 미만이면 그냥 삽입
        strcpy(heap->data[heap->size].name, name);
        heap->data[heap->size].score = score;
        heapifyUp(heap, heap->size);    // 상향 조정
        heap->size++;
    } else if (score > heap->data[0].score) {
        // 10등(루트)보다 높으면 교체
        strcpy(heap->data[0].name, name);
        heap->data[0].score = score;
        heapifyDown(heap, 0);           // 하향 조정
    }
    // 10등보다 낮으면 무시 (TOP 10 유지)
}
```

### heapifyUp() - 상향 조정 (삽입 시)
```c
void heapifyUp(MinHeap* heap, int idx) {
    if (idx == 0) return;               // 루트면 종료
    
    int parent = (idx - 1) / 2;         // 부모 인덱스
    
    // 자식이 부모보다 작으면 교환 (Min Heap)
    if (heap->data[idx].score < heap->data[parent].score) {
        swap(&heap->data[idx], &heap->data[parent]);
        heapifyUp(heap, parent);        // 재귀적으로 상향 조정
    }
}
```

### heapifyDown() - 하향 조정 (삭제/교체 시)
```c
void heapifyDown(MinHeap* heap, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;             // 왼쪽 자식
    int right = 2 * idx + 2;            // 오른쪽 자식
    
    // 왼쪽 자식이 더 작으면
    if (left < heap->size && heap->data[left].score < heap->data[smallest].score)
        smallest = left;
    
    // 오른쪽 자식이 더 작으면
    if (right < heap->size && heap->data[right].score < heap->data[smallest].score)
        smallest = right;
    
    // 자식 중 하나가 더 작으면 교환
    if (smallest != idx) {
        swap(&heap->data[idx], &heap->data[smallest]);
        heapifyDown(heap, smallest);    // 재귀적으로 하향 조정
    }
}
```

---

## music.c - 사운드

### playBGM() - 배경 음악 재생
```c
void playBGM() {
    // 기존 BGM 닫기
    mciSendString("close " BGM_ALIAS, NULL, 0, NULL);
    
    // BGM 파일 열기
    if (mciSendString("open \"bgm.mp3\" type mpegvideo alias " BGM_ALIAS, NULL, 0, NULL) != 0) {
        printf("Error: Cannot open BGM file.\n");
        return;
    }
    
    // 무한 반복 재생
    mciSendString("play " BGM_ALIAS " repeat", NULL, 0, NULL);
}
```

### playSFX() - 효과음 재생
```c
void playSFX(SoundEffectType type) {
    const char* soundPath;
    
    // 효과음 파일 선택
    switch (type) {
    case SFX_JUMP:
        soundPath = "jump.wav";
        break;
    case SFX_HIT:
        soundPath = "hit.wav";
        break;
    case SFX_DIE:
        soundPath = "die.wav";
        break;
    default:
        return;
    }
    
    // 비동기 재생 (게임 진행 방해 안 함)
    PlaySound(soundPath, NULL, SND_FILENAME | SND_ASYNC | SND_NODEFAULT);
}
```
