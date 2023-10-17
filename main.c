#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int verifica_numero_perfeito(int n) {
    int soma = 0;
    for (int i = 1; i < n; i++) {
        if (n % i == 0) {
            soma += i;
        }
    }
    
    return (soma == n);
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("Uso incorreto. Sintaxe: %s <quantidade_de_threads> <tamanho_do_vetor>\n", argv[0]);
        return 1;
    }

    int num_threads = atoi(argv[1]);
    int tamanho_vetor = atoi(argv[2]);

    if (num_threads <= 0 || tamanho_vetor <= 0) {
        printf("Quantidade de threads e tamanho do vetor devem ser maiores que zero.\n");
        return 1;
    }

    srand(time(NULL));

    int *vet = (int*)malloc(tamanho_vetor * sizeof(int));
    if (vet == NULL) {
        printf("Erro de alocação de memória.\n");
        return 1;
    }

    // Preenchendo o vetor com valores aleatórios entre 1 e 10.000
    for (int i = 0; i < tamanho_vetor; i++) {
        vet[i] = rand() % 10000 + 1;
    }

    clock_t start_time = clock();
    int contador_numeros_perfeitos = 0;

    for (int i = 0; i < tamanho_vetor; i++) {
        if (verifica_numero_perfeito(vet[i])) {
            contador_numeros_perfeitos++;
        }
    }

    clock_t end_time = clock();
    double tempo_gasto = (double)(end_time - start_time) / CLOCKS_PER_SEC;

    printf("Número de números perfeitos encontrados: %d\n", contador_numeros_perfeitos);
    printf("Tempo gasto para verificação sequencial: %f segundos\n", tempo_gasto);

    free(vet);
    return 0;
}
