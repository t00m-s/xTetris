#ifndef ALL_LIB
#define ALL_LIB
#include <stdio.h>
#include <stdlib.h>
#include "pieces.h"
#include "players.h"
#endif

void startGame(Player_t *p1, Player_t *p2, size_t r, size_t c, unsigned qty);
void endGame(Player_t p1, Player_t p2);
void printGame(Player_t p1, Player_t p2, size_t r, size_t c, int isMultiplayer);

int  findFree(Player_t player, unsigned column, unsigned *freeRow, unsigned *freeCol, Tetramino_t tetramino);
int  isLegalMove(Player_t player, unsigned freeRow, unsigned freeCol, Tetramino_t tetramino);
int  typeRotation(char rotation);
void rotatePiece(Tetramino_t *tetramino, int type);
int  insertPiece(Player_t *player, Tetramino_t tetramino, unsigned column, char rotation);

void removeRows(Player_t *player, unsigned *brLines);
void updateGame(Player_t *player);
void flipRows(Player_t *player, unsigned flips);
void updateScore(Player_t *player, unsigned *brLines);
void setGameOver(int *isPlaying);

int  isLastRowEmpty(Player_t player);


void startGame(Player_t *p1, Player_t *p2, size_t r, size_t c, unsigned qty)
{
    int i, j;
    p1->game = (char*) malloc(r * c * sizeof(char));
    p1->r = r;
    p1->c = c;
    p2->r = r;
    p2->c = c;
    p2->game = (char*) malloc(r * c * sizeof(char));
    for(i = 0; i < r; i++)
    {
        for (j = 0; j < c; j++)
        {
            p1->game[i * c + j] = empty;
            p2->game[i * c + j] = empty;
        }
    }
    generatePieces(p1->pieces, qty);
    generatePieces(p2->pieces, qty);
    p1->turn = 1; /*Comincia il giocatore 1*/
    p2->turn = 0;
}

void endGame(Player_t p1, Player_t p2)
{
    free(p1.game);
    free(p2.game);
    freeAllPieces(p1.pieces);
    freeAllPieces(p2.pieces);
}

void printGame(Player_t p1, Player_t p2, size_t r, size_t c, int isMultiplayer)
{
    int i, j;

    if(isMultiplayer)
    {
        for(i = 0; i < r; ++i)
        {
            for(j = 0; j < c; ++j)
                printf("%c ", p1.game[i * c + j]);

            printf("\t\t");

            for(j = 0; j < c; j++)
                printf("%c ", p2.game[i * c + j]);
            printf("\n");
        }
        for(j = 0; j < c; j++)
            printf("%d ", j);
        printf("\t\t");
        for(j = 0; j < c; ++j)
            printf("%d ", j);
        printf("\n");
        return;
    }

    for(i = 0; i < r; i++)
    {
        for(j = 0; j < c; j++) /* Stampa contenuto matrice di gioco */
            printf("%c ", p1.game[i * c + j]);

        printf("\n");
    }

    for(j = 0; j < c; j++) /* stampa indice colonne */
        printf("%d ", j);

    printf("\n");
}

int findFree(Player_t player, unsigned column, unsigned *freeRow, unsigned *freeCol, Tetramino_t tetramino)
{
    int i;
    int found = 0;
    for(i = 0; i < player.c; ++i)
    {
        /*Anche se la board ha già un pezzo potrei ignorarlo se il tetramino in quella posizione è vuoto*/
        if(player.game[i * player.c + column] == empty || tetramino.piece[0] == empty)
        {
            if(isLegalMove(player, *freeRow, *freeCol, tetramino)) /*Devo aumentare l'indice i*/
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

int isLegalMove(Player_t player, const unsigned freeRow, const unsigned freeCol, Tetramino_t tetramino)
{   /*Qui controlla se l'espansione è possibile*/
    size_t i = 0, j = 0;
    size_t tetH = 0, tetW = 0;
    /*Controllare limiti*/
    if(tetramino.width + freeCol > player.c || freeRow + tetramino.height  > player.r)
        return 0;

    for(i = freeRow, tetH = 0; i < (freeRow + tetramino.height) && tetH < tetramino.height; ++i, ++tetH) /*Scorro i due indici contemporaneamente*/
        for(j = freeCol, tetW = 0; j < (freeCol + tetramino.width) && tetW < tetramino.width; ++j, ++tetW)
            if(player.game[i * player.c + j] == piece && tetramino.piece[tetH * tetramino.height + tetW] == piece) /*Controlla collisioni*/
                return 0;

    return 1;
}

int typeRotation(char rotation)
{
    switch(rotation)
    {
        case 'A':
            return 3;
        case 'S':
            return 2;
        case 'D':
            return 1;
        default:
            return 0;
    }
}

void rotatePiece(Tetramino_t *tetramino, int type)
{/*
    char* newPiece = (char*) malloc(tetramino->width * tetramino->height * sizeof(char));
    int i, j;
    size_t temp;
    for(i = 0; i < tetramino->height; ++i)
        for(j = 0; j < tetramino->width; ++j)
            newPiece[i * tetramino->width + j] = tetramino->piece[];

    free(tetramino->piece);

    temp = tetramino->width;
    tetramino->width = tetramino->height;
    tetramino->height = temp;

    tetramino->piece = newPiece;
*/
}

int insertPiece(Player_t *player, Tetramino_t tetramino, unsigned column, char rotation) /*Da inserire la rotazione*/
{
    size_t i, j, tetW, tetH;
    //unsigned freeRow, freeCol; /*Questa cosa mi causa problemi adesso*/
    /*Passo una copia così posso ruotarla a piacimento*/
    int rotType = typeRotation(rotation);
    rotatePiece(&tetramino, rotType);

    if(findFree(*player, column, &freeRow, &freeCol, tetramino) && isLegalMove(*player, freeRow, freeCol, tetramino))
    {
        for(i = freeRow, tetH = 0; i < (freeRow + tetramino.height) && tetH < tetramino.height; ++i, ++tetH)    /*Scorro i due indici contemporaneamente*/
            for(j = freeCol, tetW = 0; j < (freeCol + tetramino.width) && tetW < tetramino.width; ++j, ++tetW)  /*Controlla collisioni*/
                if(tetramino.piece[tetH * tetramino.width + tetW] == piece)
                    player->game[i * player->c + j] = tetramino.piece[tetH * tetramino.width + tetW];


        return 1;
    }
    return 0;
}

void removeRows(Player_t *player, unsigned *brLines)
{
    int i, j, isFull = 0;

    for(i = (int)player->r - 1; i >= 0; --i)
    {
        for (j = 0; j < player->c; j++) /* Controllo se tutta la riga è piena*/
            if (player->game[i * player->c + j] == piece)
                ++isFull;
            else
                break;

        /* Se la riga è piena, viene rimossa.
         * Ripetuto per tutte le possibili righe (ottimizzare appena trova una riga vuota esce)
        */
        if (isFull == player->c)
        {
            for (j = 0; j < player->c; ++j)
                player->game[i * player->c + j] = empty;
            ++(*brLines);
        }
        isFull = 0;
    }
}

void updateGame(Player_t *player)
{
    int i, j;
    while(isLastRowEmpty(*player))
    {
        for (i = (int) player->r - 1; i > 0; --i)
            for (j = 0; j < player->c; ++j)
                player->game[i * player->c + j] = player->game[(i - 1) * player->c + j];
    }
}

void flipRows(Player_t *player, unsigned int flips) /*Non l'ho ancora testata ma dovrebbe andare*/
{
    int i, j;
    if(!flips) /*Non può invertire 0 righe, non ha senso... */
        return;

    for(i = (int) player->r - 1; i >= player->r - 1 - flips; --i)
        for(j = 0; j < player->c; ++j)
            if(player->game[i * player->c + j] == piece)
                player->game[i * player->c + j] = empty;
            else
                player->game[i * player->c + j] = piece;
}

int isLastRowEmpty(Player_t player)
{
    int j, isEmpty = 0;

    for (j = 0; j < player.c; ++j)
        if (player.game[(player.r - 1) * player.c + j] == empty)
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

