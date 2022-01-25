#include "pieces.h"

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
            exit(EXIT_FAILURE);
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
            for(j = 0; j < tetramino[i].width; ++j)
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

Tetramino_t rotate90pos(Tetramino_t tetramino)
{
    size_t i, j, temp;
    char* aux = (char*) malloc(sizeof(char) * tetramino.width * tetramino.height);
    for(i = 0; i < tetramino.width * tetramino.height; ++i)
        aux[i] = EMPTY_;

    if(tetramino.type == 'I') /*Necessario solo lo swap di righe e colonne*/
    {
        temp = tetramino.width;
        tetramino.width = tetramino.height;
        tetramino.height = temp;
    }
    else
    {
        /*
         * Prima riga pezzo originale = ultima colonna pezzo ruotato etc
         * Parte da inizio riga
         * Sprecare un ora per l'indice di aux gg
        */
        for (i = 0; i < tetramino.height; ++i)
            for (j = 0; j < tetramino.width; ++j)
                aux[(j * tetramino.height) + i] = tetramino.piece[i * tetramino.width + j];


        /*Swap*/
        temp = tetramino.width;
        tetramino.width = tetramino.height;
        tetramino.height = temp;

        for (i = 0; i < tetramino.width * tetramino.height; ++i)
            tetramino.piece[i] = aux[i];
    }
    free(aux);
    return tetramino;
}

Tetramino_t rotate180(Tetramino_t tetramino)
{
    /*
     * Come funzionerà:
     * Inverto posizione righe:
     * Prima riga -> ultima
     * Seconda -> penultima
     * ..
     * poi invertire posizione delle celle nella riga
     * Prima ->ultima
     */
    char aux;
    size_t i, j;


}

Tetramino_t rotate90neg(Tetramino_t tetramino)
{
    int z;
    size_t i, j, temp;

    char* aux = (char*) malloc(sizeof(char) * tetramino.width * tetramino.height);
    for(i = 0; i < tetramino.width * tetramino.height; ++i)
        aux[i] = EMPTY_;

    if(tetramino.type == 'I') /*Necessario solo lo swap di righe e colonne*/
    {
        temp = tetramino.width;
        tetramino.width = tetramino.height;
        tetramino.height = temp;
    }
    else
    {
        /*
         * Prima riga originale = ultima colonna aux
         * Parte da fine riga
        */

        /*
         * Nel loop esterno devo switchare la colonna di aux partendo dall'ultima
         * Interno devo switchare la riga
         * Non vuole stampare correttamente (Mi sa stesso discorso del bug della rotation in input
         * ma funziona
         */
        for (i = 0; i < tetramino.height; ++i)
            for (j = 0, z = (int) tetramino.width - 1; j < tetramino.width && z >= 0; ++j, --z)
                aux[j * tetramino.height + i] = tetramino.piece[i * tetramino.width + z];

        /*Swap*/
        temp = tetramino.width;
        tetramino.width = tetramino.height;
        tetramino.height = temp;


        for (i = 0; i < tetramino.width * tetramino.height; ++i)
            tetramino.piece[i] = aux[i];
    }
    free(aux);
    return tetramino;
}

Tetramino_t rotatePiece(Tetramino_t tetramino, unsigned rot)
{
    /*Passo una copia, la modifico e la ritorno modificata
     * Casi di rotazione: +90°, -90°, 180°, 360° (non far nulla)
     */
    if(tetramino.type == 'O') /*Non serve ruotarlo*/
        return tetramino;

    switch(rot)
    {
        case 1:
            tetramino = rotate90pos(tetramino);
            break;
        case 2:
            tetramino = rotate180(tetramino);
            break;
        case 3:
            tetramino = rotate90neg(tetramino);
        default:
            break;
    }

    return tetramino;
}

unsigned typeRotation(char rotation)
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
    size_t i;
    for(i = 0; i < 7; ++i)
        free(tetraminio[i].piece);
}
