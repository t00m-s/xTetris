#include </home/tom/Documents/Progetto/HeaderFiles/library.h>
/*
    TODO:
    -Scegliere tipologia (Singleplayer / multiplayer locale/ vs CPU)
    -Modificare il pezzo in base alla rotazione
    -CPU
*/

int main()
{
    Player_t player1, player2;
    int isPlaying = 1, total = 0, brLines = 0, isMultiplayer = 0;
    char rotation;
    size_t nrPiece = 0, column;
    int confirm;
    unsigned qty;
    size_t r, c;


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

    printf("Modalità di gioco: \n0)SinglePlayer\n1)Multiplayer\n");
    scanf("%d", &isMultiplayer);
    startGame(&player1, &player2, r, c, qty);
    printGame(player1, player2, r, c, isMultiplayer);
    while(isPlaying)
    {
        nextTurn(&player1, &player2);
    }
    endGame(player1, player2);
    return 0;
}
