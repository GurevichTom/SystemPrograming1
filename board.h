//
// Created by Tom on 06.12.2024.
//

#ifndef BOARD_H
#define BOARD_H

void setRandomEmtpyPos(int* board, int size, int val);
void initBoard(int* board, int size);
void resetBoard(int* board, int size);
int hasValidMoves(const int* board, int size);
void addRandomTile(int* board, int size);
#endif //BOARD_H
