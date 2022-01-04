#include "cpu.h"

cpuMove_t easyCPU(Player_t *player)
{
    cpuMove_t temp;
    char pRotation[4] = {'W', 'A', 'S', 'D'};
    temp.col = rand()%player->c;
    temp.rotation = pRotation[rand()%4];
    do
    {
        temp.piece = rand()%7;
    } while (!piecesLeft(player->pieces[piece]));
    return temp;
}
