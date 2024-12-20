#include <stdio.h>
#include "move.h"

// directions:
#define RIGHT 1
#define LEFT -1
#define UP    1
#define DOWN -1

void moveAndMerge(int** writePos, const int* startPos, int* current, const int direction, int* tiles_moved, int* score, int* mergeOccurred) {
    if (*current == 0)
        return; // Skip empty cells      

    int* prevPos = *writePos + direction;

    // Combine cells of the same value
    if (*writePos != startPos && *prevPos == *current && !*mergeOccurred) {
        *prevPos *= 2;
        *current = 0;
        *mergeOccurred = 1; // Prevent more than one merge in line
        *tiles_moved = 1;
        *score += *prevPos;
    } else {
        // Push value to the next writing position
        if (current != *writePos) {
            **writePos = *current;
            *current = 0;
            *tiles_moved = 1;
        }
        *writePos -= direction;
    }
}




int pushHorizontal(int* board, const int size, int* score, const int direction) {
    int tiles_moved = 0;

    for (int i = 0; i < size; i++) {
        int* startPos = board + i * size;
        startPos = (direction == RIGHT) ? startPos + size - 1 : startPos;
        int* writePos = startPos;

        int mergeOccurred = 0;

        for (int j = 0; j < size; j++) {
            int* current = startPos - j * direction;
            moveAndMerge(&writePos, startPos, current, direction, &tiles_moved, score, &mergeOccurred);
        }
    }

    return tiles_moved;
}

int pushLeft(int* board, const int size, int *score) {
    return pushHorizontal(board, size, score, LEFT);
}

int pushRight(int* board, const int size, int *score) {
    return pushHorizontal(board, size, score, RIGHT);
}

int pushVertical(int* board, const int size, int* score, const int direction) {
    int tiles_moved = 0;

    for (int i = 0; i < size; i++) {
        int* startPos = board + i;
        startPos = (direction == UP) ? startPos : startPos + size * (size - 1);
        int* writePos = startPos;

        int mergeOccurred = 0;

        for (int j = 0; j < size; j++) {
            int* current = startPos + j * size * direction;
            moveAndMerge(&writePos, startPos, current, -size * direction, &tiles_moved, score, &mergeOccurred);
        }
    }

    return tiles_moved;
}

int pushUp(int* board, const int size, int *score) {
    return pushVertical(board, size, score, UP);
}

int pushDown(int *board, const int size, int *score) {
    return pushVertical(board, size, score, DOWN);
}



int handleMove(const char choice, int* board, const int size, int *score) {
    int tiles_moved = 0;

    switch (choice) {
        case 'l':
            tiles_moved = pushLeft(board, size, score);
            break;

        case 'r':
            tiles_moved = pushRight(board, size, score);
            break;

        case 'u':
            tiles_moved = pushUp(board, size, score);
            break;

        case 'd':
            tiles_moved = pushDown(board, size, score);
            break;

        default:
            printf("Invalid move direction.\n");
        return 0;
    }

    if (!tiles_moved) {
        printf("Nothing to move in this direction, choose another option\n");
    }

    return tiles_moved;
}
