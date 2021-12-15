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
    int isPlaying = 1, isMultiplayer = 0, confirm = 0;
    unsigned brLines = 0, qty = 0, column = 0;
    char rotation = 'W';
    size_t nrPiece = 0;
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

        printf("Confermi?\n");
        scanf("%d", &confirm);
    }while(!confirm);

    printf("Modalità di gioco: \n0)SinglePlayer\n1)Multiplayer\n");
    scanf("%d", &isMultiplayer);
    startGame(&player1, &player2, r, c, qty);
    while(isPlaying)
    {
        printf("Turno giocatore %d\nScegli colonna dove inserire il pezzo:\n", player1.turn ? 1 : 2);
        scanf("%d", &column);

        printf("Scegli il pezzo:\n");
        scanf("%ld", &nrPiece);

        printf("Scegli rotazione:\n");
        scanf("%c", &rotation);
        if(player1.turn)
        {
            if(!(insertPiece(&player1, player1.pieces[nrPiece], column, rotation) && piecesLeft(player1.pieces[nrPiece])))
                setGameOver(&isPlaying);
            else
            {
                removeRows(&player1, &brLines);
                updateGame(&player1);
                if (isMultiplayer) flipRows(&player2, brLines);
                updateScore(&player1, &brLines);
            }
        }
        else
        {
            if(!(insertPiece(&player2, player2.pieces[nrPiece], column, rotation) && piecesLeft(player2.pieces[nrPiece])))
                setGameOver(&isPlaying);
            else
            {
                removeRows(&player2, &brLines);
                updateGame(&player2);
                flipRows(&player1, brLines);
                updateScore(&player2, &brLines);
            }
        }
        printGame(player1, player2, r, c, isMultiplayer);
        if(isMultiplayer)   nextTurn(&player1, &player2);
    }
    endGame(player1, player2);
    return 0;
}
