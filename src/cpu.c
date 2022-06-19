#include "cpu.h"

CpuMove_t cpuDecision(Player_t *player, Tetramino_t collection[7])
{
    /*
     * TODO:
     * Recursive CPU?
    */
    size_t bestColumn = 0, defaultColStats = 0;
    size_t row = 0;
    size_t i = 0, j = 0;
    CpuMove_t result = { 0, 0, 'W'};
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
         while(collection[result.nrPiece].qty == 0);
        result.rotation = (rand() % 2) ? 'A' : 'D';
    }
    else if(adjacent == 3)
    {
        do
            result.nrPiece = (rand() % 6 ) + 1; /* 1 -- 6 */
        while(collection[result.nrPiece].qty == 0);

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
        while(collection[result.nrPiece].qty == 0);

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
