#include <stdio.h>
#include <stdlib.h>
#include </home/kh3ro/Documents/Progetto/pieces.h>
/* Dichiaro tutte le firme delle funzioni all'inizio */
void fillGame(char *game, int r, int c, char fill);
void fillRandom(char *game, int r, int c, char fill, int pStart, int pEnd);
void fillRow(char *game, int r, int c, char fill, int rFill);
void printGame(char *game, int r, int c);
int  findFirstFreeColumn(char *game, int r, int c);
int  insertPiece(char *game, int r, int c, Tetramino tetramino, int column);
void removeRows(char *game, int r, int c, int *brLines);
void updateGame(char *game, int r, int c, int *total, int *brLines);
void updateScore(int *total, int *brLines, int *totalBrLines);
void setGameOver(int *isPlaying);
int  isLastRowEmpty(char *game, int r, int c);
int  isFirstRowFull(char *game, int r, int c);

/*Fine dichiarazioni firme*/
void fillGame(char *game, int r, int c, char fill)
{
    int i, j;
    for(i = 0; i < r; i++)
        for(j = 0; j < c; j++)
            game[i * c + j] = fill;
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

int firstFreeColRow(char *game, int r, int c, )
{

}

int insertPiece(char *game, int r, int c, Tetramino tetramino, int column)
{
    int i, j, k;
    int isLegal = 1;
    tetramino.width = 4;
    tetramino.height = 1;
    for(i = 0; i < tetramino.width; ++i)
        tetramino.piece[i] = 'X';

    /*Inserimento pezzo*/
    for(i = tetramino.height - 1; i >= 0; ++i)
        for(j = 0; j < tetramino.width; ++j)
            if(game[1] != 'X')
                game[1] = tetramino.piece[i * tetramino.width + j];


    return isLegal;
}

void removeRows(char *game, int r, int c, int *brLines)
{
    int i, j, isFull = 0;

    for(i = r - 1; i >= 0; --i)
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
        }
        isFull = 0;
    }
}

void updateGame(char *game, int r, int c, int *total, int *brLines)
{
    int i, j;
    for (i = r - 1; i > 0; --i)
        for (j = 0; j < c; ++j)
            game[i * c + j] = game[(i - 1) * c + j];
}

int isLastRowEmpty(char *game, int r, int c)
{
    int j, isEmpty = 0;

    for (j = 0; j < c; ++j)
    {
        if (game[(r - 1) * c + j] == 'O')
            ++isEmpty;
        else
            break;
    }

    return isEmpty == c;
}

int isFirstRowFull(char *game, int r, int c)
{
    int j, isFull = 0;

    for(j = 0; j < c; ++j)
        if(game[j] == 'X')
            ++isFull;
        else
            break;

    return isFull == c;
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
