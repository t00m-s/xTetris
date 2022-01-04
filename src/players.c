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

void startGame(Player_t *p1, Player_t *p2, size_t r, size_t c, unsigned qty)
{
    int i, j;
    p1->game = (char*) malloc(r * c * sizeof(char));
    p1->r = r;
    p1->c = c;
    p2->r = r;
    p2->c = c;
    p2->game = (char*) malloc(r * c * sizeof(char));
    for(i = 0; i < r; i++)
    {
        for (j = 0; j < c; j++)
        {
            p1->game[i * c + j] = empty;
            p2->game[i * c + j] = empty;
        }
    }
    generatePieces(p1->pieces, qty);
    generatePieces(p2->pieces, qty);
    p1->turn = 1; /*Comincia il giocatore 1*/
    p2->turn = 0;
}

void endGame(Player_t p1, Player_t p2, int isMultiplayer)
{
    printf("Player1:\nRighe rimosse: %d\nPunteggio totale:%d\n\n",p1.totalBrLines,p1.totalPoints);
    if(isMultiplayer)
        printf("Player2:\nRighe rimosse: %d\nPunteggio totale:%d\n\n",p2.totalBrLines,p2.totalPoints);

    free(p1.game);
    free(p2.game);
    freeAllPieces(p1.pieces);
    freeAllPieces(p2.pieces);
}

void printGame(Player_t p1, Player_t p2, int isMultiplayer)
{
    int i, j;

    if(isMultiplayer)
    {
        for(i = 0; i < p1.r; ++i)
        {
            for(j = 0; j < p1.c; ++j)
                printf("%c ", p1.game[i * p1.c + j]);

            printf("\t\t");

            for(j = 0; j < p2.c; j++)
                printf("%c ", p2.game[i * p2.c + j]);
            printf("\n");
        }
        for(j = 0; j < p1.c; j++)
            printf("%d ", j);
        printf("\t\t");
        for(j = 0; j < p1.c; ++j)
            printf("%d ", j);
        printf("\n");
        return;
    }

    for(i = 0; i < p1.r; i++)
    {
        for(j = 0; j < p1.c; j++) /* Stampa contenuto matrice di gioco */
            printf("%c ", p1.game[i * p1.c + j]);

        printf("\n");
    }

    for(j = 0; j < p1.c; j++) /* stampa indice colonne */
        printf("%d ", j);

    printf("\n");
}


void removeRows(Player_t *player, unsigned *brLines)
{
    int i, j, isFull = 0;

    for(i = (int)player->r - 1; i >= 0; --i)
    {
        for (j = 0; j < player->c; j++) /* Controllo se tutta la riga è piena*/
            if (player->game[i * player->c + j] == piece)
                ++isFull;
            else
                break;

        /* Se la riga è piena, viene rimossa.
         * Ripetuto per tutte le possibili righe (ottimizzare appena trova una riga vuota esce)
        */
        if (isFull == player->c)
        {
            for (j = 0; j < player->c; ++j)
                player->game[i * player->c + j] = empty;
            ++(*brLines);
        }
        isFull = 0;
    }
}

void updateGame(Player_t *player)
{
    int i, j;
    while(isLastRowEmpty(*player))
    {
        for (i = (int) player->r - 1; i > 0; --i)
            for (j = 0; j < player->c; ++j)
                player->game[i * player->c + j] = player->game[(i - 1) * player->c + j];
    }
}

void flipRows(Player_t *player, unsigned int flips) /*Non l'ho ancora testata ma dovrebbe andare*/
{
    size_t i, j;
    if(!flips) /*Non può invertire 0 righe, non ha senso... */
        return;

    for(i = player->r - 1; i >= player->r - flips; --i)
        for(j = 0; j < player->c; ++j)
            if(player->game[i * player->c + j] == piece)
                player->game[i * player->c + j] = empty;
            else
                player->game[i * player->c + j] = piece;
}

int isLastRowEmpty(Player_t player)
{
    size_t j;
    unsigned isEmpty = 0;

    for (j = 0; j < player.c; ++j)
        if (player.game[(player.r - 1) * player.c + j] == empty)
            ++isEmpty;
        else
            break;

    return isEmpty == player.c;
}

void updateScore(Player_t *player, unsigned *brLines)
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
    player->totalBrLines += *brLines;
    *brLines = 0;
}

void setGameOver(int *isPlaying)
{
    *isPlaying = 0;
}
