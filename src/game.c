#include <stdio.h>
#include "players.h"
#include "pieces.h"
#include "cpu.h"

/* Se inserisco un pezzo in  */

int main()
{
    Player_t player1, player2;
    int isPlaying = 1, isMultiplayer = 0, confirm = 0, cpu = 0;
    unsigned int column = 0;
    char rotation = ' ';
    size_t nrPiece = 0;
    setbuf(stdout, 0); /* Usare solo CON DEBUG */
    startGame(&player1, &player2);
    /* Selezione modalità */
    printf("Scegli modalità di gioco:\n0) Single-player\n1) Multiplayer\n");
    scanf("%d", &isMultiplayer);
    if(isMultiplayer)
    {
        printf("0)Player1 vs Player2\n1)Player1 vs CPU\n");
        scanf("%d", &cpu);
    }


    /* Loop di gioco */
    while(isPlaying)
    {
        printGame(&player1, &player2, isMultiplayer);
        printf("Turno giocatore %d:\n", player1.turn ? 1 : 2);
        printPieceHint(player1.turn ? player1.pieces : player2.pieces);
        if(isMultiplayer)
        {
            if(player1.turn)
            {
                printf("Tetramino da inserire:\n");
                scanf("%lu", &nrPiece);

                printf("Rotazione tetramino:\n");
                scanf(" %c", &rotation);

                printf("Colonna dove inserire il tetramino:\n");
                scanf("%u", &column);

                if(!multiPlayerTurn(&player1, &player2, nrPiece, column, rotation))
                    setGameOver(&isPlaying);
            }
            else
            {
                if(cpu)
                {
                    CpuMove_t cpuChoice = cpuDecision(&player2); /* Infinite loop here
                    printf("Valori: %d \t%d \t%c\n", cpuChoice.nrPiece, cpuChoice.column, cpuChoice.rotation);
                    Si blocca quando prova dalla sesta colonna
                    */
                    if(!multiPlayerTurn(&player2, &player1, cpuChoice.nrPiece, cpuChoice.column, cpuChoice.rotation))
                        setGameOver(&isPlaying);
                }
                else
                {
                    printf("Tetramino da inserire:\n");
                    scanf("%lu", &nrPiece);

                    printf("Rotazione tetramino:\n");
                    scanf(" %c", &rotation);

                    printf("Colonna dove inserire il tetramino:\n");
                    scanf("%u", &column);
                    if (!multiPlayerTurn(&player2, &player1, nrPiece, column, rotation))
                        setGameOver(&isPlaying);
                }
            }
            nextTurn(&player1, &player2);
        }
        else
        {
            printf("Tetramino da inserire:\n");
            scanf("%lu", &nrPiece);

            printf("Rotazione tetramino:\n");
            scanf(" %c", &rotation);

            printf("Colonna dove inserire il tetramino:\n");
            scanf("%u", &column);
            if(!singlePlayerTurn(&player1, nrPiece, column, rotation))
                setGameOver(&isPlaying);
        }
    }

    /* Fine gioco: Stampa risultati e libera memoria occupata */
    endGame(&player1, &player2, isMultiplayer);

    return 0;
}
