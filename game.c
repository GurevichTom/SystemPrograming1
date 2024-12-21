#include <stdio.h>
#include <ctype.h>
#include "game.h"
#include "displayGame.h"
#include "board.h"
#include "move.h"

// Game states:
#define NOT_INITIALIZED 0
#define RUNNING         1
#define STOPPED        -1

void initGame(int* board, const int boardSize, int *gameState, int scoreToWin, int *score) {
    *score = 0;
    resetBoard(board, boardSize);
    addRandomTile(board, boardSize, score);
    *gameState = RUNNING;
    printStartMessage(scoreToWin);
}



int runFunction(const char choice, int* board, const int size, int *gameState, int *score, int bestScore, int scoreToWin) {
    switch (choice) {
        case 'n':
            initGame(board, size, gameState, scoreToWin, score);
            return 1;
        case 'e':
            printf("Ending previous game - your score %d best score %d\n\n", *score, bestScore);
            printf("Bye bye\n");
            *gameState = STOPPED;
            break;
        case 'l': // Fallthrough
        case 'r':
        case 'u':
        case 'd':
            if (*gameState == NOT_INITIALIZED){
                printf("Need to start game first\n");
                return 0;
            }
            return handleMove(choice, board, size, score);
        default:
            printf("Wrong option\n");
    }

    return 0;
}

char displayMainMenu() {
    /*char *menuOptions[] = {"N/n New Game", "R/r Move Right", "L/l Move Left",
        "U/u Move Up", "D/d Move down", "E/e Exit"};
    const int menuCount = sizeof(menuOptions) / sizeof(menuOptions[0]);

    printf("\n\nPlease choose one of the following options:\n");
    for (int i = 0; i < menuCount; i++) {
        printf("%s\n", *(menuOptions+i));
    }*/
    
    printf("\n\nPlease choose one of the following options:\n");
    
    printf("N/n New Game\n");
    printf("R/r Move Right\n");
    printf("L/l Move Left\n");
    printf("U/u Move Up\n");
    printf("D/d Move down\n");
    printf("E/e Exit\n");

    char userChoice;
    scanf(" %c", &userChoice);

    return tolower(userChoice);
}

void playGame(int* board, int size, int scoreToWin) {
    int best = 0;
    int score = 0;
    int gameState = NOT_INITIALIZED;
    int tiles_moved = 1; // Start as 1 to ensure initial display
    int has_valid_moves = 1;

     while (score < scoreToWin && has_valid_moves && gameState != STOPPED) {
         // If a move has been made (or at the start), show the board
        if (tiles_moved)
            displayBoard(board, size, best, score);

         // Get user choice and run the corresponding function
        const char choice = displayMainMenu();
        tiles_moved = runFunction(choice, board, size, &gameState, &score, best, scoreToWin);

         // If tiles were moved this turn, add a random new tile
        if (tiles_moved)
            addRandomTile(board, size, &score);

        // Update best score if needed
        best = score > best ? score : best;

        // Check if any moves remain
        has_valid_moves = hasValidMoves(board, size);
    }

    // Show the final board state unless the user exited
    if (gameState != STOPPED)
        displayBoard(board, size, best, score);

    // Print endgame result
    if (!has_valid_moves)
        printf("Game over your score is %d\n", score);
    else if (score >= scoreToWin)
        printf("You won %d!  - Ending Game\n", score);

    // cleanup
    resetBoard(board, size);
}
