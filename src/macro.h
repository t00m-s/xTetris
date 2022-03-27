/**
 * @file macro.h
 * @author Tommaso Soncin
 * @brief Definizione di varie macro utilizzate nel gioco xTetris
 */

#ifndef PIECES_VALUE
#define PIECES_VALUE
    #ifndef EMPTY_
        #define EMPTY_ '-'
    #endif

    #ifndef PIECE_
        #define PIECE_ 'X'
    #endif
#endif

/*
 * \e funziona solo su Linux, sostituisco con \033
*/
#ifndef COLOR_
#define COLOR_
    #ifndef COLOR_CYAN
        #define  COLOR_CYAN "\033[0;36m"
    #endif

    #ifndef COLOR_BLUE
        #define  COLOR_BLUE "\033[0;34m"
    #endif

    /* Non esiste arancione come ANSI Escape quindi uso il bianco */
    #ifndef COLOR_WHITE
        #define  COLOR_WHITE "\033[0;37m"
    #endif

    #ifndef COLOR_YELLOW
        #define  COLOR_YELLOW "\033[0;33m"
    #endif

    #ifndef COLOR_GREEN
        #define  COLOR_GREEN "\033[0;32m"
    #endif

    #ifndef COLOR_PURPLE
        #define  COLOR_PURPLE "\033[0;35m"
    #endif

    #ifndef COLOR_RED
        #define  COLOR_RED "\033[0;31m"
    #endif

    #ifndef COLOR_RESET_DEFAULT
        #define COLOR_RESET_DEFAULT "\033[0m"
    #endif

    #ifndef COLOR_EMPTY_PIECE
        #define COLOR_EMPTY_PIECE
    #endif
#endif
