Minesweeper:	main.o	grid.o ncmove.o
	-gcc main.o grid.o ncmove.o -o Minesweeper -lncurses

main.o: main.c grid.h ncmove.h
	-gcc -c main.c

grid.o: grid.c grid.h
	-gcc -c grid.c

ncmove.o: ncmove.c ncmove.h
	-gcc -c ncmove.c

clean:
	rm -f *.o