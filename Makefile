all:
	gcc -c shellsort.c -o shellsort.o -fopenmp
	gcc main.c shellsort.o -o shellsort -fopenmp
	gcc filemaker.c -o filemaker -lm
run:
	./shellsort
	./filemaker

clean:
	rm -f *.o
	rm -f shellsort
	rm -f filemaker
	rm -f *.in
	rm -f *.out