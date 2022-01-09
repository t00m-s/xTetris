#ifndef PLAYERS_H
#define PLAYERS_H
#include <stdlib.h>
#include "pieces.h"
#include "definePieces.h"
typedef struct player{
    char* game;
    size_t r;
    size_t c;
    Tetramino_t pieces[7];
    unsigned qty;
    unsigned totalPoints;
    unsigned totalBrLines;
    int turn;
}Player_t;

void nextTurn(Player_t *p1, Player_t *p2);
void startGame(Player_t *p1, Player_t *p2, size_t r, size_t c, unsigned qty);
void endGame(Player_t p1, Player_t p2, int isMultiplayer);
void printGame(Player_t p1, Player_t p2, int isMultiplayer);
void removeRows(Player_t *player, unsigned *brLines);
void updateGame(Player_t *player);
void flipRows(Player_t *player, unsigned flips);
void updateScore(Player_t *player, unsigned *brLines);
void setGameOver(int *isPlaying);
int  isLastRowEmpty(Player_t player);
int  findFree(Player_t player, unsigned column, unsigned *freeRow, unsigned *freeCol, Tetramino_t tetramino);
int  insertPiece(Player_t *player, Tetramino_t tetramino, unsigned column, char rotation);
unsigned missingPieces(Player_t player);

#endif
