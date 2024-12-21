#include <stdio.h>
#include "displayGame.h"

void displayRowDelimiter(const int size) {
    const int delimiter_lines_per_element = 7;
    const char row_delimiter = '-';

    for (int i = 0; i < delimiter_lines_per_element * size + 1; i++) {
        printf("%c", row_delimiter);
    }
    printf("\n");
}

void printStartMessage(const int winScore) {
    // Print the top horizontal line
    printf("------------------- STARTING A GAME -------------------\n");

    // Print the score for a win with the dynamic value
    printf("                  Score for a win %d\n", winScore);

    // Print the bottom horizontal line
    printf("-------------------------------------------------------\n\n");
}


void displayScore(const int best, const int score) {
    printf("Score %d Best %d\n", score, best);
}

void displayRow(const int* row, const int size) {
    const char colDelimiter = '|';
    const int leftPadding = 5;
    const int rightPadding = 1;

    for (int i = 0; i < size; i++) {
        const int value = *(row++);

        if (value == 0) {
            printf("%c%*s%*s",
                   colDelimiter, leftPadding, "", rightPadding, "");
        } else {
            printf("%c%*d%*s",
                   colDelimiter, leftPadding, value, rightPadding, "");
        }
    }
    printf("%c\n", colDelimiter);
}

void displayBoard(const int* board, const int size, const int best, const int score) {
    for (int i = 0; i < size * size; i += size) {
        displayRowDelimiter(size);
        displayRow(board+i, size);
    }
    displayRowDelimiter(size);
}
