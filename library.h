#include <stdio.h>
#include <stdlib.h>

/* Dichiaro tutte le firme delle funzioni all'inizio */
void fillGame(char *game, int r, int c, char fill);
void fillRandom(char *game, int r, int c, char fill, int pStart, int pEnd);
void fillRow(char *game, int r, int c, char fill, int rFill);
void printGame(char *game, int r, int c);
void insertPiece(char *game, int r, int c, char tetramino[4][4], int *n_Piece, char rotation);
void removeRows(char *game, int r, int c, int *brLines);
void updateGame(char *game, int r, int c, int *total, int *brLines);
void updateScore(int *total, int *brLines, int *totalBrLines);
void setGameOver(int *isPlaying);
int  isLastRowFull(char *game, int r, int c);
int  isFirstRowFull(char *game, int r, int c);

/*Fine dichiarazioni firme*/
void fillGame(char *game, int r, int c, char fill)
{
    int i, j;
    for(i = 0; i < r; i++)
    {
        for(j = 0; j < c; j++)
            game[i * c + j] = fill;
    }
}

void fillRandom(char *game, int r, int c, char fill, int pStart, int pEnd) /* Serve solo per test */
{
    int i, j;
    for(i = pStart; i < pEnd; i++)
        for(j = 0; j < c; j++)
            game[i * c + rand()%c] = fill;
}

void fillRow(char *game, int r, int c, char fill, int rFill)
{
    int j;
    for(j = 0; j < c; ++j)
        game[rFill * c + j] = fill;
}


void printGame(char *game, int r, int c) /* Molto barbara come funzione */
{
    int i, j;
    printf("   "); /* Da incolonnare meglio */

    for(j = 0; j < c; j++) /* stampa indice colonne */
        printf("%d ", j);

    printf("\n");
    
    for(i = 0; i < r; i++)
    {
        if(i < 10) /* Stampa indice righe (probabilmente si può fare meglio)*/
            printf(" %d ", i);
        else
            printf("%d ", i);

        for(j = 0; j < c; j++) /* Stampa contenuto matrice di gioco */
            printf("%c ", game[i * c + j]);

        printf("\n");
    }
}

void insertPiece(char *game, int r, int c, char tetramino[4][4], int *n_Piece, char rotation)
{
    switch(rotation)
    {
        case 'W':
            break;
        case 'A':
            break;
        case 'S':
            break;
        case 'D':
            break;
        default:
            break;
    }
    --(*n_Piece);
}

void removeRows(char *game, int r, int c, int *brLines)
{
    int i, j, isFull = 0;

    for(i = r - 1; i >= 1; --i)
    {
        for (j = 0; j < c; j++) /* Controllo se tutta la riga è piena*/
        {
            if (game[i * c + j] == 'X')
                ++isFull;
            else
                break;
        }
        /* Se la riga è piena, viene rimossa.
         * Ripetuto per tutte le possibili righe (ottimizzare appena trova una riga vuota esce)
        */
        if (isFull == c)
        {
            for (j = 0; j < c; ++j)
                game[i * c + j] = 'O';
            ++(*brLines);
            printf("Rimossa riga: %d\n", i);
        }
        isFull = 0;
    }
}


void updateGame(char *game, int r, int c, int *total, int *brLines)
{
    int i, j;
    for(i = r - 1; i > 0; --i)
        for(j = 0; j < c; ++j)
            game[i * c + j] = game[(i - 1) * c + j]; /* Funziona ma shifta solo di una riga in totale*/

}

int isLastRowFull(char *game, int r, int c)
{
    int j, isFull = 0;

    for (j = 0; j < c; ++j)
    {
        if (game[(r - 1) * c + j] == 'X')
            ++isFull;
        else
        {
            isFull = 0;
            break;
        }
    }

    return isFull;
}

int isFirstRowFull(char *game, int r, int c)
{
    int j, isFull = 0;

    for(j = 0; j < c; ++j)
        if(game[j] == 'X')
            ++isFull;
        else
            isFull = 0;

    return isFull;
}

void updateScore(int *total, int *brLines, int *totalBrLines)
{
    /*
    * La rimozione di una riga vale 1 punto,
    * la rimozione di due righe con un solo pezzo vale 3 punti,
    * tre righe 6 punti,
    * quattro righe 12 punti (Questo per singleplayer, se 2 giocatori flippare l'ultima riga)
    */
    switch(*brLines)
    {
        case 1:
            *total += 1;
            break;
        case 2:
            *total += 3;
            break;
        case 3:
            *total += 6;
            break;
        case 4:
            *total += 12;
            break;
        default:
            break;
    }
    *totalBrLines += *brLines;
    *brLines = 0;
}

void setGameOver(int *isPlaying)
{
    *isPlaying = 0;
}
