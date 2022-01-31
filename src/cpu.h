#ifndef CPU_H
#define CPU_H
#include <stdlib.h>
#include "players.h"
#include <string.h>
typedef struct cpuDecision{
    char rotation;
    unsigned piece;
    unsigned col;
} cpuMove_t;

/**
 * @brief CPU per il gioco
 * @param player Giocatore da analizzare per calcolare la mossa
 * @return struct con mossa della CPU
 */
void easyCPU(Player_t *player);

#endif
