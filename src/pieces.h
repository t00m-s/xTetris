#ifndef PIECES_H
#define PIECES_H
#include <stdio.h>
#include "definePieces.h"
/**
 * @brief Struttura del tetramino
 */
typedef struct tetramino{
    size_t width;
    size_t height;
    unsigned qty;
    char type;
    char* piece;
} Tetramino_t;

/**
 *
 * @param tetramino
 * @param qty
 */
void generatePieces(Tetramino_t *tetramino, unsigned qty);

/**
 *
 * @param tetramino
 */
void printPieceStats(const Tetramino_t *tetramino);

/**
 *
 * @param tetramino
 * @return
 */
Tetramino_t generateRotated(Tetramino_t tetramino);

/**
 *
 * @param tetramino
 */
void freeAllPieces(Tetramino_t *tetramino);
/**
 *
 * @param tetramino
 * @return
 */
unsigned piecesLeft(Tetramino_t tetramino);

/**
 *
 * @param tetramino
 */
void decreaseQty(Tetramino_t *tetramino);

/**
 *
 * @param rotation
 * @return
 */
int typeRotation(char rotation);

/**
 *
 * @param tetramino
 */
void rotate90DegPiece(Tetramino_t *tetramino);
#endif
