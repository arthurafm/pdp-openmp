#!/bin/sh
# Este script roda um unico job em SGE
# Ele pode ser executado pelo comando SGE abaixo:
# qsub um_job.sh

# A linha abaixo nao e' um comentario. Ela especifica que o que vem
# apos ela sera invocado com o /bin/sh shell
#$ -S /bin/sh

# Coloca os arquivos de saida e de erro do seu job no diretorio .
#$ -cwd
#--------------------------------
# exemplo: (altere a partir daqui)

#!/bin/bash

#!/bin/bash

# Verifica se o nome do arquivo de entrada foi passado como argumento
if [ -z "$1" ]; then
    echo "Uso: $0 <arquivo_entrada>"
    exit 1
fi

# Captura o nome do arquivo de entrada e substitui .in por .out
input_file="$1"
output_file="${input_file%.in}.out"

# Executa o comando `time` e salva os resultados no arquivo de saída
{ time ./shellsort "$input_file"; } 2> "$output_file"

# Mostra mensagem de confirmação
echo "Resultados salvos em $output_file"


# Fim do script
