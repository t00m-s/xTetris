#include <stdio.h>
#include "players.h"
#include "pieces.h"
#include "cpu.h"


int main()
{
    Player_t player1, player2;
    int isPlaying = 1, isMultiplayer = 0, confirm = 0, cpu;
    unsigned int brLines = 0, qty = 0, column = 0;
    char rotation;
    size_t r, c, nrPiece = 0;

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
    }while((r < 5 && c < 5) || !confirm );

    printf("Modalità di gioco: \n0)SinglePlayer\n1)Multiplayer\n");
    scanf("%d", &isMultiplayer);
/*
    if(isMultiplayer)
    {
        printf("0)Player2\n1)CPU");
        scanf("%d", &cpu);
    }
*/
    startGame(&player1, &player2, r, c, qty);
    printGame(player1, player2, isMultiplayer);
    printf("\n");
    while(isPlaying)
    {
        if(missingPieces(player1) == 7 || missingPieces(player2) == 7)
            break;

        printf("Turno giocatore %d.\nPezzi disponibili:\n", player1.turn ? 1 : 2);
        printPieceHint(player1.turn ? player1.pieces : player2.pieces);
        printf("Scegli colonna dove inserire il pezzo: \n");
        scanf("%d", &column);


        printf("Scegli il pezzo:\n");
        scanf("%ld", &nrPiece);

        printf("Scegli rotazione:\n");

        /*
         * Cose strane di C?
         * Prende il valore solo se metti uno spazio prima di %c
         * Capito: A quanto pare legge in input uno spazio se non metti lo spazio
         * prima di %c
         */
        scanf(" %c", &rotation);

        if(player1.turn)
        {

            if(!(insertPiece(&player1, nrPiece, column, rotation) && piecesLeft(player1.pieces[nrPiece])))
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
            if(!(insertPiece(&player2, nrPiece, column, rotation) && piecesLeft(player2.pieces[nrPiece])))
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

        if(isMultiplayer)
            nextTurn(&player1, &player2);

    }
    endGame(&player1, &player2, isMultiplayer);
    return 0;
}
