#include </home/tom/Documents/Progetto/library.h>
/* 
    TODO:
    -Scegliere tipologia (Singleplayer / multiplayer locale/ vs CPU)
    -Implementare tutti i pezzi
    -Modificare il pezzo in base alla rotazione
    -CPU
*/

int main()
{
    int isPlaying = 1, total = 0, brLines = 0, totalBrLines = 0;
    char *gameP1;
    char rotation;
    int nrPiece = 0, qty, column, confirm;
    size_t r, c;
    Tetramino_t tetramino[7];
    /*  Posizioni array codificate per ogni pezzo SPERO NON DEFINITIVA COSì
     *  0 = I
     *  1 = J
     *  2 = L
     *  3 = O
     *  4 = S
     *  5 = T
     *  6 = Z
    */
    do
    {
        printf("Con quanti pezzi vuoi giocare? \n");
        scanf("%d", &qty);
    }while(qty <= 0);

    do
    {
        printf("Dimensioni minime: 5x5\n");

        printf("Dimensione righe: ");
        scanf("%ld", &r);

        printf("Dimensione colonne: ");
        scanf("%ld", &c);
        if(r >= 5 && c >= 5)
            break;
    }while(1);

    gameP1 = (char*) malloc(r * c * sizeof(char));
    startGame(gameP1, r, c);
    generatePieces(tetramino, qty);
    while(isPlaying)
    {
        /*Seleziona pezzo e rotazione*/
        while(1)
        {
            /*printPieceStats(tetramino);*/
            do
            {
                printf("Seleziona il pezzo: \n");
                scanf("%d", &nrPiece);
            } while (nrPiece < 0 || nrPiece >= 7);

            printf("Seleziona colonna: \n");
            scanf("%d", &column);

            printf("Confermi la scelta? \n");
            scanf("%d", &confirm);

            if(confirm)
                break;
        }
        /*Controlla legalità mossa e inserisce pezzo*/
        if(!(insertPiece(gameP1, r, c, tetramino[nrPiece], column) && piecesLeft(tetramino[nrPiece])))
            setGameOver(&isPlaying);

        /*Rimozione righe piene e aggiornamento board di gioco*/
        removeRows(gameP1, r, c, &brLines);
        updateGame(gameP1, r, c);

        /*Aggiornamento punteggio*/
        updateScore(&total, &brLines, &totalBrLines);

        printGame(gameP1, r, c);
        printf("\n");

        if(isFirstRowFull(gameP1, c))
            setGameOver(&isPlaying);

    }
    printf("Totale: %d\nRighe rimosse: %d\n", total, totalBrLines);
    free(gameP1);
    freeAllPieces(tetramino);
    return 0;
}

