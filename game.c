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
    int a, b;
    size_t r, c;

    /*Pezzo di test*/
    Tetramino tetramino;
    tetramino.height = 3;
    tetramino.width = 2;
    tetramino.piece = (char*) malloc(tetramino.width * tetramino.height * sizeof(char));
    tetramino.piece[0] = 'O';
    tetramino.piece[1] = 'X';
    tetramino.piece[2] = 'X';
    tetramino.piece[3] = 'X';
    tetramino.piece[4] = 'O';
    tetramino.piece[5] = 'X';
    tetramino.qty = 3;

    do
    {
        printf("Dimensioni minime: 5x5\n");

        printf("Dimensione righe: ");
        scanf("%ld", &r);

        printf("Dimensione colonne: ");
        scanf("%ld", &c);

    }while(r < 5 && c < 5);

    gameP1 = (char*) malloc(r * c * sizeof(char));
    fillGame(gameP1, r, c, 'O');

    while(isPlaying)
    {
    /*Seleziona pezzo e rotazione*/


    /*Controlla legalità mossa e inserisce pezzo*/
        if(!insertPiece(gameP1, r, c, &tetramino, 0))/*Ho rimosso || per isFirstRowFull */
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
    free(tetramino.piece);
    return 0;
}
