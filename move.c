#include <stdio.h>
#include "move.h"

// directions:
#define RIGHT 1      // Move one cell to the right
#define LEFT (-1)      // Move one cell to the left
#define DOWN (size)  // Move one row down (i.e., +size cells)
#define UP (-size)    // Move one row up (i.e., -size cells)

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
        *score = *prevPos > *score ? *prevPos : *score;
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

int* getStartPos(int* board, const int size, const int i, const int direction) {
    // Horizontal directions
    if (direction == LEFT) {
        return board + i * size;
    }

    if (direction == RIGHT) {
        return board + i * size + (size - 1);
    }

    // Vertical directions
    if (direction == UP) {
        return board + i;
    }

    return board + i + size * (size - 1);

}

int pushAllLines(int* board, const int size, int* score, const int direction) {
    int tiles_moved = 0;

    // Process all lines:
    // For horizontal (LEFT/RIGHT), a "line" is a row.
    // For vertical (UP/DOWN), a "line" is a column.
    for (int i = 0; i < size; i++) {
        int* startPos = getStartPos(board, size, i, direction);
        int mergeOccurred = 0;
        int* writePos = startPos;

        // Iterate through this line's cells
        for (int j = 0; j < size; j++) {
            int* current = startPos - j * direction;
            moveAndMerge(&writePos, startPos, current, direction, &tiles_moved, score, &mergeOccurred);
        }
    }

    return tiles_moved;
}

int handleMove(const char choice, int* board, const int size, int* score) {
    int tiles_moved = 0;

    switch (choice) {
        case 'l': tiles_moved = pushAllLines(board, size, score, LEFT); break;
        case 'r': tiles_moved = pushAllLines(board, size, score, RIGHT); break;
        case 'u': tiles_moved = pushAllLines(board, size, score, UP); break;
        case 'd': tiles_moved = pushAllLines(board, size, score, DOWN); break;
        default:
            printf("Invalid move direction.\n");
        return 0;
    }

    if (!tiles_moved) {
        printf("Nothing to move in this direction, choose another option\n");
    }

    return tiles_moved;
}

