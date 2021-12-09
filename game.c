#include </home/tom/Documents/Progetto/library.h>
/*
    TODO:
    -Scegliere tipologia (Singleplayer / multiplayer locale/ vs CPU)
    -Modificare il pezzo in base alla rotazione
    -CPU
*/

int main()
{
    Player_t player1;
    Player_t player2;
    int isPlaying = 1, total = 0, brLines = 0;
    char rotation;
    size_t nrPiece = 0, column;
    int confirm;
    size_t r, c;

    /*  Posizioni array codificate per ogni pezzo SPERO NON DEFINITIVA COSì, magari ci faccio un enum?
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

    player1.game = (char*) malloc(r * c * sizeof(char));

    startGame(player1.game, r, c);
    generatePieces(player1.pieces, qty);

    while(isPlaying)
    {
        break;
    }
    free(player1.game);
    freeAllPieces(player1.pieces);
    return 0;
}

