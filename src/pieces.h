#ifndef PIECES_H
#define PIECES_H
#include <stdio.h>
#include "definePieces.h"
typedef struct tetramino{
    size_t width;
    size_t height;
    unsigned qty;
    char type;
    char* piece;
} Tetramino_t;

void generatePieces(Tetramino_t *tetramino, unsigned qty);
void printPieceStats(const Tetramino_t *tetramino);
Tetramino_t generateRotated(Tetramino_t tetramino);
void freeAllPieces(Tetramino_t *tetramino);
unsigned piecesLeft(Tetramino_t tetramino);
void decreaseQty(Tetramino_t *tetramino);
int typeRotation(char rotation);
void rotate90DegPiece(Tetramino_t *tetramino);
#endif
