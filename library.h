#include <stdio.h>
#include <stdlib.h>
#include <ctype.h> /* Per toupper() */
#include </home/tom/Documents/Progetto/pieces.h>
/* Dichiaro tutte le firme delle funzioni all'inizio */
void startGame(char *game, size_t r, size_t c);
void fillRandom(char *game, size_t c, char fill, int pStart, int pEnd);
void fillRow(char *game, size_t c, char fill, int rFill);
void printGame(char *game, size_t r, size_t c);

int  findFree(const char *game, size_t r, size_t c, int column, int *freeRow, int *freeCol, Tetramino_t tetramino);
int  isLegalMove(const char *game, size_t r, size_t c, const int *freeRow, const int *freeCol, Tetramino_t tetramino);
void rotatePiece(Tetramino_t *tetramino, int type);
int  insertPiece(char *game, size_t r, size_t c, Tetramino_t tetramino, int column);


void removeRows(char *game, size_t r, size_t c, int *brLines);
void updateGame(char *game, size_t r, size_t c);
void flipRows(char *game, size_t r, size_t c, unsigned int flips);
void updateScore(int *total, int *brLines, int *totalBrLines);
void setGameOver(int *isPlaying);

int  isLastRowEmpty(const char *game, size_t r, size_t c);
int  isFirstRowFull(const char *game, size_t c);

void startGame(char *game, size_t r, size_t c)
{
    int i, j;
    for(i = 0; i < r; i++)
        for(j = 0; j < c; j++)
            game[i * c + j] = empty;
}

void fillRandom(char *game, size_t c, char fill, int pStart, int pEnd) /* Serve solo per test */
{
    int i, j;
    for(i = pStart; i < pEnd; i++)
        for(j = 0; j < c; j++)
            game[i * c + rand()%c] = fill; /* NOLINT(cert-msc50-cpp) Sopprime un warning inutile*/
}

void fillRow(char *game, size_t c, char fill, int rFill) /*Usata solo per test*/
{
    int j;
    for(j = 0; j < c; ++j)
        game[rFill * c + j] = fill;
}

void printGame(char *game, size_t r, size_t c) /* It just KIND OF works. */
{
    int i, j;
    for(i = 0; i < r; i++)
    {
        for(j = 0; j < c; j++) /* Stampa contenuto matrice di gioco */
            printf("%c ", game[i * c + j]);
        printf("\n");
    }

    for(j = 0; j < c; j++) /* stampa indice colonne */
        printf("%d ", j);
    printf("\n");
}

int findFree(const char *game, size_t r, size_t c, int column, int *freeRow, int *freeCol, Tetramino_t tetramino)
{
    size_t i;
    for(i = 0; i < r - 1; ++i)
    {
        /*Anche se la board ha già un pezzo potrei ignorarlo se il tetramino in quella posizione è vuoto*/
        if(game[i * c + column] == empty || tetramino.piece[0] == empty)
        {
            *freeRow = i;
            *freeCol = column;
            return 1;
        }
    }

    return 0;
}

int isLegalMove(const char *game, size_t r, size_t c, const int *freeRow, const int *freeCol, Tetramino_t tetramino)
{   /*Qui controlla se l'espansione è possibile*/
    int i, j;
    int tetH, tetW;
    /*Controllare limiti*/
    if(tetramino.width + *freeCol > c || *freeRow + tetramino.height  > r)
        return 0;

    for(i = *freeRow, tetH = 0; i < (*freeRow + tetramino.height) && tetH < tetramino.height; ++i, ++tetH) /*Scorro i due indici contemporaneamente*/
        for(j = *freeCol, tetW = 0; j < (*freeCol + tetramino.width) && tetW < tetramino.width; ++j, ++tetH)
            if(game[i * c + j] == piece && tetramino.piece[tetH * tetramino.height + tetW] == piece) /*Collisione, altrimenti potrei metterlo*/
                return 0;

    return 1;
}

int typeRotation(char rotation)
{
    switch(rotation)
    {
        case 'A':
            return 3;
        case 'S':
            return 2;
        case 'D':
            return 1;
        default:
            return 0;
    }
}

void rotatePiece(Tetramino_t *tetramino, int type)
{
    /*swappare width e height*/
}

int insertPiece(char *game, size_t r, size_t c, Tetramino_t tetramino, int column) /*Da inserire la rotazione*/
{
    /*Passo una copia così posso ruotarla a piacimento*/
    /*Fare: controlla tutta la possibile colonna e si salva ogni volta il risultato, l'ultimo legale è dove posso inserire il pezzo*/
    return 0;
}

void removeRows(char *game, size_t r, size_t c, int *brLines)
{
    int i, j, isFull = 0;

    for(i = (int)r - 1; i >= 0; --i)
    {
        for (j = 0; j < c; j++) /* Controllo se tutta la riga è piena*/
            if (game[i * c + j] == piece)
                ++isFull;
            else
                break;

        /* Se la riga è piena, viene rimossa.
         * Ripetuto per tutte le possibili righe (ottimizzare appena trova una riga vuota esce)
        */
        if (isFull == c)
        {
            for (j = 0; j < c; ++j)
                game[i * c + j] = empty;
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

void flipRows(char *game, size_t r, size_t c, unsigned int flips) /*Non l'ho ancora testata ma dovrebbe andare*/
{
    int i, j;
    if(!flips) /*Non può invertire 0 righe, non ha senso... */
        return;

    for(i = (int) r - 1; i >= r - 1 - flips; --i)
        for(j = 0; j < c; ++j)
            if(game[i * c + j] == piece)
                game[i * c + j] = empty;
            else
                game[i * c + j] = piece;
}

int isLastRowEmpty(const char *game, size_t r, size_t c)
{
    int j, isEmpty = 0;

    for (j = 0; j < c; ++j)
        if (game[(r - 1) * c + j] == empty)
            ++isEmpty;
        else
            break;

    return isEmpty == c;
}

/*Forse è kinda useless sta funzione*/
int isFirstRowFull(const char *game, size_t c)
{
    int j, isFull = 0;

    for(j = 0; j < c; ++j)
        if(game[j] == piece)
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
     * Con multiplayer dopo chiamo flip rows
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
