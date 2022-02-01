#include "cpu.h"

/**
 * @brief Crea una deep copy della board del player
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
 * @brief Annulla la mossa
 * @param player
 * @param tetramino
 */
void undoMove(Player_t *player, Tetramino_t tetramino)
{

}

void easyCPU(Player_t *player)
{
    /*
     * Come funziona:
     * Scansiono la board di gioco
        *EMPTY_ vale 1
        *PIECE_ vale 0
     * Provo tutte le mosse con tutte le rotazioni
     * (deve esserci una mossa di default)
     * quella che mi da status minore tra le mosse viene scelta
     *
    */
    size_t i;
    unsigned int status = 0;
    for(i = 0; i < player->r * player->c; ++i)
        status = player->game[i] == EMPTY_ ? status + 1 : status;


}


