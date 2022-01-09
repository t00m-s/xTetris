#ifndef CPU_H
#define CPU_H

#include <stdlib.h>
#include "players.h"

typedef struct cpuDecision{
    char rotation;
    unsigned piece;
    unsigned col;
} cpuMove_t;

cpuMove_t easyCPU(Player_t *player);
#endif
