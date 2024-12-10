Minesweeper:	main.o	grid.o ncmove.o highscore.o
	-gcc main.o grid.o ncmove.o highscore.o -o Minesweeper -lncurses

main.o: main.c grid.h ncmove.h highscore.h
	-gcc -c main.c

grid.o: grid.c grid.h
	-gcc -c grid.c

highscore.o: highscore.c highscore.h
	-gcc -c highscore.c

ncmove.o: ncmove.c ncmove.h
	-gcc -c ncmove.c

clean:
	rm -f *.o