#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "ranking.h"

void swap(RankingEntry* a, RankingEntry* b) {
    RankingEntry temp = *a;
    *a = *b;
    *b = temp;
}

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

void insertHeap(MinHeap* heap, char* name, int score) {
    if (heap->size < TOP_K) {
        strcpy(heap->data[heap->size].name, name);
        heap->data[heap->size].score = score;
        heapifyUp(heap, heap->size);
        heap->size++;
    } else if (score > heap->data[0].score) {
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
        insertHeap(heap, name, score);
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
    MinHeap tempHeap;
    tempHeap.size = heap->size;
    for (int i = 0; i < heap->size; i++) {
        tempHeap.data[i] = heap->data[i];
    }
    
    RankingEntry top10[TOP_K];
    int count = tempHeap.size;
    
    for (int i = 0; i < count; i++) {
        top10[i] = extractMin(&tempHeap);
    }

    system("cls");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    printf("\n\n");
    printf("   ==========================================\n");
    printf("            TOP 10 RANKINGS\n");
    printf("   ==========================================\n\n");

    for (int i = 0; i < 10; i++) {
        int idx = count - 1 - i;
        if (idx >= 0) {
            if (strcmp(top10[idx].name, currentPlayer) == 0 && top10[idx].score == currentScore) {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
                printf("   >> %d. %-20s %d pts <<\n", i + 1, top10[idx].name, top10[idx].score);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
            }
            else {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
                printf("      %d. %-20s %d pts\n", i + 1, top10[idx].name, top10[idx].score);
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
