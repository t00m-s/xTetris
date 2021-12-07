const char empty = '-';
const char piece = 'X';

/* Genero un pezzo per testare */
typedef struct tetramino{
    int width;
    int height;
    int qty;
    char type;
    char* piece;
} Tetramino_t;


/*Mi rifiuto di generare una roba del genere sul main*/

void generatePieces(Tetramino_t *tetramino, int qty)
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
            printf("Non è stato possibile allocare memoria.\n");
            EXIT_FAILURE;
        }
    }

    /* Ora comincia lo schifo, genero i pezzi base*/
    /* PEZZO I*/
    tetramino[0].type = 'I';
    tetramino[0].piece[0] = piece;
    tetramino[0].piece[1] = piece;
    tetramino[0].piece[2] = piece;
    tetramino[0].piece[3] = piece;

    /*PEZZO J*/
    tetramino[1].type = 'J';
    tetramino[1].piece[0] = piece;
    tetramino[1].piece[1] = empty;
    tetramino[1].piece[2] = empty;
    tetramino[1].piece[3] = piece;
    tetramino[1].piece[4] = piece;
    tetramino[1].piece[5] = piece;

    /*PEZZO L*/
    tetramino[2].type = 'L';
    tetramino[2].piece[0] = empty;
    tetramino[2].piece[1] = empty;
    tetramino[2].piece[2] = piece;
    tetramino[2].piece[3] = piece;
    tetramino[2].piece[4] = piece;
    tetramino[2].piece[5] = piece;

    /*PEZZO O*/
    tetramino[3].type = 'O';
    tetramino[3].piece[0] = piece;
    tetramino[3].piece[1] = piece;
    tetramino[3].piece[2] = piece;
    tetramino[3].piece[3] = piece;

    /*PEZZO S*/
    tetramino[4].type = 'S';
    tetramino[4].piece[0] = empty;
    tetramino[4].piece[1] = piece;
    tetramino[4].piece[2] = piece;
    tetramino[4].piece[3] = piece;
    tetramino[4].piece[4] = piece;
    tetramino[4].piece[5] = empty;

    /*PEZZO T*/
    tetramino[5].type = 'T';
    tetramino[5].piece[0] = empty;
    tetramino[5].piece[1] = piece;
    tetramino[5].piece[2] = empty;
    tetramino[5].piece[3] = piece;
    tetramino[5].piece[4] = piece;
    tetramino[5].piece[5] = piece;

    /*PEZZO Z*/
    tetramino[6].type = 'Z';
    tetramino[6].piece[0] = piece;
    tetramino[6].piece[1] = piece;
    tetramino[6].piece[2] = empty;
    tetramino[6].piece[3] = empty;
    tetramino[6].piece[4] = piece;
    tetramino[6].piece[5] = piece;
}

void printPieceStats (Tetramino_t *tetramino)
{
    int i, j, k;
    for(i = 0; i < 7; ++i)
    {
        printf("Pezzo: %c, Quantità: %d   \n",tetramino[i].type, tetramino[i].qty);
        for(k = 0; k < tetramino[i].height; ++k)
        {
            for (j = 0; j < tetramino[i].width; ++j)
                printf("%c", tetramino[i].piece[k * tetramino[i].width + j]);
            printf("\n");
        }
        printf("\n");
    }
}

int piecesLeft(const Tetramino_t tetramino) /*Nome insomma, controlla se ho ancora pezzi disponibili di quel tipo*/
{
    int i, flag;
    for(i = 0; i < 7; ++i)
        if(!tetramino.qty)
            flag = 0;
        else
            return 1;

    return flag;
}
void generateRotated(Tetramino_t tetramino, char rotation)
{

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
