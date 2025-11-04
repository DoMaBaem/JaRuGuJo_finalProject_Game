#define _CRT_SECURE_NO_WARNINGS
#include "ranking.h"

void swap(RankingEntry* a, RankingEntry* b) {
    RankingEntry temp = *a;
    *a = *b;
    *b = temp;
}

void heapifyUp(MaxHeap* heap, int idx) {
    if (idx == 0) return;
    int parent = (idx - 1) / 2;
    if (heap->data[idx].score > heap->data[parent].score) {
        swap(&heap->data[idx], &heap->data[parent]);
        heapifyUp(heap, parent);
    }
}

void heapifyDown(MaxHeap* heap, int idx) {
    int largest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < heap->size && heap->data[left].score > heap->data[largest].score)
        largest = left;
    if (right < heap->size && heap->data[right].score > heap->data[largest].score)
        largest = right;

    if (largest != idx) {
        swap(&heap->data[idx], &heap->data[largest]);
        heapifyDown(heap, largest);
    }
}

void insertHeap(MaxHeap* heap, char* name, int score) {
    if (heap->size >= MAX_RANKINGS) return;
    strcpy(heap->data[heap->size].name, name);
    heap->data[heap->size].score = score;
    heapifyUp(heap, heap->size);
    heap->size++;
}

RankingEntry extractMax(MaxHeap* heap) {
    RankingEntry max = heap->data[0];
    heap->data[0] = heap->data[heap->size - 1];
    heap->size--;
    heapifyDown(heap, 0);
    return max;
}

void loadRankings(MaxHeap* heap) {
    heap->size = 0;
    FILE* file = fopen(RANKING_FILE, "r");
    if (file == NULL) return;

    char name[50];
    int score;
    while (fscanf(file, "%s %d", name, &score) == 2) {
        insertHeap(heap, name, score);
    }
    fclose(file);
}

void saveRankings(MaxHeap* heap) {
    FILE* file = fopen(RANKING_FILE, "w");
    if (file == NULL) return;

    for (int i = 0; i < heap->size; i++) {
        fprintf(file, "%s %d\n", heap->data[i].name, heap->data[i].score);
    }
    fclose(file);
}

void displayRankings(MaxHeap* heap, char* currentPlayer, int currentScore) {
    MaxHeap tempHeap = *heap;
    RankingEntry top10[10];
    int count = 0;

    while (tempHeap.size > 0 && count < 10) {
        top10[count++] = extractMax(&tempHeap);
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