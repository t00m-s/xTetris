OPTIONS=-Ansi -Wall -Wextra -pedantic

all: pieces.o players.o cpu.o
	gcc ${OPTIONS} -o xTetris game.c pieces.o players.o cpu.o

pieces.o: pieces.c
	gcc ${OPTIONS} -c pieces.c

players.o: players.c
	gcc ${OPTIONS} -c players.c

cpu.o: cpu.c
	gcc ${OPTIONS} -c cpu.c

clean:
	rm *.o 
