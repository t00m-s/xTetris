typedef struct player{
    char* game;
    size_t r;
    size_t c;
    Tetramino_t pieces[7];
    unsigned qty;
    int totalPoints;
    int totalBrLines;
    int turn;
}Player_t;

void nextTurn(Player_t *p1, Player_t *p2);

void nextTurn(Player_t *p1, Player_t *p2)
{
    if(p1->turn)
    {
        p1->turn = 0;
        p2->turn = 1;
    }
    else
    {
        p1->turn = 1;
        p2->turn = 0;
    }
}

