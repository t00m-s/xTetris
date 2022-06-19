/**
 * @file game.c
 * @author Tommaso Soncin
 * @brief Utilizzo varie funzioni create in precedenza per effettuare una partita di xTetris.
 */


#include <stdio.h>
#include "players.h"
#include "pieces.h"
#include "cpu.h"
int main()
{
    Player_t player1, player2;
    Tetramino_t collection[7];
    int isPlaying = 1, isMultiplayer = 0, cpu = 0;
    unsigned int column = 0;
    char rotation;
    size_t nrPiece = 0;

    /* Selezione modalità */
    puts("Scegli modalità di gioco:");
    puts("0) Single-player");
    puts("1) Multiplayer");
    scanf("%d", &isMultiplayer);

    if (isMultiplayer)
    {
        puts("0) Player1 vs Player2");
        puts("1) Player1 vs CPU");
        puts("2) CPU vs CPU");
        scanf("%d", &cpu);
    }

    startGame(&player1, &player2, collection, isMultiplayer);

    /* Loop di gioco */
    while (isPlaying)
    {
        printGame(&player1, &player2, isMultiplayer);
        printf("Turno giocatore %d:\n", player1.turn ? 1 : 2);
        printPieceHint(collection);
        if (isMultiplayer)
        {
            if(cpu == 2)
            {
                if(player1.turn) 
                {
                    CpuMove_t move = cpuDecision(&player1, collection);
                    if(!multiPlayerTurn(&player1, &player2, &collection[move.nrPiece], move.column, move.rotation))
                        setGameOver(&isPlaying);
                }
                else 
                {
                    CpuMove_t move = cpuDecision(&player2, collection);
                    if(!multiPlayerTurn(&player2, &player1, &collection[move.nrPiece], move.column, move.rotation))
                        setGameOver(&isPlaying);
                }
            }
            else if(cpu == 1 && player2.turn)
            {
                CpuMove_t move = cpuDecision(&player2, collection);
                if(!multiPlayerTurn(&player2, &player1, &collection[move.nrPiece], move.column, move.rotation))
                    setGameOver(&isPlaying);
            }
            else if(cpu == 1 && player1.turn)
            {
                getUserInput(&nrPiece, &column, &rotation);

                if(!multiPlayerTurn(&player1, &player2, &collection[nrPiece], column, rotation))
                    setGameOver(&isPlaying);
            }
            else
            {
                getUserInput(&nrPiece, &column, &rotation);

                if(player1.turn && !multiPlayerTurn(&player1, &player2, &collection[nrPiece], column, rotation))
                    setGameOver(&isPlaying);

                if(player2.turn && !multiPlayerTurn(&player2, &player1, &collection[nrPiece], column, rotation))
                    setGameOver(&isPlaying);
            }

            nextTurn(&player1, &player2);
        }
        else
        {
            getUserInput(&nrPiece, &column, &rotation);
            if (!singlePlayerTurn(&player1, &collection[nrPiece], column, rotation))
                setGameOver(&isPlaying);
        }
    }

    endGame(&player1, &player2, collection, isMultiplayer);

    return 0;
}
