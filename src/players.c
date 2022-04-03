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


    p1->board.arena = (Game_t*) malloc(r * c * sizeof(Game_t));
    p1->board.r = r;
    p1->board.c = c;
    p1->totalPoints = 0;
    p1->totalBrLines = 0;

    p2->board.arena = (Game_t*) malloc(r * c * sizeof(Game_t));
    p2->board.r = r;
    p2->board.c = c;
    p2->totalPoints = 0;
    p2->totalBrLines = 0;

    for(i = 0; i < r; i++)
    {
        for (j = 0; j < c; j++)
        {
            p1->board.arena[i * c + j].game = EMPTY_;
            p1->board.arena[i * c + j].pieceType = EMPTY_;
            p2->board.arena[i * c + j].game = EMPTY_;
            p2->board.arena[i * c + j].pieceType = EMPTY_;

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

    free(p1->board.arena);
    free(p2->board.arena);
    freeAllPieces(p1->pieces);
    freeAllPieces(p2->pieces);
}


/**
 * @brief Funzione d'appoggio per stampare il colore di una casella di gioco
 * @param type Tipo di tetramino
 */
void printWithColor(const char type)
{
    switch(type)
    {
        case FLIP_:
            printf(COLOR_EMPTY_PIECE" "COLOR_RESET_DEFAULT);
            break;
        case 'I':
            printf(COLOR_CYAN" "COLOR_RESET_DEFAULT);
            break;
        case 'J':
            printf(COLOR_BLUE" "COLOR_RESET_DEFAULT);
            break;
        case 'L':
            printf(COLOR_WHITE" "COLOR_RESET_DEFAULT);
            break;
        case 'O':
            printf(COLOR_YELLOW" "COLOR_RESET_DEFAULT);
            break;
        case 'S':
            printf(COLOR_GREEN" "COLOR_RESET_DEFAULT);
            break;
        case 'T':
            printf(COLOR_PURPLE" "COLOR_RESET_DEFAULT);
            break;
        case 'Z':
            printf(COLOR_RED" "COLOR_RESET_DEFAULT);
            break;
        default:
            printf(COLOR_EMPTY_PIECE" "COLOR_RESET_DEFAULT);
            break;
    }
}

/* Da cambiare con sequenza ANSI */
void clearScreen() { system("clear"); }

void printGame(const Player_t *p1, const Player_t *p2, int isMultiplayer)
{
    size_t i, j;

    /*clearScreen();*/
    for(i = 0; i < p1->board.r; ++i)
    {
        /* Stampa contenuto board di gioco */
        for (j = 0; j < p1->board.c; ++j)
            printWithColor(p1->board.arena[i * p1->board.c + j].pieceType);

        printf("\t\t");

        if(isMultiplayer)
            for(j = 0; j < p2->board.c; ++j)
                printWithColor(p2->board.arena[i * p2->board.c + j].pieceType);

        printf("\n");
    }

    /* Stampa indici di gioco */
    for(j = 0; j < p1->board.c; ++j)
    {
        if(j > 9)
            printf("%lu ", j);
        else
            printf("%lu  ", j);
    }

    printf("\t\t");

    if(isMultiplayer)
    {
        for(j = 0; j < p2->board.c; ++j)
        {
            if(j > 9)
                printf("%lu ", j);
            else
                printf("%lu  ", j);
        }
    }
    printf("\n");
}

/**
 * @brief Funzione di appoggio per controllare la legalità di una mossa.
 * @param player Giocatore da cui si analizza la board di gioco.
 * @param freeRow Riga dalla quale comincia il controllo della mossa.
 * @param freeCol Colonna dalla quale comincia il controllo della mossa.
 * @param tetramino Tetramino da controllare.
 * @return 1 -> Mossa legale.
 *         0 -> Mossa non legale.
 */
int isLegalMove(Player_t player, const unsigned int freeRow, const unsigned int freeCol, Tetramino_t tetramino)
{
    size_t i, j;
    size_t tetH, tetW;
    /*Controllare limiti*/
    if(tetramino.width + freeCol > player.board.c || freeRow + tetramino.height  > player.board.r)
        return 0;

    for(i = freeRow, tetH = 0; i < (freeRow + tetramino.height) && tetH < tetramino.height; ++i, ++tetH) /*Scorro i due indici contemporaneamente*/
        for (j = freeCol, tetW = 0; j < (freeCol + tetramino.width) && tetW < tetramino.width; ++j, ++tetW)
            if (player.board.arena[i * player.board.c + j].game == PIECE_ && tetramino.piece[tetH * tetramino.width + tetW] == PIECE_) /*Controlla collisioni*/
                return 0; /*Bug Risolto: tetH * tetramino.width è corretto invece di tetramino.height*/

    return 1;
}

/**
 * @brief Funzione d'appoggio per trovare la combinazione {riga, colonna}
 *        dalla quale il tetramino può essere inserito.
 * @param player Giocatore
 * @param column Colonna dove si vuole inserire il tetramino
 * @param freeRow Dove viene salvata la riga trovata dalla funzione
 * @param freeCol Dove verrà salvata la colonna trovata dalla funzione
 * @param tetramino Tetramino da inserire nella board.
 * @return 1 -> Coppia {riga, colonna} trovata.
 *         0 -> Coppia {riga, colonna} non trovata.
 */
int findFree(Player_t player, unsigned column, unsigned *freeRow, unsigned *freeCol, Tetramino_t tetramino)
{
    size_t i = 0;
    int found = 0, flag = 1;

    while(i < player.board.r && flag) /* OLD BUG: Player.board.r was player.board.c */
    {
        if(player.board.arena[i * player.board.c + column].game == EMPTY_ || tetramino.piece[0] == EMPTY_)
        {
            if(isLegalMove(player, i, column, tetramino))
            {
                *freeRow = i;
                *freeCol = column;
                found = 1;
            }
            else
                flag = 0;

            ++i;
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
                    player->board.arena[i * player->board.c + j].game = copy.piece[tetH * copy.width + tetW];
                    player->board.arena[i * player->board.c + j].pieceType = copy.type;
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
    *brLines = 0; /* Reset del valore salvato */
    for(i = (int)player->board.r - 1; i >= 0; --i)
    {
        for (j = 0, isFull = 0; j < player->board.c; j++) /*TODO: Remove break */
            if (player->board.arena[i * player->board.c + j].game == PIECE_)
                ++isFull;
            else
                break;

        /* Rimuove la riga se completamente piena */
        if (isFull == player->board.c)
        {
            ++(*brLines);
            for (j = 0; j < player->board.c; ++j)
            {
                player->board.arena[i * player->board.c + j].game = EMPTY_;
                player->board.arena[i * player->board.c + j].pieceType = EMPTY_;
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

    while(flag && j < player.board.c)
    {
        if (player.board.arena[(player.board.r - 1) * player.board.c + j].game == EMPTY_)
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
    while(isLastRowEmpty(*player))
    {
        for (i = player->board.r - 1; i > 0; --i)
            for (j = 0; j < player->board.c; ++j)
            {
                player->board.arena[i * player->board.c + j].game = player->board.arena[(i - 1) * player->board.c +j].game;
                player->board.arena[i * player->board.c + j].pieceType = player->board.arena[(i - 1) * player->board.c + j].pieceType;
            }
    }
}

void flipRows(Player_t *player, unsigned int flips)
{
    size_t i, j;
    if(!flips) /*Non può invertire 0 righe */
        return;

    for(i = player->board.r - 1; i >= player->board.r - flips; --i)
    {
        for (j = 0; j < player->board.c; ++j)
        {
            if (player->board.arena[i * player->board.c + j].game == PIECE_)
            {
                player->board.arena[i * player->board.c + j].game = EMPTY_;
                player->board.arena[i * player->board.c + j].pieceType = EMPTY_;
            }
            else
            {
                player->board.arena[i * player->board.c + j].game = PIECE_;
                player->board.arena[i * player->board.c + j].pieceType = FLIP_; /* Placeholder per i colori */
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
        if(!player->pieces[i].qty)
            ++flag;

    return flag;
}

int isPlayable(const Player_t *player1, const Player_t *player2)
{
    if(missingPieces(player1) == (sizeof(player1->pieces) / sizeof(Tetramino_t)) || missingPieces(player2) == (sizeof(player2->pieces) / sizeof(Tetramino_t)))
        return 0;
    return 1;
}

int playerTurn(Player_t *player, Player_t *player2, size_t nrPiece, unsigned int column, char rotation, int isMultiplayer, unsigned int brLines)
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
