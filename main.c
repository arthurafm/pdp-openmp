#include <stdio.h>
#include <stdlib.h>
#include "shellsort.h"

/* Define o tamanho máximo dos elementos a serem processados no vetor */
#define LENGTH 8

FILE *fin, *fout;

char *strings;
long int N;

void openfiles(char* file_name) {
	fin = fopen(file_name, "r+");
	if (fin == NULL) {
		perror("fopen fin");
		exit(EXIT_FAILURE);
	}

	fout = fopen("shellsort.out", "w");
	if (fout == NULL) {
		perror("fopen fout");
		exit(EXIT_FAILURE);
	}
}

void closefiles(void) {
	fclose(fin);
	fclose(fout);
}

/* 	Input se dá por um arquivo chamado "shellsort.in" cuja primeira linha dada é o número de elementos no vetor,
	seguida pela sequência de elementos a serem ordenados.
	Os elementos são ordenados como STRINGS, não como números. */

int main(int argc, char* argv[]) {

	long int i;

	openfiles(argv[1]);

	fscanf(fin, "%ld", &N);
	strings = (char*) malloc(N * LENGTH);
	if (strings == NULL) {
		perror("malloc strings");
		exit(EXIT_FAILURE);
	}

	for (i = 0; i < N; i++)
		fscanf(fin, "%s", strings + (i * LENGTH));

	shell_sort(strings, LENGTH, N);

	for (i = 0; i < N; i++)
		fprintf(fout, "%s\n", strings + (i * LENGTH));
		fflush(stdin);

	free(strings);
	closefiles();

	return EXIT_SUCCESS;
}
