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
    int nrPiece = 0, qty;
    size_t r, c;

    /*SPERO NON SIA DEFINITIVA STA ROBA*/
    /*  Posizioni array codificate per ogni pezzo
     *  0 = I
     *  1 = J
     *  2 = L
     *  3 = O
     *  4 = S
     *  5 = T
     *  6 = Z
     * */
    Tetramino_t tetramino[7];
    do
    {
        printf("Con quanti pezzi vuoi giocare? \n");
        scanf("%d", &qty);
    }while(qty <= 0);
    generatePieces(tetramino, qty);

    do
    {
        printf("Dimensioni minime: 5x5\n");

        printf("Dimensione righe: ");
        scanf("%ld", &r);

        printf("Dimensione colonne: ");
        scanf("%ld", &c);

    }while(r < 5 && c < 5);

    gameP1 = (char*) malloc(r * c * sizeof(char));
    startGame(gameP1, r, c);

    while(isPlaying) {
        /*Seleziona pezzo e rotazione*/
        int confirm = 0;
        while (!confirm)
        {
            do
            {
                printf("Seleziona il pezzo: \n");
                scanf("%d", &nrPiece);
            } while (nrPiece < 0 || nrPiece >= 7);

            do /*Fa schifo? Forse. Funziona? In teoria*/
            {
                printf("Seleziona rotazione pezzo: \n");
                scanf("%c", &rotation);
                rotation -= 32; /*Converte in maiuscolo ASCII*/
            } while (rotation != 'W' || rotation != 'A' || rotation != 'S' || rotation != 'D');

            printf("Confermi la scelta? \n");
            scanf("%d", &confirm);
        }
    /*Controlla legalità mossa e inserisce pezzo*/
        if(!insertPiece(gameP1, r, c, &tetramino[nrPiece], 0))/*Ho rimosso || per isFirstRowFull */
            setGameOver(&isPlaying);
    /*Rimozione righe piene e aggiornamento board di gioco*/
        removeRows(gameP1, r, c, &brLines);

        updateGame(gameP1, r, c);
            
    /*Aggiornamento punteggio*/

        updateScore(&total, &brLines, &totalBrLines);

        printGame(gameP1, r, c);
        printf("\n");

      /*if(isFirstRowFull(gameP1, r, c))*/
            setGameOver(&isPlaying);

    }

    printf("Totale: %d\nRighe rimosse: %d\n", total, totalBrLines);
    free(gameP1);
    freeAllPieces(tetramino);
    return 0;
}
