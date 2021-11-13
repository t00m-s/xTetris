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
    int n_I = 20, n_J = 20, n_L = 20, n_O = 20, n_S = 20, n_T = 20, n_Z = 20; /* Counter pezzi Player1 */
    char rotation;
    char *game;
    int r, c;
    do
    {
        printf("Dimensione righe: ");
        scanf("%d", &r);

        printf("Dimensione colonne: ");
        scanf("%d", &c);
    }while(r < 5 && c < 5);
    game = (char*) malloc(r * c * sizeof(char));

    fillGame(game, r, c, 'O');
    fillRandom(game, r, c, 'X', 0, 2);
    fillRow(game, r, c, 'X', 3);
    fillRow(game, r, c, 'X', 4);
    fillRow(game, r, c, 'X', 5); /*Ho perso il contenuto dell'ultima riga alla fine wtf */

    printGame(game, r, c);

    while(isPlaying)
    {/*
        while(!confirm)
        {
            printf("Seleziona pezzo tra i disponibili: \n");
            printf("1|%d tetremini I\n2|%d tetramini J\n3|%d tetramini L\n4|%d tetramini O\n5|%d tetramini S\n6|%d tetramini T\n7|%d tetramini Z\n", n_I, n_J, n_L, n_O, n_S, n_T, n_Z);
            
            printf("Scegli rotazione: \n");
            scanf("%c", &rotation);

            printf("Confermi? (0 per annullare, 1 per confermare)");
            scanf("%d", &confirm);
        }*/

    /* Viene perso il contenuto dell'ultima riga */
        removeRows(game, r, c, &brLines);

        if(!isLastRowFull(game, r, c))
            updateGame(game, r, c, &total, &brLines);

        updateScore(&total, &brLines, &totalBrLines);

        printGame(game, r, c);

        /*if(isFirstRowFull(game, r, c))*/
            setGameOver(&isPlaying);

    }

    printf("Totale: %d\nRighe rimosse: %d\n", total, totalBrLines);
    printGame(game, r, c);
    free(game);
    return 0;
}
