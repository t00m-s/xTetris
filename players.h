typedef struct player{
    int turn;
    int totalPoints;

} Player_t;

void printStats(Player_t player)
{
    printf("Punteggio: %d", player.totalPoints);
}