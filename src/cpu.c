#include <stdlib.h>
#include "cpu.h"
#include "players.h"
#include "pieces.h"

typedef struct cpuDecision{
    char rotation;
    unsigned piece;
    unsigned col;
} cpuMove;

cpuMove easyCPU(Player_t *player)
{
    cpuMove temp;
    char pRotation[4] = {'W', 'A', 'S', 'D'};
    temp.col = rand()%player->c;
    temp.rotation = pRotation[rand()%4];
    do
    {
        temp.piece = rand()%7;
    } while (!piecesLeft(player->pieces[piece]));
    return temp;
}
