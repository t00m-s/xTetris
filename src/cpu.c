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
    for(i = 0; i < player->board.r * player->board.c; ++i)
        if(player->board.arena[i].cell == EMPTY_)
            ++status;

    return status;
}

/**
 * @brief Funzione d'appoggio che crea una deep copy della board di un player
 * @param src Board originale
 * @param dest Dove viene salvata la deep copy della board originale
 * (Passare puntatore singolo nella funzione)
 */
void copyGame(Player_t *player, Player_t *dest)
{
    size_t i;
    dest->board.arena = (Cell_t *) malloc(player->board.r * player->board.c * sizeof(Cell_t));
    if(!dest->board.arena)
    {
        printf("Errore durante la copia della board.\n");
        exit(EXIT_FAILURE);
    }

    for(i = 0; i < player->board.r * player->board.c; ++i)
    {
        dest->board.arena[i].cell = player->board.arena[i].cell;
        dest->board.arena[i].pieceType = player->board.arena[i].pieceType;
    }
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

    copy.board.r = player->board.r;
    copy.board.c = player->board.c;
    copy.turn = player->turn;
    copy.totalBrLines = player->totalBrLines;
    copy.totalPoints = player->totalPoints;
    copyGame(player, &copy);
    copyPieces(player, &copy);

    return copy;
}

/**
 * @brief Funzione d'appoggio che libera la memoria occupata dalla copia.
 * @param copy Copia da rimuovere.
 */
void freeCopy(Player_t *player)
{
    free(player->board.arena);
    freeAllPieces(player->pieces);
}

/**
 * @brief Funzione d'appoggio che calcola una mossa legale
 * @param move Struct che conterrà la mossa di default 
 * @param player Giocatore al quale verrà calcolata la mossa di default
 */
void defaultMove(CpuMove_t *move, Player_t *player)
{
    char rotations[] = {'W', 'A', 'S', 'D'};
    size_t rot, col, nrPiece;
    int found = 0;
    Player_t fakePlayer;

    while(!found)
    {
        rot = rand() % 4;
        col = rand() % player->board.c;
        nrPiece = rand() % (sizeof(player->pieces) / sizeof(Tetramino_t));
        fakePlayer = copyPlayer(player);
        if(insertPiece(&fakePlayer, nrPiece, col, rotations[rot]))
        {
            move->rotation = rotations[rot];
            move->column = col;
            move->nrPiece = nrPiece;
            found = 1;
        }
        freeCopy(&fakePlayer);
    }
}

CpuMove_t cpuDecision(Player_t *player)
{
    /*
     * Come funziona:
     * (Mossa di default: la prima mossa random legale che trova)
     * Scansiona la board per cercare la colonna più vuota
     * TODO:
     * CPU meno stupida
    */
    size_t bestColumn = 0, defaultStats = 0;
    size_t row = 0;
    size_t i = 0, j = 0;
    CpuMove_t result;
    Player_t fakePlayer = copyPlayer(player);
    size_t adjacent = 1;

    defaultMove(&result, &fakePlayer);
    freeCopy(&fakePlayer);

    /* defaultColumn stats */
    for(i = 0; i < player->board.c; ++i)
        for(j = 0; j < player->board.r; ++j)
            if(player->board.arena[j * player->board.c + j].cell == EMPTY_)
                ++defaultStats;

    /* Find the best column */
    for(i = 0; i < player->board.c; ++i)
    {
        size_t tempStats = 0;
        for(j = 0; j < player->board.r; ++j)
            if(player->board.arena[j * player->board.c + j].cell == EMPTY_)
                ++tempStats;

        if(tempStats > defaultStats)
            bestColumn = i;
    }


    /* Best column found, find the last empty row*/
    for(i = 0; i < player->board.r; ++i)
        if(player->board.arena[i * player->board.c + bestColumn].cell == EMPTY_)
            row = i;

    /* Row and column found, check adjacent*/
    for(j = bestColumn; j < player->board.c && adjacent < 4; ++j)
        if(player->board.arena[row * player->board.c + j].cell == EMPTY_)
            ++adjacent;


    if(adjacent == 1) /* Colonna libera */
    {
        if(player->pieces[0].qty)
        {
            result.column = bestColumn;
            result.nrPiece = 0;
            result.rotation = 'A';
        }
    }
    else if(adjacent == 2) /* Colonna + successiva */
    {
        /*
         * Pezzi possibili:
         *
        */
    }
    return result;
}
