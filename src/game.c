#include "library.h"
/*
    TODO:
    -Scegliere tipologia (Singleplayer / multiplayer locale/ vs CPU)
    -Modificare il pezzo in base alla rotazione
    -CPU
*/

int main()
{
    Player_t player1, player2;
    int isPlaying = 1, isMultiplayer = 0, confirm = 0, p2CPU = 0;
    unsigned brLines = 0, qty = 0, column = 0;
    char rotation;
    size_t nrPiece = 0;
    size_t r, c;

    if(empty == piece) /*Warning perchè li vede come valori già assegnati diversi*/
    {
        printf("ERRORE: I PEZZI EMPTY NON POSSONO ESSERE UGUALI A QUELLI INTERI");
        EXIT_FAILURE;
    }

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
    if(isMultiplayer)
    {
        printf("0)Player2\n1)CPU");
        scanf("%d", &p2CPU);
    }
    startGame(&player1, &player2, r, c, qty);
    printGame(player1, player2, isMultiplayer);

    while(isPlaying)
    {
        if(missingPieces(player1) == 7 || missingPieces(player2) == 7)
            break;

        printf("Turno giocatore %d.\nScegli colonna dove inserire il pezzo:\n", player1.turn ? 1 : 2);
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
                decreaseQty(&player1.pieces[nrPiece]);
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
                decreaseQty(&player2.pieces[nrPiece]);
                removeRows(&player2, &brLines);
                updateGame(&player2);
                flipRows(&player1, brLines);
                updateScore(&player2, &brLines);
            }
        }
        printGame(player1, player2, isMultiplayer);
        if(isMultiplayer)   nextTurn(&player1, &player2);
    }
    endGame(player1, player2, isMultiplayer);
    return 0;
}
