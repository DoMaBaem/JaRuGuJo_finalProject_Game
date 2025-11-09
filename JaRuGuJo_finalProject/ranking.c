#define _CRT_SECURE_NO_WARNINGS
#include "ranking.h"

void swap(RankingEntry* a, RankingEntry* b) {
    RankingEntry temp = *a;
    *a = *b;
    *b = temp;
}

// Min-Heap: 부모가 자식보다 작음 (루트 = 최솟값 = 10등)
void heapifyUp(MinHeap* heap, int idx) {
    if (idx == 0) return;
    int parent = (idx - 1) / 2;
    if (heap->data[idx].score < heap->data[parent].score) {
        swap(&heap->data[idx], &heap->data[parent]);
        heapifyUp(heap, parent);
    }
}

void heapifyDown(MinHeap* heap, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < heap->size && heap->data[left].score < heap->data[smallest].score)
        smallest = left;
    if (right < heap->size && heap->data[right].score < heap->data[smallest].score)
        smallest = right;

    if (smallest != idx) {
        swap(&heap->data[idx], &heap->data[smallest]);
        heapifyDown(heap, smallest);
    }
}

// TOP 10 유지: 크기 10 이하면 삽입, 아니면 10등보다 높을 때만 교체
void insertHeap(MinHeap* heap, char* name, int score) {
    if (heap->size < TOP_K) {
        // 아직 10개 안 찼으면 그냥 삽입
        strcpy(heap->data[heap->size].name, name);
        heap->data[heap->size].score = score;
        heapifyUp(heap, heap->size);
        heap->size++;
    } else if (score > heap->data[0].score) {
        // 10등(루트)보다 높으면 교체
        strcpy(heap->data[0].name, name);
        heap->data[0].score = score;
        heapifyDown(heap, 0);
    }
}

RankingEntry extractMin(MinHeap* heap) {
    RankingEntry min = heap->data[0];
    heap->data[0] = heap->data[heap->size - 1];
    heap->size--;
    heapifyDown(heap, 0);
    return min;
}

void loadRankings(MinHeap* heap) {
    heap->size = 0;
    FILE* file = fopen(RANKING_FILE, "r");
    if (file == NULL) return;

    char name[50];
    int score;
    while (fscanf(file, "%s %d", name, &score) == 2) {
        insertHeap(heap, name, score);  // TOP 10만 유지
    }
    fclose(file);
}

void saveRankings(MinHeap* heap) {
    FILE* file = fopen(RANKING_FILE, "w");
    if (file == NULL) return;

    for (int i = 0; i < heap->size; i++) {
        fprintf(file, "%s %d\n", heap->data[i].name, heap->data[i].score);
    }
    fclose(file);
}

void displayRankings(MinHeap* heap, char* currentPlayer, int currentScore) {
    // Min-Heap을 배열로 복사 후 내림차순 정렬
    RankingEntry top10[TOP_K];
    int count = heap->size;
    
    for (int i = 0; i < count; i++) {
        top10[i] = heap->data[i];
    }
    
    // 버블 정렬 (내림차순)
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (top10[j].score < top10[j + 1].score) {
                RankingEntry temp = top10[j];
                top10[j] = top10[j + 1];
                top10[j + 1] = temp;
            }
        }
    }

    system("cls");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    printf("\n\n");
    printf("   ==========================================\n");
    printf("            TOP 10 RANKINGS\n");
    printf("   ==========================================\n\n");

    for (int i = 0; i < 10; i++) {
        if (i < count) {
            if (strcmp(top10[i].name, currentPlayer) == 0 && top10[i].score == currentScore) {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
                printf("   >> %d. %-20s %d pts <<\n", i + 1, top10[i].name, top10[i].score);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
            }
            else {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
                printf("      %d. %-20s %d pts\n", i + 1, top10[i].name, top10[i].score);
            }
        }
        else {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
            printf("      %d. ---\n", i + 1);
        }
    }

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    printf("\n   ==========================================\n");
}