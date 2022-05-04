/**
 * @file cpu.h
 * @author Tommaso Soncin
 * @brief Definizione delle funzioni della CPU per il gioco xTetris
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
    unsigned int nrPiece;
    unsigned int column;
    char rotation;
} CpuMove_t;

/**
 * @brief CPU che calcola la miglior mossa basata sulla situazione attuale della gameBoard di gioco
 * @param player Giocatore da analizzare per calcolare la mossa
 * @return Mossa scelta dalla CPU
 */
CpuMove_t cpuDecision(Player_t *player);

#endif
