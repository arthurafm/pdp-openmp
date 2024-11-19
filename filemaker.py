#Tentando mais uma vez criar o arquivo após o reset do ambiente.
import numpy as np
import random
#Gera 100 milhões de números aleatórios 
random_numbers = [random.randint(0, 99999999) for _ in range(100000000)]

#Define o caminho do arquivo para salvar
file_path = 'shellshort_100M.in'

#Salva os números em um arquivo de texto
np.savetxt(file_path, random_numbers, fmt='%d')

file_path