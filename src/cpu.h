/**
 * @file cpu.h
 * @author Tommaso Soncin
 * @brief Implementazione di una CPU per il gioco xTetris
 */

#ifndef CPU_H
#define CPU_H
#include <stdlib.h>
#include "players.h"
#include <string.h>

/**
 * @brief struct che contiene la mossa della CPU
 */
typedef struct cpuDecision{
    char rotation;
    unsigned piece;
    unsigned col;
} cpuMove_t;

/**
 * @brief CPU che calcola la miglior mossa basata sulla situazione attuale della board di gioco
 * @param player Giocatore da analizzare per calcolare la mossa
 * @return struct con mossa della CPU
 */
void easyCPU(Player_t *player);

#endif
