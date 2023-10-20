#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

#define MAX_THREADS 4 // Número máximo de threads

int verifica_numero_perfeito(int n) {
    if (n <= 1) {
        return 0; // Números menores ou iguais a 1 não são perfeitos
    }

    int soma = 1; // Inicializado com 1 para incluir o próprio número como divisor

    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            soma += i;
            if (i != n / i) { // Verifica se não é a raiz quadrada para evitar contagem dupla
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

    int vet[size], counter = 0;

    for (int n = 0; n < size; n++) {
        vet[n] = rand() % 10;
    }

    pthread_t threads[MAX_THREADS];
    int thread_data[MAX_THREADS][3]; // Armazena informações de cada thread

    for (int i = 0; i < num_threads; i++) {
        thread_data[i][0] = i * (size / num_threads); // Início do subarray
        thread_data[i][1] = (i == num_threads - 1) ? size : (i + 1) * (size / num_threads); // Fim do subarray
        thread_data[i][2] = vet; // Ponteiro para o vetor
        pthread_create(&threads[i], NULL, verificar_perfeitos, (void *)thread_data[i]);
    }

    for (int i = 0; i < num_threads; i++) {
        int *thread_results;
        pthread_join(threads[i], (void **)&thread_results);
        for (int j = 0; j < thread_data[i][1] - thread_data[i][0]; j++) {
            printf("%d\n", thread_results[j]);
        }
        counter += j;
        free(thread_results);
    }

    printf("Número de números perfeitos é: %d\n", counter);

    return 0;
}
