#include "pieces.h"

void generatePieces(Tetramino_t collection[7], unsigned qty)
{
    size_t i;
    /*Pezzo I*/
    collection[0].width = 4;
    collection[0].height = 1;

    /*Pezzo J*/
    collection[1].width = 3;
    collection[1].height = 2;

    /*Pezzo L*/
    collection[2].width = 3;
    collection[2].height = 2;

    /*Pezzo O*/
    collection[3].width = 2;
    collection[3].height = 2;

    /*Pezzo S*/
    collection[4].width = 3;
    collection[4].height = 2;

    /*Pezzo T*/
    collection[5].width = 3;
    collection[5].height = 2;

    /*Pezzo Z*/
    collection[6].width = 3;
    collection[6].height = 2;

    /*Cose in comune*/
    for (i = 0; i < 7; ++i)
    {
        collection[i].qty = qty;
        collection[i].piece = (char*) malloc(collection[i].width * collection[i].height * sizeof(char));
        if (!collection[i].piece )
        {
            printf("Non è stato possibile allocare memoria.\n");
            exit(EXIT_FAILURE);
        }
    }

    /* Pezzi base hardcoded */
    /* PEZZO I*/
    collection[0].type = 'I';
    collection[0].piece[0] = PIECE_;
    collection[0].piece[1] = PIECE_;
    collection[0].piece[2] = PIECE_;
    collection[0].piece[3] = PIECE_;

    /*PEZZO J*/
    collection[1].type = 'J';
    collection[1].piece[0] = PIECE_;
    collection[1].piece[1] = EMPTY_;
    collection[1].piece[2] = EMPTY_;
    collection[1].piece[3] = PIECE_;
    collection[1].piece[4] = PIECE_;
    collection[1].piece[5] = PIECE_;

    /*PEZZO L*/
    collection[2].type = 'L';
    collection[2].piece[0] = EMPTY_;
    collection[2].piece[1] = EMPTY_;
    collection[2].piece[2] = PIECE_;
    collection[2].piece[3] = PIECE_;
    collection[2].piece[4] = PIECE_;
    collection[2].piece[5] = PIECE_;

    /*PEZZO O*/
    collection[3].type = 'O';
    collection[3].piece[0] = PIECE_;
    collection[3].piece[1] = PIECE_;
    collection[3].piece[2] = PIECE_;
    collection[3].piece[3] = PIECE_;

    /*PEZZO S*/
    collection[4].type = 'S';
    collection[4].piece[0] = EMPTY_;
    collection[4].piece[1] = PIECE_;
    collection[4].piece[2] = PIECE_;
    collection[4].piece[3] = PIECE_;
    collection[4].piece[4] = PIECE_;
    collection[4].piece[5] = EMPTY_;

    /*PEZZO T*/
    collection[5].type = 'T';
    collection[5].piece[0] = EMPTY_;
    collection[5].piece[1] = PIECE_;
    collection[5].piece[2] = EMPTY_;
    collection[5].piece[3] = PIECE_;
    collection[5].piece[4] = PIECE_;
    collection[5].piece[5] = PIECE_;

    /*PEZZO Z*/
    collection[6].type = 'Z';
    collection[6].piece[0] = PIECE_;
    collection[6].piece[1] = PIECE_;
    collection[6].piece[2] = EMPTY_;
    collection[6].piece[3] = EMPTY_;
    collection[6].piece[4] = PIECE_;
    collection[6].piece[5] = PIECE_;
}

/*  Posizioni array codificate per ogni pezzo
 *  0 = I
 *  1 = J
 *  2 = L
 *  3 = O
 *  4 = S
 *  5 = T
 *  6 = Z
*/
void printPieceHint(const Tetramino_t collection[7])
{
    size_t i;
    for (i = 0; i < 7; ++i)
        if(collection[i].qty)
            printf("Pezzo: %c \t Quantità: %d \t Indice: %lu  \n", collection[i].type, collection[i].qty, i);

}

/**
 * @brief Ruota di +90 gradi un tetraminoo.
 * @param tetramino Tetramino da ruotare
 * @return Copia del tetramino ruotata di 90 gradi.
 */
Tetramino_t rotate90pos(Tetramino_t tetramino)
{
    size_t i, j, temp;
    int k;
    char *aux = (char*) malloc(sizeof(char) * tetramino.width * tetramino.height);
    if(!aux)
    {
        printf("\nErrore durante la rotazione del pezzo.");
        exit(EXIT_FAILURE);
    }
    
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
         * Ultima riga pezzo originale = prima colonna pezzo ruotato etc
         * Parte da inizio riga
         * Sprecare un ora per l'indice di aux gg
        */
        for (i = 0, k = (int)tetramino.height - 1; i < tetramino.height && k >= 0; ++i, --k)
            for (j = 0; j < tetramino.width; ++j)
                aux[j * tetramino.height + i] = tetramino.piece[k * tetramino.width + j];

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

/**
 * @brief Ruota di 180 gradi un tetramino.
 * @param tetramino Tetramino da ruotare.
 * @return Copia del tetramino ruotata di 180 gradi.
 */
Tetramino_t rotate180(Tetramino_t tetramino)
{
    /*
     * Inverto posizione righe:
     * Prima riga -> ultima
     * Seconda -> penultima
     * ..
     * poi invertire posizione delle celle nella riga
     * Prima -> ultima
     */
    char* aux = (char*) malloc(tetramino.width * tetramino.height * sizeof(char));
    size_t i, j;
    int k;
    char aux_;
    if(!aux)
    {
        printf("\nErrore durante la rotazione del pezzo.");
        exit(EXIT_FAILURE);
    }

    /*Swap delle righe*/
    for(i = 0, k = tetramino.height - 1; i < tetramino.height && k >= 0; ++i, --k)
        for (j = 0; j < tetramino.width; ++j)
            aux[i * tetramino.width + j] = tetramino.piece[k * tetramino.width + j];

    /*Inversione per ogni riga*/
    for(i = 0; i < tetramino.height; ++i)
    {
        for (j = 0, k = tetramino.width - 1; j < tetramino.width / 2 && k > tetramino.width / 2; ++j, --k)
        {
            aux_ = aux[i * tetramino.width + j];
            aux[i * tetramino.width + j] = aux[i * tetramino.width + k];
            aux[i * tetramino.width + k] = aux_;
        }
    }

    for(i = 0; i < tetramino.width * tetramino.height; ++i)
        tetramino.piece[i] = aux[i];

    free(aux);
    return tetramino;
}

/**
 * @brief Ruota di -90 gradi un tetramino.
 * @param tetramino Tetramino da ruotare.
 * @return Copia del tetramino ruotata.
 */
Tetramino_t rotate90neg(Tetramino_t tetramino)
{
    int z;
    size_t i, j, temp;

    char* aux = (char*) malloc(sizeof(char) * tetramino.width * tetramino.height);
    if(!aux)
    {
        printf("\nErrore durante la rotazione del pezzo.");
        exit(EXIT_FAILURE);
    }
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

Tetramino_t rotatePiece(Tetramino_t tetramino, char rotation)
{
    /*
     * Passo una copia, la modifico e la ritorno modificata
     * Casi di rotazione: +90°, -90°, 180°, 360° (non far nulla)
    */

    if(tetramino.type == 'O') /*Non serve ruotarlo*/
        return tetramino;

    switch((char)toupper((unsigned char)(rotation))) /* Sparava warning se non castavo a unsigned char */
    {
        case 'D':
            tetramino = rotate90pos(tetramino);
            break;
        case 'S':
            tetramino = rotate180(tetramino);
            break;
        case 'A':
            tetramino = rotate90neg(tetramino);
            break;
        default: /* 'W' */
            break;
    }

    return tetramino;
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
