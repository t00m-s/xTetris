#include "cpu.h"
/**
 * @brief Implementazione della struct cpuDecision
 */


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
void deleteCopy(char* copy){ free(copy); }

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

Player_t copyPlayer(Player_t *player, unsigned int qty)
{
    Player_t copy;
    copy.r = player->r;
    copy.c = player->c;
    copy.turn = player->turn;
    copy.game = copyGame(player);
    /* La quantità potrebbe non essere esatta ma non è rilevante */
    generatePieces(copy.pieces, qty);
    return copy;
}

/**
 * @brief Funzione d'appoggio che imposta una mossa di default nel caso in cui non esistano mosse
 * W.I.P.
 * @param player
 * @param move
 */
void defaultMove(Player_t *player, cpuMove_t *move)
{
    size_t i;
    for(i = 0; i < sizeof(player->pieces) / sizeof(Tetramino_t); ++i)
        if(player->pieces[i].qty)
        {
            move->nrPiece = i;
            move->column = rand()%player->c;
            move->rotation = 'W';
            return;
        } 
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
    */
    size_t i, j, col;
    unsigned int stat = boardStatus(*player);
    cpuMove_t result;
    char rotations[] = {'W', 'A', 'S', 'D'};
    Player_t fakePlayer;
    unsigned int trashcan = 0;
    defaultMove(player, &result);
    
    for(col = 0; col < player->c; ++col)
    {
        for (i = 0; i < sizeof(player->pieces) / sizeof(Tetramino_t); ++i)
        {
            for (j = 0; j < 4; ++j)
            {

                fakePlayer = copyPlayer(player, player->pieces[i].qty);
                if(insertPiece(&fakePlayer, i, col, rotations[j])) /*  Workaround: Creo un player tarocco */
                {
                    unsigned int statNow;
                    removeRows(&fakePlayer, &trashcan);
                    updateGame(&fakePlayer);
                    statNow = boardStatus(fakePlayer);
                    if(statNow > stat)
                    {
                        result.column = col;
                        result.nrPiece = i;
                        result.rotation = rotations[j];
                    }
                }
                deleteCopy(fakePlayer.game);
            }
        }
    }
    return result;
}
