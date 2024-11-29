Test:	main.o	grid.o
	-gcc main.o grid.o -o Test

main.o: main.c grid.h
	-gcc -c main.c

grid.o: grid.c grid.h
	-gcc -c grid.c

clean:
	rm -f *.o