typedef struct player{
    int turn;
    int totalPoints;
    int totalBrLines;
    char* game;
    Tetramino_t pieces[7];
} Player_t;
