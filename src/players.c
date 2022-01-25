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
    int i, j;

    if(isMultiplayer)
    {
        for(i = 0; i < p1.r; ++i)
        {
            for(j = 0; j < p1.c; ++j)
                printf("%c ", p1.game[i * p1.c + j]);

            printf("\t\t");

            for(j = 0; j < p2.c; j++)
                printf("%c ", p2.game[i * p2.c + j]);
            printf("\n");
        }
        for(j = 0; j < p1.c; j++)
            printf("%d ", j);
        printf("\t\t");
        for(j = 0; j < p1.c; ++j)
            printf("%d ", j);
        printf("\n");
        return;
    }

    for(i = 0; i < p1.r; i++)
    {
        for(j = 0; j < p1.c; j++) /* Stampa contenuto matrice di gioco */
            printf("%c ", p1.game[i * p1.c + j]);

        printf("\n");
    }

    for(j = 0; j < p1.c; j++) /* Stampa indice colonne */
        printf("%d ", j);

    printf("\n");
}

int isLegalMove(Player_t player, const unsigned freeRow, const unsigned freeCol, Tetramino_t tetramino)
{   /*Qui controlla se l'espansione è possibile*/
    size_t i = 0, j = 0;
    size_t tetH = 0, tetW = 0;
    /*Controllare limiti*/
    if(tetramino.width + freeCol > player.c || freeRow + tetramino.height  > player.r)
        return 0;

    for(i = freeRow, tetH = 0; i < (freeRow + tetramino.height) && tetH < tetramino.height; ++i, ++tetH) /*Scorro i due indici contemporaneamente*/
        for(j = freeCol, tetW = 0; j < (freeCol + tetramino.width) && tetW < tetramino.width; ++j, ++tetW)
            if(player.game[i * player.c + j] == PIECE_ && tetramino.piece[tetH * tetramino.height + tetW] == PIECE_) /*Controlla collisioni*/
                return 0;

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


int insertPiece(Player_t *player, Tetramino_t tetramino, unsigned column, char rotation) /*Da inserire la rotazione*/
{
    size_t i, j, tetW, tetH;
    unsigned freeRow, freeCol;
    unsigned rotType = typeRotation(rotation);    /*Passo una copia così posso ruotarla a piacimento*/
    tetramino = rotatePiece(tetramino, rotType);

    if(findFree(*player, column, &freeRow, &freeCol, tetramino) && isLegalMove(*player, freeRow, freeCol, tetramino))
    {
        for(i = freeRow, tetH = 0; i < (freeRow + tetramino.height) && tetH < tetramino.height; ++i, ++tetH)    /*Scorro i due indici contemporaneamente*/
            for(j = freeCol, tetW = 0; j < (freeCol + tetramino.width) && tetW < tetramino.width; ++j, ++tetW)  /*Controlla collisioni*/
                if(tetramino.piece[tetH * tetramino.width + tetW] == PIECE_)
                    player->game[i * player->c + j] = tetramino.piece[tetH * tetramino.width + tetW];


        return 1;
    }
    return 0;
}

void removeRows(Player_t *player)
{
    int i = 0, j = 0; /*Unironically wasted two hours to fix from size_t to int*/
    size_t isFull = 0;

    for(i = (int)player->r - 1; i >= 0; --i)
    {
        for (j = 0; j < player->c; j++) /* Controllo se tutta la riga è piena*/
            if (player->game[i * player->c + j] == PIECE_)
                ++isFull;
            else
                break;

        /* Se la riga è piena, viene rimossa */
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
    if(!flips) /*Non può invertire 0 righe, non ha senso... */
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
    printf("RAGA HO LE PALLE STORTE");
    *isPlaying = 0;
}

unsigned missingPieces(const Player_t player)
{
    int i, flag = 0;
    for(i = 0; i < 7; ++i)
        if(!player.pieces[i].qty)
            ++flag;
    return flag;
}
