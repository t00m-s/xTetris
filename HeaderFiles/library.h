#ifndef ALL_LIB
#define ALL_LIB
#include <stdio.h>
#include <stdlib.h>
#include "pieces.h"
#include "players.h"
#endif

int  typeRotation(char rotation);
void rotatePiece(Tetramino_t *tetramino, int type);
int  insertPiece(Player_t *player, Tetramino_t tetramino, unsigned column, char rotation);

int findFree(Player_t player, unsigned column, unsigned *freeRow, unsigned *freeCol, Tetramino_t tetramino)
{
    size_t i;
    int found = 0;
    for(i = 0; i < player.c; ++i)
    {
        /*Anche se la board ha già un pezzo potrei ignorarlo se il tetramino in quella posizione è vuoto*/
        if(player.game[i * player.c + column] == empty || tetramino.piece[0] == empty)
        {
            if(isLegalMove(player, i, column, tetramino)) /*Devo aumentare l'indice i*/
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
    unsigned freeRow, freeCol;
    int rotType = typeRotation(rotation);    /*Passo una copia così posso ruotarla a piacimento*/
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
