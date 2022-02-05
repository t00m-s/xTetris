#include "cpu.h"

/**
 * @file cpu.c
 * @author Tommaso Soncin
 * @brief Implementazione delle funzioni della CPU per il gioco xTetris
 */

/**
 * @brief Implementazione della struct cpuDecision
 */
struct cpuDecision{
    /** @brief Indice del tetramino scelto dalla CPU */
    unsigned int nrPiece;
    /** @brief Colonna scelta dalla cpu */
    unsigned int column;
    /** @breif Rotazione scelta dalla cpu */
    char rotation;
};

/**
 * @brief Funzione d'appoggio, crea una deep copy della board del player
 * @param player Giocatore da cui copiare la board
 * @return Deep copy della board di gioco
 */
char* copyGame(Player_t *player)
{
    size_t i;
    char* deepCopy = (char*) malloc(player->r * player->c * sizeof(char));
    for(i = 0; i < player->r * player->c; ++i)
        deepCopy[i] = player->game[i];

    return deepCopy;
}

/**
 * @brief Funzione d'appoggio che libera la memoria occupata dalla copia.
 * @param copy Copia da rimuovere.
 */
void deleteCopy(char* copy)
{
    free(copy);
}

/**
 * @brief Funzione d'appoggio che calcola lo stato della board.
 *        Ad ogni casella corrisponde un valore:
 *          1 -> Casella vuota
 *          0 -> Casella piena
 * @param player Giocatore da analizzare
 * @return Stato della board.
 */
unsigned int boardStatus(Player_t player)
{
    unsigned int status = 0;
    size_t i;
    for(i = 0; i < player.r * player.c; ++i)
        status = player.game[i] == EMPTY_ ? status + 1 : status;

    return status;
}

cpuMove_t cpuDecision(Player_t *player)
{
    /*
     * Come funziona:
     * Scansiono la board di gioco
        *EMPTY_ vale 1
        *PIECE_ vale 0
     * Provo tutte le mosse con tutte le rotazioni
     * (Mossa di default: la prima provata)
     * quella che mi dà status minore tra le mosse viene scelta
     * Devo mettere che la CPU prova ad evitare colonne non completamente vuote
    */
    size_t i, j;
    unsigned int stat;
    cpuMove_t result, backupMove;
    char* copy;
    char rotations[] = {'W', 'A', 'S', 'D'};
    Player_t fakePlayer;




    for(i = 0; i < sizeof(player->pieces) / sizeof(Tetramino_t); ++i)
    {
        copy = copyGame(player);
        /*insertPiece();  Workaround: Creo un player tarocco */

        deleteCopy(copy);
    }
    return result;
}
