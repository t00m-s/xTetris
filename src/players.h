/**
 * @file players.h
 * @author Tommaso Soncin
 * @brief Definizione del giocatore e funzioni associate ad esso.
 */

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
    unsigned int totalPoints;
    unsigned int totalBrLines;
    int turn;
} Player_t;

/**
 * @brief Aggiorna il prossimo turno dei due giocatori
 * @param p1 Primo giocatore
 * @param p2 Secondo giocatore
 */
void nextTurn(Player_t *p1, Player_t *p2);

/**
 * @brief Inizializza i giocatori (Genera pezzi e campo di gioco)
 * @param p1 Primo giocatore
 * @param p2 Secondo giocatore
 * @param r Righe del campo di gioco
 * @param c Colonne del campo di gioco
 * @param qty Tetramini per giocatore
 */
void startGame(Player_t *p1, Player_t *p2, size_t r, size_t c, unsigned qty);

/**
 * @brief Libera la memoria e stampa i vari risultati della partita.
 * @param p1 Primo giocatore.
 * @param p2 Secondo giocatore.
 * @param isMultiplayer Parametro per stampare o meno i risultati del secondo giocatore.
 */
void endGame(Player_t *p1, Player_t *p2, int isMultiplayer);

/**
 * @brief Stampa i campi di gioco dei due giocatori.
 * @param p1 Primo giocatore.
 * @param p2 Secondo giocatore.
 * @param isMultiplayer Parametro per decidere se stampare anche il campo del secondo giocatore.
 */
void printGame(Player_t p1, Player_t p2, int isMultiplayer);

/**
 * @brief Scansiona tutto il campo di gioco e rimuove le righe completamente piene.
 * @param player Giocatore
 * @param brLines Dove viene salvato il numero di righe rimosse in quel turno.
 */
void removeRows(Player_t *player, unsigned int *brLines);

/**
 * @brief Aggiorna il campo di gioco del giocatore.
 * @param player Giocatore
 */
void updateGame(Player_t *player);

/**
 * @brief Inverte le ultime 'flips' righe del campo di gioco del giocatore.
 * @param player
 * @param flips Numero di righe da invertire
 */
void flipRows(Player_t *player, unsigned int flips);

/**
 * @brief Aggiorna i punteggi del giocatore.
 * @param player Giocatore.
 * @param brLines Numero di righe pulite nel turno attuale.
 */
void updateScore(Player_t *player, unsigned *brLines);

/**
 * @brief Conclude il loop di gioco.
 * @param isPlaying Parametro che determina il loop di gioco.
 */
void setGameOver(int *isPlaying);

/**
 *
 * @param player
 * @return
 */
int  isLastRowEmpty(Player_t player);

/**
 * @brief Inserisce il tetramino con corretta rotazione nel campo di gioco del giocatore.
 * @param player Giocatore
 * @param tetramino Tetramino da inserire nel campo di gioco.
 * @param column Colonna del campo di gioco dove inserire il tetramino.
 * @param rotation Rotazione del tetramino.
 * @return 1 -> Pezzo inserito correttamente.
 *         0 -> Impossibile inserire il pezzo con i parametri passati.
 */
int insertPiece(Player_t *player, size_t nrPiece, unsigned column, char rotation);

/**
 * @brief Calcola quanti tetramini non sono disponibili per essere inseriti nel campo di gioco.
 * @param player Giocatore.
 * @return Numero di tetramini non disponibili per il giocatore.
 */
unsigned int missingPieces(Player_t player);

#endif
