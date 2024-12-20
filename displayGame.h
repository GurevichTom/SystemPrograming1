#ifndef __DISPLAYGAME__
#define __DISPLAYGAME__

void displayRowDelimiter(int size);
void printStartMessage(int winScore);
void displayScore(int best, int score);
void displayRow(const int* row, int size);
void displayBoard(const int* board, int size, int best, int score);


#endif
