#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

#define MAX_THREADS 4

int verifica_numero_perfeito(int n) {
    if (n <= 1) {
        return 0;
    }

    int soma = 1;

    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            soma += i;
            if (i != n / i) {
                soma += n / i;
            }
        }
    }

    return (soma == n) ? n : 0;
}

void *verificar_perfeitos(void *args) {
    int *data = (int *)args;
    int *results = (int *)malloc(data[1] * sizeof(int));
    int count = 0;

    for (int i = data[0]; i < data[1]; i++) {
        int resultado = verifica_numero_perfeito(data[2][i]);
        if (resultado != 0) {
            results[count] = resultado;
            count++;
        }
    }

    results = (int *)realloc(results, count * sizeof(int));

    return results;
}

int main() {
    srand(time(NULL));
    int size, num_threads;

    printf("Digite o tamanho do vetor: ");
    scanf("%d", &size);

    printf("Digite o número de threads (1-%d): ", MAX_THREADS);
    scanf("%d", &num_threads);

    if (num_threads < 1 || num_threads > MAX_THREADS) {
        printf("Número de threads inválido. Usando 1 thread.\n");
        num_threads = 1;
    }

    int *vet = (int *)malloc(size * sizeof(int));
    int counter = 0;

    for (int n = 0; n < size; n++) {
        vet[n] = rand() % 10;
    }

    pthread_t threads[MAX_THREADS];
    int thread_data[MAX_THREADS][3];

    for (int i = 0; i < num_threads; i++) {
        thread_data[i][0] = i * (size / num_threads);
        thread_data[i][1] = (i == num_threads - 1) ? size : (i + 1) * (size / num_threads);
        thread_data[i][2] = vet;
        pthread_create(&threads[i], NULL, verificar_perfeitos, (void *)thread_data[i]);
    }

    for (int i = 0; i < num_threads; i++) {
        int *thread_results;
        pthread_join(threads[i], (void **)&thread_results);
        for (int j = 0; j < thread_data[i][1] - thread_data[i][0]; j++) {
            printf("%d\n", thread_results[j]);
        }
        int j = 0;
        counter += j;
        free(thread_results);
    }

    free(vet); // Liberando a memória alocada para vet
    printf("Número de números perfeitos é: %d\n", counter);

    return 0;
}
