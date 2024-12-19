#include <stdio.h>
#include "move.h"

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

/*
int pushVertical(int* board, const int size, int *score, const int direction) {
    int tiles_moved = 0;

    for (int i = 0; i < size; i++) {
        int *startPos = board + i;
        startPos = (direction == 1)
                        ? startPos
                        : startPos + size * (size - 1);
        int *writePos = startPos;

        int mergeOccurred = 0;

        for (int j = 0; j < size; j++) {
            int *current = startPos + j * size * direction;

            if (*current == 0)
                continue;

            int *prevPos = writePos - size * direction;
            if (!mergeOccurred && writePos != startPos && *prevPos == *current) {
                mergeOccurred = 1;
                *prevPos *= 2;
                *current = 0;
                tiles_moved = 1;
                *score += *prevPos;
            } else {
                if (writePos != current) {
                    *writePos = *current;
                    *current = 0;
                    tiles_moved = 1;
                }
                writePos += size * direction;
            }
        }
    }

    return tiles_moved;
}

int pushHorizontal(int* board, const int size, int *score, const int direction) {
    int tiles_moved = 0;

    for (int i = 0; i < size; i++) {
        // Determine the start of the row and initial traversal position
        int *startPos = board + i * size;
        startPos = (direction == 1)
                        ? startPos + size - 1 // Rightmost position for right
                        : startPos;          // Leftmost position for left
        int *writePos = startPos;

        int mergeOccurred = 0;

        for (int j = 0; j < size; j++) {
            // Current pointer based on direction
            int *current = startPos - j * direction;

            if (*current == 0)
                continue; // Skip empty cells

            // Combine cells of the same value
            int *prevPos = writePos + direction;
            if (writePos != startPos && *prevPos == *current && !mergeOccurred) {
                *prevPos *= 2;
                mergeOccurred = 1; // Prevent more than one merge in line
                *current = 0;
                tiles_moved = 1;
                *score += *prevPos; // Update score
            } else {
                // Push value to the next writing position
                if (current != writePos) {
                    *writePos = *current;
                    *current = 0;
                    tiles_moved = 1;
                }
                writePos -= direction; // Move write position (left or right) based on direction
            }
        }
    }

    return tiles_moved;
}*/


int pushHorizontal(int* board, const int size, int* score, const int direction) {
    int tiles_moved = 0;

    for (int i = 0; i < size; i++) {
        int* startPos = board + i * size;
        startPos = (direction == 1) ? startPos + size - 1 : startPos;
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
    return pushHorizontal(board, size, score, -1);
}

int pushRight(int* board, const int size, int *score) {
    return pushHorizontal(board, size, score, 1);
}

int pushVertical(int* board, const int size, int* score, const int direction) {
    int tiles_moved = 0;

    for (int i = 0; i < size; i++) {
        int* startPos = board + i;
        startPos = (direction == 1) ? startPos : startPos + size * (size - 1);
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
    return pushVertical(board, size, score, 1);
}

int pushDown(int *board, const int size, int *score) {
    return pushVertical(board, size, score, -1);
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
