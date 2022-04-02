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

    #ifndef FLIP_
        #define FLIP_ '#'
    #endif
#endif

/*
 * \e funziona solo su Linux, sostituisco con \033
 * Non propriamente colore del testo ma background color
*/
#ifndef COLOR_
#define COLOR_
    #ifndef COLOR_CYAN
        #define  COLOR_CYAN "\033[46m"
    #endif

    #ifndef COLOR_BLUE
        #define  COLOR_BLUE "\033[44m"
    #endif

    #ifndef COLOR_WHITE
        #define  COLOR_WHITE "\033[47m"
    #endif

    #ifndef COLOR_YELLOW
        #define  COLOR_YELLOW "\033[43m"
    #endif

    #ifndef COLOR_GREEN
        #define  COLOR_GREEN "\033[42m"
    #endif

    #ifndef COLOR_PURPLE
        #define  COLOR_PURPLE "\033[45m"
    #endif

    #ifndef COLOR_RED
        #define  COLOR_RED "\033[41m"
    #endif

    #ifndef COLOR_RESET_DEFAULT
        #define COLOR_RESET_DEFAULT "\033[0m"
    #endif

    #ifndef COLOR_EMPTY_PIECE
        #define COLOR_EMPTY_PIECE "\033[40m"
    #endif
#endif
