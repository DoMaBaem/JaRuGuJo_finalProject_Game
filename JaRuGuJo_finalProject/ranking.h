#ifndef RANKING_H
#define RANKING_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#define MAX_RANKINGS 100
#define RANKING_FILE "rankings.txt"

typedef struct {
    char name[50];
    int score;
} RankingEntry;

typedef struct {
    RankingEntry data[MAX_RANKINGS];
    int size;
} MaxHeap;

void swap(RankingEntry* a, RankingEntry* b);
void heapifyUp(MaxHeap* heap, int idx);
void heapifyDown(MaxHeap* heap, int idx);
void insertHeap(MaxHeap* heap, char* name, int score);
RankingEntry extractMax(MaxHeap* heap);
void loadRankings(MaxHeap* heap);
void saveRankings(MaxHeap* heap);
void displayRankings(MaxHeap* heap, char* currentPlayer, int currentScore);

#endif