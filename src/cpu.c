#include "cpu.h"

/**
 * @brief Funzione d'appoggio che calcola lo stato della gameBoard.
 *        Ad ogni casella corrisponde un valore:
 *          1 -> Casella vuota
 *          0 -> Casella piena
 * @param player Giocatore da analizzare
 * @return Stato della gameBoard.
 */
unsigned int boardStatus(Player_t *player)
{
    unsigned int status = 0;
    size_t i;
    for(i = 0; i < player->gameBoard.r * player->gameBoard.c; ++i)
        if(player->gameBoard.arena[i] == EMPTY_)
            ++status;

    return status;
}

/**
 * @brief Funzione d'appoggio che crea una deep copy della gameBoard di un player
 * @param src Board originale
 * @param dest Dove viene salvata la deep copy della gameBoard originale
 * (Passare puntatore singolo nella funzione)
 */
void copyGame(Player_t *player, Player_t *dest)
{
    size_t i;
    dest->gameBoard.arena = (char *) malloc(player->gameBoard.r * player->gameBoard.c * sizeof(char));
    dest->gameBoard.colors = (char *) malloc(player->gameBoard.r * player->gameBoard.c * sizeof(char));
    if(!dest->gameBoard.arena || !dest->gameBoard.colors)
    {
        puts("Errore durante la copia della gameBoard.");
        exit(EXIT_FAILURE);
    }

    for(i = 0; i < player->gameBoard.r * player->gameBoard.c; ++i)
    {
        dest->gameBoard.arena[i] = player->gameBoard.arena[i];
        dest->gameBoard.colors[i] = player->gameBoard.arena[i];
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
 * @brief Crea una deep copy del giocatore
 * @param player Giocatore xTetris originale
 * @return Deep Copy del player
*/
Player_t copyPlayer(Player_t *player)
{
    Player_t copy;

    copy.gameBoard.r = player->gameBoard.r;
    copy.gameBoard.c = player->gameBoard.c;
    copy.turn = player->turn;
    copy.totalBrLines = player->totalBrLines;
    copy.totalPoints = player->totalPoints;
    copyGame(player, &copy);
    copyPieces(player, &copy);

    return copy;
}

/**
 * @brief Libera la memoria occupata dalla copia.
 * @param copy Copia da rimuovere.
 */
void freeCopy(Player_t *player)
{
    free(player->gameBoard.arena);
    free(player->gameBoard.colors);
    freeAllPieces(player->pieces);
}

/**
 * @brief Calcola una mossa generica
 * @param move Struct che conterrà la mossa di default 
 * @param player Giocatore al quale verrà calcolata la mossa di default
 */
void defaultMove(CpuMove_t *move, Player_t *player)
{
    Player_t fakePlayer = copyPlayer(player);

    move->rotation = 'W';
    move->column = rand() % (player->gameBoard.c - 1);
    move->nrPiece = rand() % (sizeof(player->pieces) / sizeof(Tetramino_t));

    freeCopy(&fakePlayer);
}

CpuMove_t cpuDecision(Player_t *player)
{
    /*
     * Come funziona:
     * (Mossa di default: la prima mossa random che trova)
     * Scansiona la gameBoard per cercare la colonna più vuota
     * 
     * TODO:
     * Recursive CPU? Maybe
    */
    size_t bestColumn = 0, defaultColStats = 0;
    size_t row = 0;
    size_t i = 0, j = 0;
    CpuMove_t result = {0, 0, 'W'};
    size_t adjacent = 0;

    /* defaultColumn ( 0 ) stats */
    for(i = 0; i < player->gameBoard.r; ++i)
        if(player->gameBoard.arena[i * player->gameBoard.c] == EMPTY_)
            ++defaultColStats;

    /* Find the best column */
    for(i = 0; i < player->gameBoard.c; ++i)
    {
        size_t tempStats = 0;
        for(j = 0; j < player->gameBoard.r; ++j)
            if (player->gameBoard.arena[j * player->gameBoard.c + i] == EMPTY_)
                ++tempStats;

        if(tempStats > defaultColStats)
        {
            defaultColStats = tempStats;
            bestColumn = i;
        }
    }


    /* Best column found, find the last empty row*/
    for(i = 0; i < player->gameBoard.r; ++i)
        if(player->gameBoard.arena[i * player->gameBoard.c + bestColumn] == EMPTY_)
            row = i;

    /* Row and column found, check adjacent*/
    for(j = bestColumn; j < player->gameBoard.c; ++j)
        if(player->gameBoard.arena[row * player->gameBoard.c + j] == EMPTY_)
            ++adjacent;
    /*printf("Best:%lu\tAdjacent:%lu\n", bestColumn, adjacent);*/
    result.column = bestColumn;
    /* Random piece based on how many adjacent rows are there */
    if(adjacent == 1)
    {
        result.nrPiece = 0;
        result.rotation = 'A';
    }
    else if(adjacent == 2)
    {
        do
            result.nrPiece = (rand() % 6 ) + 1; /* 1 -- 6 */
         while(player->pieces[result.nrPiece].qty == 0);
        result.rotation = (rand() % 2) ? 'A' : 'D';
    }
    else if(adjacent == 3)
    {
        do
            result.nrPiece = (rand() % 6 ) + 1; /* 1 -- 6 */
        while(player->pieces[result.nrPiece].qty == 0);

        switch (rand() % 4)
        {
            case 3:
                result.rotation = 'D';
                break;
            case 2:
                result.rotation = 'S';
                break;
            case 1:
                result.rotation = 'A';
                break;
            default:
                result.rotation = 'W';
                break;
        }
    }
    else
    {
        do
            result.nrPiece = rand() % 7;
        while(player->pieces[result.nrPiece].qty == 0);

        switch (rand() % 4)
        {
            case 3:
                result.rotation = 'D';
                break;
            case 2:
                result.rotation = 'S';
                break;
            case 1:
                result.rotation = 'A';
                break;
            default:
                result.rotation = 'W';
                break;
        }
    } 
    

    return result;
}
