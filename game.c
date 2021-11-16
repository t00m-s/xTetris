#include </home/kh3ro/Documents/Progetto/library.h>
/* 
    TODO:
    -Scegliere tipologia (Singleplayer / multiplayer locale/ vs CPU)
    -Input mossa
    -Input rotazione
    -Controllo rotazione
    -Posizione pezzo
    -CPU
*/

int main()
{
    int isPlaying = 1, confirm = 0, total = 0, brLines = 0, totalBrLines = 0;
    int gameType = 0;
    char *gameP1;
    int r, c;
    do
    {
        printf("Dimensioni minime: 5x5\n");

        printf("Dimensione righe: ");
        scanf("%d", &r);

        printf("Dimensione colonne: ");
        scanf("%d", &c);
    }while(r < 5 && c < 5);

    gameP1 = (char*) malloc(r * c * sizeof(char));
    fillGame(gameP1, r, c, 'O');

    printf("Scegli la modalità di gioco:");
    printf("\n1)Singleplayer\n2)Multiplayer Locale\n3)Multiplayer vs CPU\n");
    scanf("%d", &gameType);

    while(isPlaying)
    {
    /*Inserisci pezzo e controlla rotazione */


    /*Rimozione righe piene e aggiornamento board di gioco*/
        removeRows(gameP1, r, c, &brLines);

        while(isLastRowEmpty(gameP1, r, c))
            updateGame(gameP1, r, c, &total, &brLines);
            
    /*Aggiornamento punteggio*/
        updateScore(&total, &brLines, &totalBrLines);

        printGame(gameP1, r, c);
        printf("\n");

      /*if(isFirstRowFull(gameP1, r, c))*/
            setGameOver(&isPlaying);

    }

    printf("Totale: %d\nRighe rimosse: %d\n", total, totalBrLines);
    free(gameP1);
    return 0;
}
