#ifndef __GAME__
#define __GAME__

void initGame(int* board, int boardSize, int *gameState, int scoreToWin, int *score);
void playGame(int* board, int size, int scoreToWin);
int runFunction(char choice, int* board, int size, int *gameState, int *score, int bestScore, int scoreToWin);
char displayMainMenu();


#endif
