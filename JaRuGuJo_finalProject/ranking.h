#ifndef RANKING_H
#define RANKING_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#define TOP_K 10
#define RANKING_FILE "rankings.txt"

typedef struct {
    char name[50];
    int score;
} RankingEntry;

typedef struct {
    RankingEntry data[TOP_K];
    int size;
} MinHeap;

void swap(RankingEntry* a, RankingEntry* b);
void heapifyUp(MinHeap* heap, int idx);
void heapifyDown(MinHeap* heap, int idx);
void insertHeap(MinHeap* heap, char* name, int score);
RankingEntry extractMin(MinHeap* heap);
void loadRankings(MinHeap* heap);
void saveRankings(MinHeap* heap);
void displayRankings(MinHeap* heap, char* currentPlayer, int currentScore);

#endif