# Platform Jump Game - 기능 설명 및 알고리즘 분석

## 1. 게임 종류
**2D 플랫폼 점프 게임 (Platform Jumper)**
- 장르: 아케이드 액션 플랫포머
- 마리오 스타일의 횡스크롤 점프 게임

---

## 2. 게임 주요 구성 요소

### 2.1 플레이어 (Player)
- 위치: x, y 좌표
- 체력: 100 (몬스터 충돌 시 감소)
- 생명: 3개
- 점수: 코인 획득 및 적 처치로 증가
- 조작: A/D (좌우 이동), W/Space (점프)

### 2.2 몬스터 (Enemy)
- **Type 0 (Red 'M')**: 일반 몬스터, 데미지 15, 점수 100
- **Type 1 (Blue 'W')**: 추적 몬스터, 데미지 25, 점수 150
  - 주기적으로 플레이어 추적 (Homing)
- 플랫폼 위를 좌우로 이동
- 위에서 밟으면 처치 가능

### 2.3 코인 (Coin)
- 총 38개 배치
- 획득 시 점수 +50
- 모든 코인 수집 시 다음 레벨로 진행 (+500 보너스)

### 2.4 플랫폼 (Platform)
- 총 24개의 블록
- 다양한 높이와 위치에 배치
- 플레이어가 점프하여 이동

---

## 3. 랭킹 시스템 - 파일 기반 + Max Heap

### 3.1 시스템 구조
```
rankings.txt (파일) → loadRankings() → Max Heap → displayRankings() → TOP 10
```

### 3.2 파일 기반 저장
- **파일명**: `rankings.txt`
- **형식**: `이름 점수` (공백으로 구분)
- **영속성**: 게임 종료 후에도 데이터 유지

### 3.3 Max Heap 자료구조 사용
```c
typedef struct {
    RankingEntry data[MAX_RANKINGS];  // 최대 100개
    int size;
} MaxHeap;
```

---

## 4. Max Heap 알고리즘 분석

### 4.1 왜 Max Heap을 사용하는가?

#### 문제 상황
- 파일에서 N개의 랭킹 데이터 읽기
- **상위 10개만 필요**
- 새로운 점수 추가 시 정렬 필요

#### 다른 방법과의 비교

| 방법 | 삽입 | 최댓값 추출 | TOP 10 추출 | 공간 복잡도 |
|------|------|-------------|-------------|-------------|
| **배열 정렬** | O(1) | O(N log N) | O(N log N) | O(N) |
| **Max Heap** | O(log N) | O(log N) | O(10 log N) | O(N) |

### 4.2 시간 복잡도 분석 (Big-O)

#### 파일에서 N개 데이터 로딩
```
배열 정렬: O(N) + O(N log N) = O(N log N)
Max Heap:  O(N log N)  [N번 삽입, 각 O(log N)]
```

#### TOP 10 추출
```
배열 정렬: O(N log N) [전체 정렬] + O(10) = O(N log N)
Max Heap:  O(10 log N) [10번 extractMax]
```

#### 새 점수 추가 후 TOP 10 조회
```
배열 정렬: O(1) [삽입] + O(N log N) [정렬] = O(N log N)
Max Heap:  O(log N) [삽입] + O(10 log N) [추출] = O(log N)
```

### 4.3 Max Heap의 핵심 장점

#### ✅ 부분 정렬에 최적화
- 전체 데이터를 정렬할 필요 없음
- **상위 K개만 필요할 때 효율적**
- 이 게임에서는 K=10 (TOP 10)

#### ✅ 동적 데이터 처리
- 새로운 점수 추가: O(log N)
- 최고 점수 조회: O(1) [루트 노드]
- 최고 점수 제거: O(log N)

#### ✅ 실시간 랭킹 업데이트
```c
// 게임 종료 시
insertHeap(&rankings, playerName, score);  // O(log N)
saveRankings(&rankings);                   // O(N)
displayRankings(&rankings, ...);           // O(10 log N)
```

### 4.4 구현된 핵심 함수

#### insertHeap - O(log N)
```c
void insertHeap(MaxHeap* heap, char* name, int score) {
    heap->data[heap->size] = {name, score};
    heapifyUp(heap, heap->size);  // 상향 조정
    heap->size++;
}
```

#### extractMax - O(log N)
```c
RankingEntry extractMax(MaxHeap* heap) {
    RankingEntry max = heap->data[0];  // 루트 = 최댓값
    heap->data[0] = heap->data[heap->size - 1];
    heap->size--;
    heapifyDown(heap, 0);  // 하향 조정
    return max;
}
```

#### displayRankings - O(10 log N)
```c
void displayRankings(MaxHeap* heap, ...) {
    MaxHeap tempHeap = *heap;  // 복사본 생성
    for (int i = 0; i < 10; i++) {
        top10[i] = extractMax(&tempHeap);  // 10번 추출
    }
    // 출력...
}
```

---

## 5. 실제 성능 비교 예시

### 시나리오: 100명의 플레이어 데이터, TOP 10 조회

| 작업 | 배열 정렬 | Max Heap | 성능 차이 |
|------|-----------|----------|-----------|
| 데이터 로딩 | O(100 log 100) ≈ 664 | O(100 log 100) ≈ 664 | 동일 |
| TOP 10 추출 | O(100 log 100) ≈ 664 | O(10 log 100) ≈ 66 | **10배 빠름** |
| 새 점수 추가 | O(100 log 100) ≈ 664 | O(log 100) ≈ 6.6 | **100배 빠름** |

### 결론
- **일부 데이터만 필요한 경우 Max Heap이 압도적으로 효율적**
- 랭킹 시스템처럼 "상위 K개"만 필요한 경우 최적의 선택
- 메모리 사용량은 동일하지만 시간 복잡도에서 큰 이득

---

## 6. 게임 플로우

```
1. 플레이어 이름 입력
2. rankings.txt 파일에서 기존 랭킹 로드 → Max Heap 구성
3. 게임 시작
   - 플랫폼 점프
   - 코인 수집 (+50점)
   - 몬스터 처치 (+100/+150점)
   - 몬스터 충돌 시 체력 감소
4. 게임 오버 (체력 0 또는 생명 소진)
5. 새 점수를 Max Heap에 삽입
6. rankings.txt에 저장
7. TOP 10 랭킹 화면 표시
```

---

## 7. 기술 스택
- **언어**: C
- **자료구조**: Max Heap (우선순위 큐)
- **파일 I/O**: 텍스트 파일 기반 영속성
- **그래픽**: Windows Console API (더블 버퍼링)
- **물리**: 중력, 점프, 충돌 감지
