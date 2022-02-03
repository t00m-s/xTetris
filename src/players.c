#include "players.h"

void nextTurn(Player_t *p1, Player_t *p2)
{
    if(p1->turn)
    {
        p1->turn = 0;
        p2->turn = 1;
    }
    else
    {
        p1->turn = 1;
        p2->turn = 0;
    }
}

void startGame(Player_t *p1, Player_t *p2, size_t r, size_t c, unsigned qty)
{
    int i, j;
    p1->game = (char*) malloc(r * c * sizeof(char));
    p1->r = r;
    p1->c = c;
    p1->totalPoints = 0;
    p1->totalBrLines = 0;

    p2->game = (char*) malloc(r * c * sizeof(char));
    p2->r = r;
    p2->c = c;
    p2->totalPoints = 0;
    p2->totalBrLines = 0;

    for(i = 0; i < r; i++)
    {
        for (j = 0; j < c; j++)
        {
            p1->game[i * c + j] = EMPTY_;
            p2->game[i * c + j] = EMPTY_;
        }
    }
    generatePieces(p1->pieces, qty);
    generatePieces(p2->pieces, qty);
    p1->turn = 1; /*Default: Comincia P1*/
    p2->turn = 0;
}

void endGame(Player_t *p1, Player_t *p2, int isMultiplayer)
{
    printf("Player1:\nRighe rimosse: %d\nPunteggio totale:%d\n\n", p1->totalBrLines, p1->totalPoints);
    if(isMultiplayer)
        printf("Player2:\nRighe rimosse: %d\nPunteggio totale:%d\n\n", p2->totalBrLines, p2->totalPoints);

    free(p1->game);
    free(p2->game);
    freeAllPieces(p1->pieces);
    freeAllPieces(p2->pieces);
}

void printGame(Player_t p1, Player_t p2, int isMultiplayer)
{
    size_t i, j;
    /*
     * ANSI Escape Code per pulire lo schermo
     * Non so se funziona lol

    printf("\033[2J\033[1;1H");
    */
    for(i = 0; i < p1.r; ++i)
    {
        /* Stampa contenuto board di gioco */
        for (j = 0; j < p1.c; ++j)
            printf("%c  ", p1.game[i * p1.c + j]);

        printf("\t\t");

        if(isMultiplayer)
            for(j = 0; j < p2.r; ++j)
                printf("%c  ", p2.game[i * p2.c + j]);

        printf("\n");
    }

    /* Stampa indici di gioco */
    for(j = 0; j < p1.c; ++j)
    {
        if(j > 9)
            printf("%lu ", j);
        else
            printf("%lu  ", j);
    }

    printf("\t\t");

    if(isMultiplayer)
    {
        for(j = 0; j < p2.c; ++j)
        {
            if(j > 9)
                printf("%lu ", j);
            else
                printf("%lu  ", j);
        }
    }
    printf("\n");
}

int isLegalMove(Player_t player, const unsigned freeRow, const unsigned freeCol, Tetramino_t tetramino)
{
    size_t i = 0, j = 0;
    size_t tetH = 0, tetW = 0;
    /*Controllare limiti*/
    if(tetramino.width + freeCol > player.c || freeRow + tetramino.height  > player.r)
        return 0;

    for(i = freeRow, tetH = 0; i < (freeRow + tetramino.height) && tetH < tetramino.height; ++i, ++tetH) /*Scorro i due indici contemporaneamente*/
        for (j = freeCol, tetW = 0; j < (freeCol + tetramino.width) && tetW < tetramino.width; ++j, ++tetW)
            if (player.game[i * player.c + j] == PIECE_ && tetramino.piece[tetH * tetramino.width + tetW] == PIECE_) /*Controlla collisioni*/
                return 0; /*Bug Risolto: tetH * tetramino.width è corretto invece di tetramino.height*/

    return 1;
}

int findFree(Player_t player, unsigned column, unsigned *freeRow, unsigned *freeCol, Tetramino_t tetramino)
{
    size_t i;
    int found = 0;
    for(i = 0; i < player.c; ++i)
    {
        /*Anche se la board ha già un pezzo potrei ignorarlo se il tetramino in quella posizione è vuoto*/
        if(player.game[i * player.c + column] == EMPTY_ || tetramino.piece[0] == EMPTY_)
        {
            if(isLegalMove(player, i, column, tetramino))
            {
                *freeRow = i;
                *freeCol = column;
                found = 1;
            }
            else
                break;
        }
    }

    return found;
}

/**
 * @brief Funzione di appoggio per creare la deepCopy che verrà modificata nella rotazione
 * @param tetramino Tetramino originale
 * @return DeepCopy del tetramino in input
 */
Tetramino_t deepCopyTetramino(Tetramino_t tetramino)
{
    Tetramino_t cpy;
    size_t i;
    cpy.width = tetramino.width;
    cpy.height = tetramino.height;
    cpy.type = tetramino.type;
    cpy.qty = tetramino.qty;
    cpy.piece = (char*) malloc(tetramino.width * tetramino.height * sizeof(char));

    for(i = 0; i < tetramino.width * tetramino.height; ++i)
        cpy.piece[i] = tetramino.piece[i];

    return cpy;
}

int insertPiece(Player_t *player, size_t nrPiece, unsigned column, char rotation)
{
    size_t i, j, tetW, tetH;
    unsigned freeRow, freeCol;
    /*
     * Copia creata per evitare di modificare il puntatore originale
     * (che aveva causato bug visto che lo sovrascrivevo ruotandolo)
    */
    Tetramino_t tetraminoCopy = rotatePiece(deepCopyTetramino(player->pieces[nrPiece]), rotation);
    if(findFree(*player, column, &freeRow, &freeCol, tetraminoCopy) && isLegalMove(*player, freeRow, freeCol, tetraminoCopy))
    {
        for(i = freeRow, tetH = 0; i < (freeRow + tetraminoCopy.height) && tetH < tetraminoCopy.height; ++i, ++tetH)    /*Scorro i due indici contemporaneamente*/
            for(j = freeCol, tetW = 0; j < (freeCol + tetraminoCopy.width) && tetW < tetraminoCopy.width; ++j, ++tetW)  /* Rimosso if */
                if(tetraminoCopy.piece[tetH * tetraminoCopy.width + tetW] == PIECE_) /* Evita di sovrascrivere altri pezzi */
                    player->game[i * player->c + j] = tetraminoCopy.piece[tetH * tetraminoCopy.width + tetW];

        free(tetraminoCopy.piece);
        return 1;
    }
    free(tetraminoCopy.piece);
    return 0;
}

void removeRows(Player_t *player)
{
    int i = 0, j = 0; /*Unironically wasted two hours to fix from size_t to int*/
    size_t isFull = 0;

    for(i = (int)player->r - 1; i >= 0; --i)
    {
        for (j = 0; j < player->c; j++)
            if (player->game[i * player->c + j] == PIECE_)
                ++isFull;
            else
                break;

        /* Rimuove la riga se completamente piena */
        if (isFull == player->c)
        {
            for (j = 0; j < player->c; ++j)
                player->game[i * player->c + j] = EMPTY_;

            ++player->totalBrLines;
        }
        isFull = 0;
    }
}

void updateGame(Player_t *player)
{
    size_t i, j;
    while(isLastRowEmpty(*player))
    {
        for (i = player->r - 1; i > 0; --i)
            for (j = 0; j < player->c; ++j)
                player->game[i * player->c + j] = player->game[(i - 1) * player->c + j];
    }
}

void flipRows(Player_t *player, unsigned int flips)
{
    size_t i, j;
    if(!flips) /*Non può invertire 0 righe */
        return;

    for(i = player->r - 1; i >= player->r - flips; --i)
        for(j = 0; j < player->c; ++j)
            if(player->game[i * player->c + j] == PIECE_)
                player->game[i * player->c + j] = EMPTY_;
            else
                player->game[i * player->c + j] = PIECE_;
}

int isLastRowEmpty(Player_t player)
{
    size_t j;
    unsigned isEmpty = 0;

    for (j = 0; j < player.c; ++j)
        if (player.game[(player.r - 1) * player.c + j] == EMPTY_)
            ++isEmpty;
        else
            break;

    return isEmpty == player.c;
}

void updateScore(Player_t *player, unsigned *brLines)
{
    /*
    * La rimozione di una riga vale 1 punto,
    * la rimozione di due righe con un solo pezzo vale 3 punti,
    * tre righe 6 punti,
    * quattro righe 12 punti
     * Con multiplayer dopo chiamo flip rows
    */
    switch(*brLines)
    {
        case 1:
            player->totalPoints += 1;
            break;
        case 2:
            player->totalPoints += 3;
            break;
        case 3:
            player->totalPoints += 6;
            break;
        case 4:
            player->totalPoints += 12;
            break;
        default:
            break;
    }

    player->totalBrLines += *brLines;
    *brLines = 0;
}

void setGameOver(int *isPlaying)
{
    *isPlaying = 0;
}

unsigned missingPieces(const Player_t player)
{
    size_t i, flag = 0;

    for(i = 0; i < 7; ++i)
        if(!player.pieces[i].qty)
            ++flag;

    return flag;
}
