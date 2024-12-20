#ifndef __MOVE__
#define __MOVE__

void moveAndMerge(int** writePos, const int* startPos, int* current, int direction, int* tiles_moved, int* score, int* mergeOccurred);
int* getStartPos(int* board, int size, int i, int direction);
int pushAllLines(int* board, int size, int* score, int direction);
int handleMove(char choice, int* board, int size, int *score);

#endif
