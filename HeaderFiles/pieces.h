#ifndef PIECES_H
#include "players.h"
#include <stdio.h>
/*Se il giocatore vuole modificare i simboli*/
const char empty = '-';
const char piece = 'X';

typedef struct tetramino{
    size_t width;
    size_t height;
    unsigned qty;
    char type;
    char* piece;
} Tetramino_t;

void generatePieces(Tetramino_t *tetramino, unsigned qty);
void printPieceStats(const Tetramino_t *tetramino);
Tetramino_t generateRotated(Tetramino_t tetramino, char rotation);
void freeAllPieces(Tetramino_t *tetramino);
unsigned missingPieces(Player_t player);
unsigned piecesLeft(Tetramino_t tetramino);
void decreaseQty(Tetramino_t *tetramino);
#endif