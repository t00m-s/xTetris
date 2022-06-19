/**
 * @file players.h
 * @author Tommaso Soncin
 * @brief Definizione del giocatore di xTetris e funzioni associate ad esso.
 */

#ifndef PLAYERS_H
#define PLAYERS_H
#include <stdlib.h>
#include "pieces.h"
#include "macro.h"

/**
 * @brief Struttura del campo di gioco
 */
typedef struct board{
    char *arena;
    char *colors;
    size_t r;
    size_t c;
} Board_t;

/**
 * @brief Struttura del giocatore
 */
typedef struct player{
    Board_t gameBoard;
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
 * @brief Inizializza tutti i campi e valori dei giocatori.
 * @param p1 Primo giocatore
 * @param p2 Secondo giocatore
 * @param collection Tetramini usabili
 * @param isMultiplayer Parametro che stabilisce se raddoppiare o meno i tetramini
 */
void startGame(Player_t *p1, Player_t *p2, Tetramino_t collection[7], int isMultiplayer);

/**
 * @brief Libera la memoria e stampa i vari risultati della partita.
 * @param p1 Primo giocatore.
 * @param p2 Secondo giocatore.
 * @param isMultiplayer Parametro per stampare o meno i risultati del secondo giocatore.
 */
void endGame(Player_t *p1, Player_t *p2, Tetramino_t collection[7], int isMultiplayer);

/**
 * @brief Stampa i campi di gioco dei due giocatori.
 * @param p1 Primo giocatore.
 * @param p2 Secondo giocatore.
 * @param isMultiplayer Parametro per decidere se stampare anche il campo del secondo giocatore.
 */
void printGame(const Player_t *p1, const Player_t *p2, int isMultiplayer);

/**
 * @brief Stampa il campo di gioco senza colori
 * @param p1 Primo giocatore
 * @param p2 Secondo giocatore 
 * @param isMultiplayer Parametro per decidere se stampare anche il campo del secondo giocatore.
 */
void printDebug(const Player_t *p1, const Player_t *p2, int isMultiplayer);

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
 * @brief Inverte le ultime righe del campo di gioco del giocatore.
 * @param player Giocatore
 * @param flips Numero di righe da invertire
 */
void flipRows(Player_t *player, unsigned int flips);

/**
 * @brief Aggiorna i punteggi del giocatore.
 * @param player Giocatore.
 * @param brLines Numero di righe pulite nel turno attuale.
 */
void updateScore(Player_t *player, unsigned int brLines);

/**
 * @brief Conclude il loop di gioco.
 * @param isPlaying Parametro che determina il loop di gioco.
 */
void setGameOver(int *isPlaying);

/**
 * @brief Inserisce il tetramino con corretta rotazione nel campo di gioco del giocatore.
 * @param player Giocatore
 * @param tet Tetramino da inserire nel campo di gioco.
 * @param column Colonna del campo di gioco dove inserire il tetramino.
 * @param rotation Rotazione del tetramino.
 * @return 1 -> Pezzo inserito correttamente.
 * @return 0 -> Impossibile inserire il pezzo con i parametri passati.
 */
int insertPiece(Player_t *player, Tetramino_t *tet, unsigned column, char rotation);

/**
 * @brief Pulisce il terminale.
 */
void clearScreen();

/**
 * @brief Funzione che controlla se è ancora possibile continuare la partita
 * @param collection Collezione di tetramini
 * @return 1 -> La partita può continuare.
 * @return 0 -> La partita non può continuare
 */
int isPlayable(const Tetramino_t *collection);

/**
 * @brief Turno xTetris nel caso giocatore singolo
 * @param player Giocatore
 * @param tet Tetramino da posizionare
 * @param column Colonna dove verrà inserito il tetrmaino scelto
 * @param rotation Rotazione del tetramino scelto
 * @return 1 -> Turno concluso correttamente.
 * @return 0 -> Turno concluso in modo non corretto.
 */
int singlePlayerTurn(Player_t *player, Tetramino_t *tet, unsigned int column, char rotation);

/**
 * @brief Turno xTetris nel caso multigiocatore
 * @param player Primo giocatore
 * @param player2 Secondo giocatore
 * @param tet Tetramino da posizionare
 * @param column Colonna nella quale verrà inserito il tetramino
 * @param rotation Eventuale rotazione del tetramino scelto
 * @return 1 -> Turno concluso correttamente.
 * @return 0 -> Turno concluso in modo non corretto.
 */
int multiPlayerTurn(Player_t *player, Player_t *player2, Tetramino_t *tet, unsigned int column, char rotation);

/**
 * @brief Richiede all'utente i parametri per effettuare il turno
 * @param nrPiece Indice del tetramino da scegliere
 * @param column Colonna nella quale verrà posizionato il tetramino
 * @param rotation Rotazione del tetramino
 */
void getUserInput(size_t *nrPiece, unsigned int *column, char *rotation);

#endif
