#include <stdlib.h>
#include "board.h"


void setRandomEmtpyPos(int* board, const int size, const int val) {
    int row, col, *chosenPlace;
    do {
        row = rand() % size;
        col = rand() % size;
        chosenPlace = board + row * size + col;
    } while (*(chosenPlace) != 0);

    *(chosenPlace) = val;
}

void addRandomTile(int* board, int size) {
    const int initialNumberProbability = 70;
    const int rareNum = 4;
    const int commonNum = 2;

    const int randomValue = rand() % 100;
    int chosenNumber = (randomValue <= initialNumberProbability) ? commonNum : rareNum;

    setRandomEmtpyPos(board, size, chosenNumber);
}

void resetBoard(int* board, const int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            *(board++) = 0;
        }
    }
}

// int hasValidVerticalMoves()

int hasValidMoves(const int *board, const int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (*board == 0) // Empty cell
                return 1;
            if (j != size-1 && *board == *(board+1)) // Check right
                return 1;
            if (j != 0 && *board == *(board-1)) // Check left
                return 1;
            if (i != 0 && *board == *(board - size)) // Check up
                return 1;
            if (i != size-1 && *board == *(board + size)) // Check down
                return 1;

            board++;
        }
    }
    return 0;
}

