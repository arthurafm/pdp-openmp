all:
	gcc -c shellsort.c -o shellsort.o -fopenmp
	gcc main.c shellsort.o -o shellsort -fopenmp

run:
	./shellsort
