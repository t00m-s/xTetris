#include "cpu.h"

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
 * @brief Funzione d'appoggio che crea una deep copy della board di un player
 * @param src Board originale
 * @param dest Dove viene salvata la deep copy della board originale
 * (Passare puntatore singolo nella funzione)
 */
void copyGame(Player_t *player, char *dest)
{
    size_t i;
    dest = (char*) malloc(player->r * player->c * sizeof(char));
    if(!dest)
    {
        printf("Errore durante la copia della board.\n");
        exit(EXIT_FAILURE);
    }

    for(i = 0; i < player->r * player->c; ++i)
        dest[i] = player->game[i];
}

void copyPieces(Player_t *src, Player_t *dest)
{
    size_t i, j;

    for(i = 0; i < sizeof(src->pieces) / sizeof(Tetramino_t); ++i)
    {
        dest->pieces[i].height = src->pieces[i].height;
        dest->pieces[i].width = src->pieces[i].width;
        dest->pieces[i].qty = src->pieces[i].qty;
        dest->pieces[i].type = src->pieces[i].type;

        dest->pieces[i].piece = (char*) malloc(src->pieces[i].height * src->pieces[i].width * sizeof(char));
        if(!dest->pieces[i].piece)
        {
            printf("Errore durante la mossa della CPU (Tetramini).\n");
            exit(EXIT_FAILURE);
        }

        for(j = 0; j < src->pieces[i].height * src->pieces[i].width; ++j)
            dest->pieces[i].piece[j] = src->pieces[i].piece[j];

    }
}

/**
 * @brief Funzione d'appoggio che crea una deep copy del player
 * @param player Giocatore xTetris originale
 * @param qty Numero di tetramini
 * @return Deep Copy del player
*/
Player_t copyPlayer(Player_t *player)
{
    Player_t copy;

    copy.r = player->r;
    copy.c = player->c;
    copy.turn = player->turn;
    copy.totalBrLines = player->totalBrLines;
    copy.totalPoints = player->totalPoints;
    copyGame(player, copy.game);
    copyPieces(player, &copy);

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
        EMPTY_ = 1
        PIECE_ = 0
     * Provo tutte le mosse con tutte le rotazioni
     * (Mossa di default: la prima provata e che sia legale)
     * quella che mi dà status maggiore tra le mosse viene scelta
     * LISTA DI BUG:
     *  fakeMove fa la mossa sulla board originale (Forse perchè la board è nello heap?)
     *  durante copyPlayer il puntatore di player viene passato come NULL
    */
    size_t piece, rot;
    unsigned int stat = boardStatus(player), col;
    cpuMove_t result;
    char rotations[] = {'W', 'A', 'S', 'D'};
    unsigned int tempPoint = 0;
    Player_t fakePlayer;
    /* Mossa di default per ora */
    result.column = 4;
    result.nrPiece = 2;
    result.rotation = rotations[rand()%4];
    for(col = 0; col < player->c; ++col)
    {
        for(piece = 0; piece < sizeof(player->pieces) / sizeof(Tetramino_t); ++piece)
        {
            for(rot = 0; rot < 4; ++rot)
            {
                unsigned int statAfter;
                fakePlayer = copyPlayer(player);
                if(insertPiece(&fakePlayer, piece, col, rotations[rot]))
                {
                    removeRows(&fakePlayer, &tempPoint);
                    updateGame(&fakePlayer);
                    statAfter = boardStatus(&fakePlayer);
                    if(statAfter > stat)
                    {
                        result.nrPiece = piece;
                        result.rotation = rotations[rot];
                        result.column = col;
                    }
                }
                freeCopy(&fakePlayer);
            }
        }
    }
    return result;
}
