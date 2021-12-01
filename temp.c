while(isPlaying)
{
/*Seleziona pezzo e rotazione*/
int confirm = 0;
while (!confirm)
{
do
{
printf("Seleziona il pezzo: \n");
scanf("%d", &nrPiece);
} while (nrPiece < 0 || nrPiece >= 7);

do /*Fa schifo? Forse. Funziona? In teoria*/
{
printf("Seleziona rotazione pezzo: \n");
scanf("%c", &rotation);
rotation = (char)toupper(rotation); /*Converte in maiuscolo ASCII*/
} while (rotation != 'W' || rotation != 'A' || rotation != 'S' || rotation != 'D');

printf("Confermi la scelta? \n");
scanf("%d", &confirm);
}
/*Controlla legalità mossa e inserisce pezzo*/
if(!insertPiece(gameP1, r, c, &tetramino[nrPiece], 0))/*Ho rimosso || per isFirstRowFull */
setGameOver(&isPlaying);
/*Rimozione righe piene e aggiornamento board di gioco*/
removeRows(gameP1, r, c, &brLines);

updateGame(gameP1, r, c);
/*Aggiornamento punteggio*/

updateScore(&total, &brLines, &totalBrLines);

printGame(gameP1, r, c);
printf("\n");

if(isFirstRowFull(gameP1, c))
setGameOver(&isPlaying);

}
