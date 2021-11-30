/* Genero un pezzo per testare */
typedef struct tetramino{
    int width;
    int height;
    int qty;
    char* piece;
    char* rotatedPiece;
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
        tetramino[i].piece = (char*) malloc(tetramino[i].width * tetramino[i].height * sizeof(char));
        tetramino[i].rotatedPiece = (char*) malloc(tetramino[i].width * tetramino[i].height * sizeof(char));
    }
}

void generateRotated(Tetramino_t *tetramino, char rotation)
{

}

void freeAllPieces(Tetramino_t *tetraminio)
{
    int i;
    for(i = 0; i < 7; ++i)
    {
        free(tetraminio[i].piece);
        free(tetraminio[i].rotatedPiece);
    }
}
