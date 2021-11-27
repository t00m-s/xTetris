#include <stdio.h>
#include <stdlib.h>
#include </home/tom/Documents/Progetto/pieces.h>
/* Dichiaro tutte le firme delle funzioni all'inizio */
void fillGame(char *game, size_t r, size_t c, char fill);
void fillRandom(char *game, size_t c, char fill, int pStart, int pEnd);
void fillRow(char *game, size_t c, char fill, int rFill);
void printGame(char *game, size_t r, size_t c);

int  findFree(const char *game, size_t r, size_t c, int column, int *freeRow, int *freeCol);
int  isLegalMove(const char *game, size_t r, size_t c, const int *freeRow, const int *freeCol, Tetramino tetramino);
int  insertPiece(char *game, size_t r, size_t c, Tetramino *tetramino, int column);

void removeRows(char *game, size_t r, size_t c, int *brLines);
void updateGame(char *game, size_t r, size_t c);
void updateScore(int *total, int *brLines, int *totalBrLines);
void setGameOver(int *isPlaying);

int  isLastRowEmpty(const char *game, size_t r, size_t c);
int  isFirstRowFull(const char *game, size_t c);

void fillGame(char *game, size_t r, size_t c, char fill)
{
    int i, j;
    for(i = 0; i < r; i++)
        for(j = 0; j < c; j++)
            game[i * c + j] = fill;
}

void fillRandom(char *game, size_t c, char fill, int pStart, int pEnd) /* Serve solo per test */
{
    int i, j;
    for(i = pStart; i < pEnd; i++)
        for(j = 0; j < c; j++)
            game[i * c + rand()%c] = fill;
}

void fillRow(char *game, size_t c, char fill, int rFill) /*Usata solo per test*/
{
    int j;
    for(j = 0; j < c; ++j)
        game[rFill * c + j] = fill;
}

void printGame(char *game, size_t r, size_t c) /* It just works. */
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

int findFree(const char *game, size_t r, size_t c, int column, int *freeRow, int *freeCol)
{
    int i, j;
    for(i = (int) r - 1; i >= 0; --i)
        if(game[i * column] == 'O')
        {
            *freeRow = i;
            *freeCol = column;
            return 1;
        }
    return 0;
}

int isLegalMove(const char *game, size_t r, size_t c, const int *freeRow, const int *freeCol, Tetramino tetramino) /*Modificare: deve controllare se tutto il pezzo sta dentro*/
{ /*Mi servono i puntatori di row e col?*/
    int isLegal = 1;
    int i, j;
    int cFreeRow = *freeRow;
    int cFreeCol = *freeCol;

    /*Controllo se esce dai limiti*/
    if(tetramino.width + *freeCol >= c || *freeRow - tetramino.height  < 0)
        isLegal = 0;

    if(isLegal)/* Forse rischio errore con pezzo a T */
    {
        for(i = cFreeRow; i >= 0 && isLegal; --i)
            for(j = 0; j < cFreeCol && isLegal; ++j)
                if(game[i * c + j] != 'O')
                    isLegal = 0;
    }
    /*Controllare se in quello spazio posso metterci il pezzo */

    return isLegal;
}

int insertPiece(char *game, size_t r, size_t c, Tetramino *tetramino, int column)
{
    int i, j;
    int freeCol, freeRow;
    findFree(game, r, c, column, &freeRow, &freeCol);

    /*Controllo se mossa legale*/
    if(!isLegalMove(game, r, c, &freeRow, &freeCol, *tetramino))
        return 0;

    /*Inserimento pezzo*/
    for(i = tetramino->height - 1; i >= 0; --i, --freeRow)
        for (j = 0; j < tetramino->width; ++j)
            game[freeRow * c + j] = tetramino->piece[i * tetramino->width + j];
    
    --tetramino->qty;
    return 1;
}

void removeRows(char *game, size_t r, size_t c, int *brLines)
{
    int i, j, isFull = 0;

    for(i = (int)r - 1; i >= 0; --i)
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

void updateGame(char *game, size_t r, size_t c)
{
    int i, j;
    while(isLastRowEmpty(game, r, c))
    {
        for (i = (int) r - 1; i > 0; --i)
            for (j = 0; j < c; ++j)
                game[i * c + j] = game[(i - 1) * c + j];
    }
}

int isLastRowEmpty(const char *game, size_t r, size_t c)
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

int isFirstRowFull(const char *game, size_t c)
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
    * quattro righe 12 punti
     * QUESTO VALE PER SINGLEPLAYER
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
