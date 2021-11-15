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
    char *game;
    int r, c;
    do
    {
        printf("Dimensioni minime: 5x5\n");

        printf("Dimensione righe: ");
        scanf("%d", &r);

        printf("Dimensione colonne: ");
        scanf("%d", &c);
    }while(r < 5 && c < 5);

    game = (char*) malloc(r * c * sizeof(char));
    fillGame(game, r, c, 'O');

    printf("Scegli la modalità di gioco:");
    printf("\n1)Singleplayer\n2)Multiplayer Locale\n3)Multiplayer vs CPU\n");
    scanf("%d", &gameType);

    while(isPlaying)
    {
    /*Inserisci pezzo e controlla rotazione */


    /*Rimozione righe piene e aggiornamento board di gioco*/
        removeRows(game, r, c, &brLines);

        while(isLastRowEmpty(game, r, c))
            updateGame(game, r, c, &total, &brLines);
            
    /*Aggiornamento punteggio*/
        updateScore(&total, &brLines, &totalBrLines);

        printGame(game, r, c);
        printf("\n");

      if(isFirstRowFull(game, r, c))
            setGameOver(&isPlaying);

    }

    printf("Totale: %d\nRighe rimosse: %d\n", total, totalBrLines);
    free(game);
    return 0;
}
