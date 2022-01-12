#include "pieces.h"
#include <stdlib.h>
#include <stdio.h>

/*  Posizioni array codificate per ogni pezzo
 *  0 = I
 *  1 = J
 *  2 = L
 *  3 = O
 *  4 = S
 *  5 = T
 *  6 = Z
*/

void generatePieces(Tetramino_t *tetramino, unsigned qty)
{
    int i;
    /*Pezzo I*/
    tetramino[0].width = 4;
    tetramino[0].height = 1;

    /*Pezzo J*/
    tetramino[1].width = 3;
    tetramino[1].height = 2;
    /*Pezzo L*/
    tetramino[2].width = 3;
    tetramino[2].height = 2;
    /*Pezzo O*/
    tetramino[3].width = 2;
    tetramino[3].height = 2;
    /*Pezzo S*/
    tetramino[4].width = 3;
    tetramino[4].height = 2;
    /*Pezzo T*/
    tetramino[5].width = 3;
    tetramino[5].height = 2;
    /*Pezzo Z*/
    tetramino[6].width = 3;
    tetramino[6].height = 2;

    /*Cose in comune*/
    for (i = 0; i < 7; ++i)
    {
        tetramino[i].qty = qty;
        tetramino[i].piece = (char *) malloc(tetramino[i].width * tetramino[i].height * sizeof(char));
        if (!tetramino[i].piece)
        {
            printf("Non è stato possibile allocare memoria per i pezzi di gioco.\n");
            EXIT_FAILURE;
        }
    }

    /* Pezzi base hardcoded*/
    /* PEZZO I*/
    tetramino[0].type = 'I';
    tetramino[0].piece[0] = PIECE_;
    tetramino[0].piece[1] = PIECE_;
    tetramino[0].piece[2] = PIECE_;
    tetramino[0].piece[3] = PIECE_;

    /*PEZZO J*/
    tetramino[1].type = 'J';
    tetramino[1].piece[0] = PIECE_;
    tetramino[1].piece[1] = EMPTY_;
    tetramino[1].piece[2] = EMPTY_;
    tetramino[1].piece[3] = PIECE_;
    tetramino[1].piece[4] = PIECE_;
    tetramino[1].piece[5] = PIECE_;

    /*PEZZO L*/
    tetramino[2].type = 'L';
    tetramino[2].piece[0] = EMPTY_;
    tetramino[2].piece[1] = EMPTY_;
    tetramino[2].piece[2] = PIECE_;
    tetramino[2].piece[3] = PIECE_;
    tetramino[2].piece[4] = PIECE_;
    tetramino[2].piece[5] = PIECE_;

    /*PEZZO O*/
    tetramino[3].type = 'O';
    tetramino[3].piece[0] = PIECE_;
    tetramino[3].piece[1] = PIECE_;
    tetramino[3].piece[2] = PIECE_;
    tetramino[3].piece[3] = PIECE_;

    /*PEZZO S*/
    tetramino[4].type = 'S';
    tetramino[4].piece[0] = EMPTY_;
    tetramino[4].piece[1] = PIECE_;
    tetramino[4].piece[2] = PIECE_;
    tetramino[4].piece[3] = PIECE_;
    tetramino[4].piece[4] = PIECE_;
    tetramino[4].piece[5] = EMPTY_;

    /*PEZZO T*/
    tetramino[5].type = 'T';
    tetramino[5].piece[0] = EMPTY_;
    tetramino[5].piece[1] = PIECE_;
    tetramino[5].piece[2] = EMPTY_;
    tetramino[5].piece[3] = PIECE_;
    tetramino[5].piece[4] = PIECE_;
    tetramino[5].piece[5] = PIECE_;

    /*PEZZO Z*/
    tetramino[6].type = 'Z';
    tetramino[6].piece[0] = PIECE_;
    tetramino[6].piece[1] = PIECE_;
    tetramino[6].piece[2] = EMPTY_;
    tetramino[6].piece[3] = EMPTY_;
    tetramino[6].piece[4] = PIECE_;
    tetramino[6].piece[5] = PIECE_;
}

void printPieceStats(const Tetramino_t *tetramino)
{
    int i, j, k;
    for(i = 0; i < 7; ++i)
    {
        printf("Pezzo: %c, Quantità: %d   \n",tetramino[i].type, tetramino[i].qty);
        /*for(k = 0; k < tetramino[i].height; ++k)
        {
            for (j = 0; j < tetramino[i].width; ++j)
                printf("%c", tetramino[i].piece[k * tetramino[i].width + j]);
            printf("\n");
        }
        printf("\n");*/
    }
}

unsigned piecesLeft(const Tetramino_t tetramino) /*Nome insomma, controlla se ho ancora pezzi disponibili di quel tipo*/
{
    return tetramino.qty;
}

void rotate90DegPiece(Tetramino_t *tetramino)
{
/*
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

void decreaseQty(Tetramino_t *tetramino)
{
    --tetramino->qty;
}

void freeAllPieces(Tetramino_t *tetraminio)
{
    int i;
    for(i = 0; i < 7; ++i)
        free(tetraminio[i].piece);
}
