#include "cpu.h"

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
 * @brief Funzione d'appoggio per effettuare una copia dei tetramini del giocatore in input.
 * @param player Giocatore da cui copiare i tetramini.
 * @return Copia dei tetramini del giocatore. 
 */
Tetramino_t* copyPiece(Tetramino_t *piece)
{
    size_t i, j;
    Tetramino_t temp;
    temp.height = piece->height;
    temp.width = piece->width;
    temp.qty = piece->qty;
    temp.type = piece->type;
    for(i = 0; i < sizeof(piece) / sizeof(Tetramino_t); ++i)
    {
        
        for(j = 0; j < piece->height * piece->width; ++j)
        
    }
    
    return temp;
}

/**
 * @brief Funzione d'appoggio che calcola lo stato della board.
 *        Ad ogni casella corrisponde un valore:
 *          1 -> Casella vuota
 *          0 -> Casella piena
 * @param player Giocatore da analizzare
 * @return Stato della board.
 */
unsigned int boardStatus(Player_t *player)
{
    unsigned int status = 0;
    size_t i;
    for(i = 0; i < player->r * player->c; ++i)
        status = player->game[i] == EMPTY_ ? status + 1 : status;

    return status;
}

/**
 *@brief Funzione d'appoggio che crea una deep copy del player
 *@param player Giocatore xTetris originale
 *@param qty Numero di tetramini
 *@return Deep Copy del player
*/
Player_t copyPlayer(Player_t *player, unsigned int qty)
{
    Player_t copy;
    size_t i;
    copy.r = player->r;
    copy.c = player->c;
    copy.turn = player->turn;
    copy.game = copyGame(player);
    copy.pieces = NULL; //TODO: finire funzione copyPieces
    return copy;
}

/**
 * @brief Funzione d'appoggio che libera la memoria occupata dalla copia.
 * @param copy Copia da rimuovere.
 */
void freeCopy(Player_t *player)
{
    free(player->game);
    freeAllPieces(player->pieces);
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
     * quella che mi dà status maggiore tra le mosse viene scelta
     * LISTA DI BUG:
     *  fakeMove fa la mossa sulla board originale (Forse perchè la board è nello heap?)
    */
    size_t i, j, col;
    unsigned int stat = boardStatus(player);
    cpuMove_t result;
    char rotations[] = {'W', 'A', 'S', 'D'};
    unsigned int tempPoint = 0;
    Player_t fakePlayer;

    for(col = 0; col < player->c; ++col)
    {
        for (i = 0; i < sizeof(player->pieces) / sizeof(Tetramino_t); ++i)
        {
            for (j = 0; j < 4; ++j)
            {
                fakePlayer = copyPlayer(player, player->pieces[i].qty);
                if(insertPiece(&fakePlayer, i, col, rotations[j]))
                {
                    unsigned int statAfter;

                    statAfter = boardStatus(&fakePlayer);
                    if(statAfter > stat)
                    {
                        result.column = col;
                        result.nrPiece = i;
                        result.rotation = rotations[j];
                    }
                    freeCopy(&fakePlayer);
                }
            }
        }
    }
    return result;
}
