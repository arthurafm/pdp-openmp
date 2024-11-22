#include <stdio.h>
#include <stdlib.h>
#include <math.h>

short AbreArquivo(FILE **arq, const char *nome_arq, const char *modo) {
    *arq = fopen(nome_arq, modo);
    if (*arq == NULL) {
        return 0;
    }
    return 1;
}

int main() {
    for (int i = 1; i < 9; i++) {
        char file_name[50];
        sprintf(file_name, "shellsort_10na%d.in", i);
        
        FILE *arq; 
        if (AbreArquivo(&arq, file_name, "w")) {
            fprintf(arq, "%d\n", (int)pow(10, i));
            for (int j = (int)pow(10, i) - 1; j > 0; j--) {
                fprintf(arq, "%d\n", j);
            }
            fclose(arq);
        }
    }
    return 0;
}
