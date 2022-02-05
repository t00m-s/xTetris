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
#include <ctype.h>
#include "macro.h"
/**
 * @brief Struttura del tetramino del gioco xTetris.
 */
typedef struct tetramino{
    size_t width;
    size_t height;
    unsigned qty;
    char type;
    char* piece;
} Tetramino_t;

/**
 * @brief Genera tutti i tetramini base del gioco xTetris.
 * @param tetramino Collezione di tetramini.
 * @param qty Numero di tetramini per giocatore.
 */
void generatePieces(Tetramino_t *tetramino, unsigned qty);

/**
 * @brief Per ogni pezzo stampa: indice, numero di pezzi rimanenti, tipologia.
 * @param tetramino Puntatore alla collezione di tetramini per giocatore
 */
void printPieceHint(const Tetramino_t *tetramino);

/**
 * @brief Ruota un tetramino.
 * @param tetramino Tetramino da ruotare.
 * @param rotation Rotazione scelta dal giocatore.
 * @return Copia del tetramino ruotata.
 */
Tetramino_t rotatePiece(Tetramino_t tetramino, char rotation);

/**
 * @brief Libera la memoria occupata dai tetramini.
 * @param tetramino Collezione di tetramini.
 */
void freeAllPieces(Tetramino_t *tetramino);

/**
 * @brief Fornisce all'utente il numero di tetramini per tipologia di tetramino in input
 * @param tetramino Pezzo del gioco xTetris
 * @return Numero di tetramini rimanenti di quella tipologia
 */
unsigned piecesLeft(Tetramino_t tetramino);

/**
 *
 * @param tetramino
 */
void decreaseQty(Tetramino_t *tetramino);

#endif
