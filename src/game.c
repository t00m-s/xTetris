#include <stdio.h>
#include "players.h"
#include "pieces.h"
#include "cpu.h"

/* Se inserisco un pezzo in  */

int main()
{
    Player_t player1, player2;
    int isPlaying = 1, isMultiplayer = 0, cpu = 0;
    unsigned int column = 0;
    char rotation;
    size_t nrPiece = 0;
    /*setbuf(stdout, 0); Usare solo CON DEBUG */
    startGame(&player1, &player2);
    /* Selezione modalità */
    puts("Scegli modalità di gioco:");
    puts("0) Single-player");
    puts("1) Multiplayer");
    scanf("%d", &isMultiplayer);
    if (isMultiplayer) {
        puts("0) Player1 vs Player2");
        puts("1) Player1 vs CPU");
        scanf("%d", &cpu);
    }


    /* Loop di gioco */
    while (isPlaying)
    {
        printGame(&player1, &player2, isMultiplayer);
        printf("Turno giocatore %d:\n", player1.turn ? 1 : 2);
        printPieceHint(player1.turn ? player1.pieces : player2.pieces);
        if (isMultiplayer)
        {
            if (cpu && player2.turn)
            {
            }
            else
            {
                int valid;
                unsigned int prev = player1.turn ? player1.totalBrLines : player2.totalBrLines;
                puts("Tetramino da inserire:");
                scanf("%lu", &nrPiece);

                puts("Rotazione tetramino:");
                scanf(" %c", &rotation);

                puts("Colonna dove inserire il tetramino:");
                scanf("%u", &column);

                valid = insertPiece(player1.turn ? &player1 : &player2,
                                    nrPiece, column, rotation);
                if(!valid)
                    setGameOver(&isPlaying);
                else
                {
                    removeRows(player1.turn ? &player1 : &player2,

                           player1.turn ? &player1.totalBrLines : &player2.totalBrLines);
                    updateGame(player1.turn ? &player1 : &player2);
                    flipRows(player1.turn ? &player2 : &player1,
                         player1.turn ? player1.totalBrLines - prev : player2.totalBrLines - prev);

                    updateScore(player1.turn ? &player1 : &player2,
                            player1.turn ? player1.totalBrLines - prev : player2.totalBrLines - prev);
                }
            }
            nextTurn(&player1, &player2);
        }
        else
        {
            int valid = 0;
            puts("Tetramino da inserire:");
            scanf("%lu", &nrPiece);

            puts("Rotazione tetramino:");
            scanf(" %c", &rotation);

            puts("Colonna dove inserire il tetramino:");
            scanf("%u", &column);
            valid = singlePlayerTurn(&player1, nrPiece, column, rotation);
            if (!valid)
                setGameOver(&isPlaying);
        }
    }

    endGame(&player1, &player2, isMultiplayer);

    return 0;
}
