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
    int i;
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

    do
    {
        printf("Dimensioni minime: 5x5\n");

        printf("Dimensione righe: ");
        scanf("%ld", &r);

        printf("Dimensione colonne: ");
        scanf("%ld", &c);

        /*Resetto la lunghezza*/
        if(r >= 5 && c >= 5)
            break;
    }while(1);

    gameP1 = (char*) malloc(r * c * sizeof(char));
    startGame(gameP1, r, c);
    generatePieces(tetramino, qty);
    printPieceStats(tetramino);

    printf("Totale: %d\nRighe rimosse: %d\n", total, totalBrLines);
    free(gameP1);
    freeAllPieces(tetramino);
    return 0;
}
