/* Copyright (c) 2011 the authors listed at the following URL, and/or
 the authors of referenced articles or incorporated external code:
 http://en.literateprograms.org/Shell_sort_(C)?action=history&offset=20060603235103

 Permission is hereby granted, free of charge, to any person obtaining
 a copy of this software and associated documentation files (the
 "Software"), to deal in the Software without restriction, including
 without limitation the rights to use, copy, modify, merge, publish,
 distribute, sublicense, and/or sell copies of the Software, and to
 permit persons to whom the Software is furnished to do so, subject to
 the following conditions:

 The above copyright notice and this permission notice shall be
 included in all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

 Retrieved from: http://en.literateprograms.org/Shell_sort_(C)?oldid=5835
 */

#include "shellsort.h"
#include <string.h>
#include <omp.h>

/*

1- Organizar o problema -> Não é paralelizável, porque a escrita é ordenada
2- Separar intervalos -> Paralelizável - podemos tratar úm elemento de cada um dos intervalos ao mesmo tempo
3- Dentro dos intervalos -> Não é paralelizável - porque tem dependência de dados

*/


/* 	A parte paralelizável do shellSort se põe nos diferentes intervalos
	por parte do algoritmo, portanto, dentro dessa função */
void shell_sort_pass(char *a, int length, long int size, int interval) {
	int i;
	
	/* Leitura do vetor e separação de intervalos */
	/* A eficiência máxima pode ser atingida através de executar o máximo de elementos que não estão no mesmo intervalo ao mesmo tempo */
	#pragma omp parallel for schedule(auto)
	for (i = 0; i < size; i++) {
		/* Insert a[i] into the sorted sublist */
		int j;

		char v[length];
		strcpy(v, a + i * length);

		/*	Trata o interior dos intervalos de trás pra frente,
			quebrando a execução ao encontrar ordenamento, assumindo suas operações passadas já ordenaram. */
		for (j = i - interval; j >= 0; j -= interval) {
			if (strcmp(a + j * length, v) <= 0)
				break;
			strcpy(a + (j + interval) * length, a + j * length);
		}
		strcpy(a + (j + interval) * length, v);
	}
}

void shell_sort(char *a, int length, long int size) {
	int ciura_intervals[] = { 701, 301, 132, 57, 23, 10, 4, 1 };
	double extend_ciura_multiplier = 2.3;

	int interval_idx = 0;
	int interval = ciura_intervals[0];

	/* Define o tamanho inicial do intervalo a partir do tamanho do vetor */
	if (size > interval) {
		/* Iteração muito curta para valer a pena ser paralelizável */
		while (size > interval) {
			interval_idx--;
			interval = (int) (interval * extend_ciura_multiplier);
		}
	} else {
		/* Iteração muito curta para valer a pena ser paralelizável */
		while (size < interval) {
			interval_idx++;
			interval = ciura_intervals[interval_idx];
		}
	}

	/* Realiza as iterações enquanto reduz os intervalos */
	/* Essa iteração não é paralelizável, uma vez a cada passo, a operação utiliza o mesmo espaço dentro do vetor */
	while (interval > 1) {
		interval_idx++;
		if (interval_idx >= 0) {
			interval = ciura_intervals[interval_idx];
		} else {
			interval = (int) (interval / extend_ciura_multiplier);
		}

		shell_sort_pass(a, length, size, interval);
	}

}

