#ifndef PIECES_VALUE
#define PIECES_VALUE
    #ifndef EMPTY_
        #define EMPTY_ '-'
    #endif

    #ifndef PIECE_
        #define PIECE_ 'X'
    #endif
#endif

#ifndef COLOR_
#define COLOR_
    #ifndef COLOR_CYAN
        #define  COLOR_CYAN "\e[0;36m"
    #endif

    #ifndef COLOR_BLUE
        #define  COLOR_BLUE "\e[0;34m"
    #endif

    /* Non esiste arancione come ANSI Escape  */
    #ifndef COLOR_ORANGE
        #define  COLOR_ORANGE
    #endif

    #ifndef COLOR_YELLOW
        #define  COLOR_YELLOW "\e[0;33m"
    #endif

    #ifndef COLOR_GREEN
        #define  COLOR_GREEN "\e[0;32m"
    #endif

    #ifndef COLOR_PURPLE
        #define  COLOR_PURPLE "\e[0;35m"
    #endif

    #ifndef COLOR_RED
        #define  COLOR_RED "\e[0;31m"
    #endif

    #ifndef COLOR_RESET_DEFAULT
        #define COLOR_RESET_DEFAULT "\e[0m"
    #endif
#endif
