/**
 * @file pieces.h
 * @author Tommaso Soncin
 * @brief Definizione dei pezzi di gioco (tetramini) e delle funzioni associati ad essi
 */

#ifndef PIECES_H
#define PIECES_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "macro.h"
/**
 * @brief Struttura del tetramino
 */
typedef struct tetramino{
    size_t width;
    size_t height;
    unsigned qty;
    char type;
    char* piece;
    char* color;
} Tetramino_t;

/**
 *
 * @param tetramino
 * @param qty
 */
void generatePieces(Tetramino_t *tetramino, unsigned qty);

/**
 * @brief Per ogni pezzo stampa: indice, numero di pezzi rimanenti, tipologia.
 * @param tetramino
 */
void printPieceHint(const Tetramino_t *tetramino);

/**
 *
 * @param tetramino
 * @param rotation
 * @return
 */
Tetramino_t rotatePiece(Tetramino_t tetramino, char rotation);

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

#endif
