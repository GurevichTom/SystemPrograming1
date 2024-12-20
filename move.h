#ifndef __MOVE__
#define __MOVE__

void moveAndMerge(int** writePos, const int* startPos, int* current, int direction, int* tiles_moved, int* score, int* mergeOccurred);
int pushHorizontal(int* board, int size, int* score, int direction);
int pushLeft(int* board, int size, int *score);
int pushRight(int* board, int size, int *score);
int pushVertical(int* board, int size, int* score, int direction);
int pushUp(int* board, int size, int *score);
int pushDown(int *board, int size, int *score);
int handleMove(char choice, int* board, int size, int *score);

#endif
