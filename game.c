#include <stdio.h>
#include "game.h"
#include "displayGame.h"
#include "board.h"
#include "move.h"

void initGame(int* board, const int boardSize, int *gameState, int scoreToWin, int *score) {
    resetBoard(board, boardSize);
    addRandomTile(board, boardSize);
    *gameState = 1;
    *score = 0;
    printStartMessage(scoreToWin);
}



int runFunction(const char choice, int* board, const int size, int *gameState, int *score, int bestScore, int scoreToWin) {
    if (!*gameState && choice != 'n' && choice != 'e') {
        printf("Need to start game first\n");
        return 0;
    }

    switch (choice) {
        case 'n':
            initGame(board, size, gameState, scoreToWin, score);
            return 1;
        case 'l': // Fallthrough
        case 'r':
        case 'u':
        case 'd':
            return handleMove(choice, board, size, score);
        case 'e':
            printf("Ending previous game - your score %d best score %d\n\n", *score, bestScore);
            printf("Bye bye\n");
            *gameState = -1;
            break;
        default:
            printf("No such option\n");
    }

    return 0;
}

char displayMainMenu() {
    // Each key in `menuKeys` corresponds to the option at the same index in `menuOptions`.
    char *menuOptions[] = {"N/n New Game", "R/r Move Right", "L/l Move Left",
        "U/u Move Up", "D/d Move down", "E/e Exit"};
    const int menuCount = sizeof(menuOptions) / sizeof(menuOptions[0]);

    printf("\n\nPlease choose one of the following options:\n");
    for (int i = 0; i < menuCount; i++) {
        printf("%s\n", *(menuOptions+i));
    }

    char userChoice;
    scanf(" %c", &userChoice);

    return userChoice;
}

void playGame(int* board, int size, int scoreToWin) {
    int best = 0;
    int score = 0;
    int gameState = 0;
    int tiles_moved = 1;
    int has_valid_moves = 1;

     while (score < scoreToWin && has_valid_moves && gameState != -1) {
        if (tiles_moved)
            displayBoard(board, size, best, score);
        const char choice = displayMainMenu();
        tiles_moved = runFunction(choice, board, size, &gameState, &score, best, scoreToWin);
        best = score > best ? score : best;

        if (tiles_moved)
            addRandomTile(board, size);

        has_valid_moves = hasValidMoves(board, size);
    }

    if (gameState != -1)
        displayBoard(board, size, best, score);

    if (!has_valid_moves)
        printf("Game over your score is %d\n", score);
    else if (score >= scoreToWin)
        printf("You won %d!  - Ending Game\n", score);

    // cleanup
    resetBoard(board, size);
}
