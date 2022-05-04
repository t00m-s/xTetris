#include "players.h"

void nextTurn(Player_t *p1, Player_t *p2)
{
    if(p1->turn)
    {
        p1->turn = 0;
        p2->turn = 1;
    }
    else
    {
        p1->turn = 1;
        p2->turn = 0;
    }
}

void startGame(Player_t *p1, Player_t *p2)
{
    size_t r = 0, c = 0;
    int conf = 0;
    unsigned int qty = 0;
    size_t i, j;

    while(!conf)
    {
        do
        {
            puts("Dimensione righe campo di gioco: ");
            scanf("%lu", &r);
        }while(r < 15);

        do
        {
            puts("Dimensione colonne campo di gioco: ");
            scanf("%lu", &c);
        }while(c < 10);

        do
        {
            puts("Numero di pezzi per tetramino: ");
            scanf("%u", &qty);
        }while(qty < 20);

        printf("Righe: %lu , Colonne: %lu , Pezzi: %u.\nConfermi?\n", r, c, qty);
        scanf("%d", &conf);
    }


    p1->gameBoard.arena = (char*) malloc(r * c * sizeof(char));
    p1->gameBoard.colors = (char*) malloc(r * c * sizeof(char));
    p1->gameBoard.r = r;
    p1->gameBoard.c = c;
    p1->totalPoints = 0;
    p1->totalBrLines = 0;

    p2->gameBoard.arena = (char*) malloc(r * c * sizeof(char));
    p2->gameBoard.colors = (char*) malloc(r * c * sizeof(char));
    p2->gameBoard.r = r;
    p2->gameBoard.c = c;
    p2->totalPoints = 0;
    p2->totalBrLines = 0;

    if(!p1->gameBoard.arena || !p1->gameBoard.colors)
    {
        puts("Errore durante la creazione del primo giocatore.");
        exit(EXIT_FAILURE);
    }

    if(!p2->gameBoard.arena || !p2->gameBoard.colors)
    {
        puts("Errore durante la creazione del secondo giocatore.");
        exit(EXIT_FAILURE);
    }

    for(i = 0; i < r; i++)
    {
        for (j = 0; j < c; j++)
        {
            p1->gameBoard.arena[i * c + j] = EMPTY_;
            p1->gameBoard.colors[i * c + j] = EMPTY_;

            p2->gameBoard.arena[i * c + j] = EMPTY_;
            p2->gameBoard.colors[i * c + j] = EMPTY_;

        }
    }
    generatePieces(p1->pieces, qty);
    generatePieces(p2->pieces, qty);
    p1->turn = 1; /*Default: Comincia P1*/
    p2->turn = 0;
}

void endGame(Player_t *p1, Player_t *p2, int isMultiplayer)
{
    printf("Player1:\nRighe rimosse: %d\nPunteggio totale:%d\n\n", p1->totalBrLines, p1->totalPoints);
    if(isMultiplayer)
        printf("Player2:\nRighe rimosse: %d\nPunteggio totale:%d\n\n", p2->totalBrLines, p2->totalPoints);

    free(p1->gameBoard.arena);
    free(p1->gameBoard.colors);
    free(p2->gameBoard.arena);
    free(p2->gameBoard.colors);
    freeAllPieces(p1->pieces);
    freeAllPieces(p2->pieces);
}


/**
 * @brief Funzione d'appoggio per stampare il colore di una casella di gioco
 * @param type Tipo di tetramino
 */
void printWithColor(const char type)
{
    char rnd[7] = {'I', 'J', 'L', 'O', 'S', 'T', 'Z'};
    switch(type)
    {
        case FLIP_:
            printWithColor(rnd[rand()%7]);
            break;
        case 'I':
            printf(COLOR_CYAN"   "COLOR_RESET_DEFAULT" ");
            break;
        case 'J':
            printf(COLOR_BLUE"   "COLOR_RESET_DEFAULT" ");
            break;
        case 'L':
            printf(COLOR_WHITE"   "COLOR_RESET_DEFAULT" ");
            break;
        case 'O':
            printf(COLOR_YELLOW"   "COLOR_RESET_DEFAULT" ");
            break;
        case 'S':
            printf(COLOR_GREEN"   "COLOR_RESET_DEFAULT" ");
            break;
        case 'T':
            printf(COLOR_PURPLE"   "COLOR_RESET_DEFAULT" ");
            break;
        case 'Z':
            printf(COLOR_RED"   "COLOR_RESET_DEFAULT" ");
            break;
        default:
            printf(COLOR_EMPTY"   "COLOR_RESET_DEFAULT" ");
            break;
    }
}

/* Da cambiare con sequenza ANSI */
void clearScreen() { system("clear"); }

void printGame(const Player_t *p1, const Player_t *p2, int isMultiplayer)
{
    size_t i, j;

    /*clearScreen();*/
    for(i = 0; i < p1->gameBoard.r; ++i)
    {
        /* Stampa contenuto gameBoard di gioco */
        for (j = 0; j < p1->gameBoard.c; ++j)
            printWithColor(p1->gameBoard.colors[i * p1->gameBoard.c + j]);

        printf("\t\t");

        if(isMultiplayer)
            for(j = 0; j < p2->gameBoard.c; ++j)
                printWithColor(p2->gameBoard.colors[i * p2->gameBoard.c + j]);

        printf("\n");
    }

    /* Stampa indici di gioco
    for(j = 0; j < p1->gameBoard.c; ++j)
    {
        if(j > 9)
            printf("%lu ", j);
        else
            printf("%lu  ", j);
    }

    printf("\t\t");

    if(isMultiplayer)
    {
        for(j = 0; j < p2->gameBoard.c; ++j)
        {
            if(j > 9)
                printf("%lu ", j);
            else
                printf("%lu  ", j);
        }
    }
    */
    printf("\n");
}

/**
 * @brief Funzione di appoggio per controllare la legalità di una mossa.
 * @param player Giocatore da cui si analizza la gameBoard di gioco.
 * @param freeRow Riga dalla quale comincia il controllo della mossa.
 * @param freeCol Colonna dalla quale comincia il controllo della mossa.
 * @param tet Tetramino da controllare.
 * @return 1 -> Mossa legale.
 *         0 -> Mossa non legale.
 */
int isLegalMove(Player_t player, const unsigned int freeRow, const unsigned int freeCol, Tetramino_t tet)
{
    size_t i, j;
    size_t tetH, tetW;
    /*Controllare limiti*/
    if(tet.width + freeCol > player.gameBoard.c || freeRow + tet.height  > player.gameBoard.r)
        return 0;

    for(i = freeRow, tetH = 0; i < (freeRow + tet.height) && tetH < tet.height; ++i, ++tetH) /*Scorro i due indici contemporaneamente*/
        for (j = freeCol, tetW = 0; j < (freeCol + tet.width) && tetW < tet.width; ++j, ++tetW)
            if (player.gameBoard.arena[i * player.gameBoard.c + j] == PIECE_ && tet.piece[tetH * tet.width + tetW] == PIECE_) /*Controlla collisioni*/
                return 0; /*Bug Risolto: tetH * tet.width è corretto invece di tet.height*/

    return 1;
}

/**
 * @brief Funzione d'appoggio per trovare la combinazione {riga, colonna}
 *        dalla quale il tetramino può essere inserito.
 * @param player Giocatore
 * @param column Colonna dove si vuole inserire il tetramino
 * @param freeRow Dove viene salvata la riga trovata dalla funzione
 * @param freeCol Dove verrà salvata la colonna trovata dalla funzione
 * @param tetramino Tetramino da inserire nella gameBoard.
 * @return 1 -> Coppia {riga, colonna} trovata.
 *         0 -> Coppia {riga, colonna} non trovata.
 */
int findFree(Player_t player, unsigned column, unsigned *freeRow, unsigned *freeCol, Tetramino_t tetramino)
{
    size_t i = 0;
    int found = 0;
    /* OLD BUGS:
     * Player.gameBoard.r was player.gameBoard.c
     * Using while instead of for caused an infinite loop (even when written correctly)
    */
    for(i = 0; i < player.gameBoard.r; ++i)
    {
        if(player.gameBoard.arena[i * player.gameBoard.c + column] == EMPTY_ || tetramino.piece[0] == EMPTY_)
        {
            if(isLegalMove(player, i, column, tetramino))
            {
                *freeRow = i;
                *freeCol = column;
                found = 1;
            }
        }
    }

    return found;
}

/**
 * @brief Funzione di appoggio per creare la deepCopy che verrà modificata nella rotazione
 * @param tetramino Tetramino originale
 * @return DeepCopy del tetramino in input
 */
Tetramino_t copyTetramino(Tetramino_t *tetramino)
{
    Tetramino_t cpy;
    size_t i;
    cpy.width = tetramino->width;
    cpy.height = tetramino->height;
    cpy.type = tetramino->type;
    cpy.qty = tetramino->qty;
    cpy.piece = (char*) malloc(tetramino->width * tetramino->height * sizeof(char));

    for(i = 0; i < tetramino->width * tetramino->height; ++i)
        cpy.piece[i] = tetramino->piece[i];

    return cpy;
}

int insertPiece(Player_t *player, size_t nrPiece, unsigned column, char rotation)
{
    size_t i, j, tetW, tetH;
    int legal = 0;
    unsigned freeRow, freeCol;
    /*
     * Copia creata per evitare di modificare il puntatore originale
     * (che aveva causato bug visto che lo sovrascrivevo ruotandolo)
    */
    Tetramino_t copy;

    /* Evita di controllare pezzi inesistenti o fuori dall'array */
    if((nrPiece > (sizeof(player->pieces) / sizeof(Tetramino_t) ) - 1) || !player->pieces[nrPiece].qty)
        return legal;

    copy = rotatePiece(copyTetramino(&player->pieces[nrPiece]), rotation);
    if(findFree(*player, column, &freeRow, &freeCol, copy)) /* && isLegalMove(*player, freeRow, freeCol, copy) */
    {
        for(i = freeRow, tetH = 0; i < (freeRow + copy.height) && tetH < copy.height; ++i, ++tetH)
            for(j = freeCol, tetW = 0; j < (freeCol + copy.width) && tetW < copy.width; ++j, ++tetW)
                if(copy.piece[tetH * copy.width + tetW] == PIECE_) /* Evita di sovrascrivere altri pezzi */
                {
                    player->gameBoard.arena[i * player->gameBoard.c + j] = copy.piece[tetH * copy.width + tetW];
                    player->gameBoard.colors[i * player->gameBoard.c + j] = copy.type;
                }

        legal = 1;
    }
    free(copy.piece);
    return legal;
}

void removeRows(Player_t *player, unsigned int *brLines)
{
    int i;
    size_t j; /*Unironically wasted two hours to fix from size_t to int*/
    size_t isFull = 0;

    for(i = (int)player->gameBoard.r - 1; i >= 0; --i)
    {
        for (j = 0, isFull = 0; j < player->gameBoard.c; j++)
            if (player->gameBoard.arena[i * player->gameBoard.c + j] == PIECE_)
                ++isFull;

        /* Rimuove la riga se completamente piena */
        if (isFull == player->gameBoard.c)
        {
            ++(*brLines);
            for (j = 0; j < player->gameBoard.c; ++j)
            {
                player->gameBoard.arena[i * player->gameBoard.c + j] = EMPTY_;
                player->gameBoard.colors[i * player->gameBoard.c + j] = EMPTY_;
            }
        }
    }
}

/**
 * @brief Funzione d'appoggio per conoscere lo stato dell'ultima riga (piena, non piena)
 * @param player Giocatore
 * @return 1 -> Riga vuota. 0 -> Riga non vuota.
 */
int isLastRowEmpty(Player_t player)
{
    size_t j = 0;
    unsigned int isEmpty = 0;
    int flag = 1;

    while(flag && j < player.gameBoard.c)
    {
        if (player.gameBoard.arena[(player.gameBoard.r - 1) * player.gameBoard.c + j] == EMPTY_)
            ++isEmpty;
        else
            flag = 0;

        ++j;
    }

    return flag;
}

void updateGame(Player_t *player)
{
    size_t i, j;
    /*
     * OLD BUG: isLastRowEmpty on a while loop causing infinite loop if board was empty
    */
        for (i = player->gameBoard.r - 1; i > 0; --i)
            if(isLastRowEmpty(*player))
            {
                for (j = 0; j < player->gameBoard.c; ++j)
                {
                    player->gameBoard.arena[i * player->gameBoard.c + j] =
                        player->gameBoard.arena[(i - 1) * player->gameBoard.c + j];

                    player->gameBoard.colors[i * player->gameBoard.c + j] =
                        player->gameBoard.colors[(i - 1) * player->gameBoard.c + j];
                }
            }

}

void flipRows(Player_t *player, unsigned int flips)
{
    size_t i, j;
    if(flips < 3 || flips > player->gameBoard.r) /* Da specifica sotto le 3 righe non inverte*/
        return;

    for(i = player->gameBoard.r - 1; i >= player->gameBoard.r - flips; --i)
    {
        for (j = 0; j < player->gameBoard.c; ++j)
        {
            if (player->gameBoard.arena[i * player->gameBoard.c + j] == PIECE_)
            {
                player->gameBoard.arena[i * player->gameBoard.c + j] = EMPTY_;
                player->gameBoard.colors[i * player->gameBoard.c + j] = EMPTY_;
            }
            else
            {
                player->gameBoard.arena[i * player->gameBoard.c + j] = PIECE_;
                player->gameBoard.colors[i * player->gameBoard.c + j] = FLIP_; /* Placeholder per colore random */
            }
        }
    }
}

void updateScore(Player_t *player, unsigned int brLines)
{
    /*
    * La rimozione di una riga vale 1 punto,
    * la rimozione di due righe con un solo pezzo vale 3 punti,
    * tre righe 6 punti,
    * quattro righe 12 punti
    */
    switch(brLines)
    {
        case 1:
            player->totalPoints += 1;
            break;
        case 2:
            player->totalPoints += 3;
            break;
        case 3:
            player->totalPoints += 6;
            break;
        case 4:
            player->totalPoints += 12;
            break;
        default:
            break;
    }
    player->totalBrLines += brLines;
}

void setGameOver(int *isPlaying) { *isPlaying = 0; }

unsigned int missingPieces(const Player_t *player)
{
    size_t i, flag = 0;

    for(i = 0; i < sizeof(player->pieces) / sizeof(Tetramino_t); ++i)
        if(player->pieces[i].qty == 0)
            ++flag;

    return flag;
}

int isPlayable(const Player_t *player1, const Player_t *player2)
{
    if(missingPieces(player1) == (sizeof(player1->pieces) / sizeof(Tetramino_t)) ||
       missingPieces(player2) == (sizeof(player2->pieces) / sizeof(Tetramino_t)))
        return 0;
    return 1;
}

int playerTurn(Player_t *player, Player_t *player2, size_t nrPiece, unsigned int column,
               char rotation, int isMultiplayer, unsigned int brLines)
{
    if(insertPiece(player, nrPiece, column, rotation))
    {
        decreaseQty(&player->pieces[nrPiece]);
        removeRows(player, &brLines);
        updateGame(player);

        if(isMultiplayer)
            flipRows(player2, brLines);

        updateScore(player, brLines);
        return 1;
    }
    return 0;
}

int singlePlayerTurn(Player_t *player, size_t nrPiece, unsigned int column, char rotation)
{
    unsigned int brLines = 0;
    return playerTurn(player, NULL, nrPiece, column, rotation, 0, brLines);
}

int multiPlayerTurn(Player_t *player, Player_t *player2, size_t nrPiece, unsigned int column, char rotation)
{
    unsigned int brLines = 0;
    return playerTurn(player, player2, nrPiece, column, rotation, 1, brLines);
}

