Minesweeper: ncinteract.o grid.o ncmove.o highscore.o
	gcc main.o ncinteract.o grid.o ncmove.o highscore.o -lncurses -o Minesweeper


ncinteract.o: ncinteract.c grid.h ncmove.h highscore.h
	gcc -c ncinteract.c

grid.o: grid.c grid.h
	gcc -c grid.c

ncmove.o: ncmove.c ncmove.h
	gcc -c ncmove.c

highscore.o: highscore.c highscore.h
	gcc -c highscore.c

clean:
	rm -f *.o Minesweeper
