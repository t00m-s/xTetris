#ifndef PLAYERS_H
#define PLAYERS_H
#include <stdlib.h>
#include "pieces.h"
#include "macro.h"

/**
 * @brief Struttura del giocatore
 */
typedef struct player{
    char* game;
    size_t r;
    size_t c;
    Tetramino_t pieces[7];
    unsigned totalPoints;
    unsigned totalBrLines;
    int turn;
} Player_t;

/**
 * @brief Aggiorna il prossimo turno dei due giocatori
 * @param p1 Primo giocatore
 * @param p2 Secondo giocatore (può essere CPU)
 */
void nextTurn(Player_t *p1, Player_t *p2);

/**
 * @brief Inizializza il campo di gioco,
 * @param p1 Primo giocatore
 * @param p2 Secondo giocatore
 * @param r Righe del campo di gioco
 * @param c Colonne del campo di gioco
 * @param qty Tetramini per giocatore
 */
void startGame(Player_t *p1, Player_t *p2, size_t r, size_t c, unsigned qty);

/**
 * @brief Libera la memoria e stampa i vari risultati della partita.
 * @param p1 Primo giocatore
 * @param p2 Secondo giocatore
 * @param isMultiplayer
 */
void endGame(Player_t *p1, Player_t *p2, int isMultiplayer);

/**
 * @brief Stampa i
 * @param p1 Primo giocatore
 * @param p2 Secondo giocatore
 * @param isMultiplayer
 */
void printGame(Player_t p1, Player_t p2, int isMultiplayer);

/**
 *
 * @param player
 * @param brLines
 */
void removeRows(Player_t *player);

/**
 *
 * @param player
 */
void updateGame(Player_t *player);

/**
 *
 * @param player
 * @param flips
 */
void flipRows(Player_t *player, unsigned flips);

/**
 *
 * @param player
 * @param brLines
 */
void updateScore(Player_t *player, unsigned *brLines);

/**
 *
 * @param isPlaying
 */
void setGameOver(int *isPlaying);

/**
 *
 * @param player
 * @return
 */
int  isLastRowEmpty(Player_t player);

/**
 *
 * @param player
 * @param column
 * @param freeRow
 * @param freeCol
 * @param tetramino
 * @return
 */
int  findFree(Player_t player, unsigned column, unsigned *freeRow, unsigned *freeCol, Tetramino_t tetramino);

/**
 *
 * @param player
 * @param tetramino
 * @param column
 * @param rotation
 * @return
 */
int  insertPiece(Player_t *player, size_t nrPiece, unsigned column, char rotation);

/**
 *
 * @param player
 * @return
 */
unsigned missingPieces(Player_t player);

#endif
