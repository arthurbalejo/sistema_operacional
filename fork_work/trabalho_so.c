#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>

void criarArvore(int nivel, int maxNivel, int qtdFilhos) {
    if (nivel >= maxNivel) {
        return;
    }

    clock_t inicio = clock(); // Inicia a contagem do tempo

    for (int i = 0; i < qtdFilhos; i++) {
        pid_t filho = fork();

        if (filho == -1) {
            perror("Erro ao criar processo filho");
        } else if (filho == 0) {
            // Código do processo filho
            printf("PID: %d, PPID: %d\n", getpid(), getppid());
            criarArvore(nivel + 1, maxNivel, qtdFilhos);
            exit(0);
        } else {
            // Processo pai
            wait(NULL); // Espera pelo término do processo filho
        }
    }

    clock_t fim = clock(); // Encerra a contagem do tempo
    double tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
    if (nivel == 0) {
        printf("Tempo total de criação da árvore: %.6f segundos\n", tempo);
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Uso: %s <qtd_filhos_nivel1> [qtd_filhos_nivel2 ...]\n", argv[0]);
        exit(1);
    }

    int maxNivel = argc - 1;
    int *qtdFilhos = (int *)malloc(maxNivel * sizeof(int));

    for (int i = 1; i < argc; i++) {
        qtdFilhos[i - 1] = atoi(argv[i]);
        if (qtdFilhos[i - 1] <= 0) {
            fprintf(stderr, "A quantidade de filhos deve ser um número positivo.\n");
            exit(1);
        }
    }

    printf("Nível 0 - Processo raiz com PID %d\n", getpid());
    criarArvore(1, maxNivel, qtdFilhos[0]);

    free(qtdFilhos);

    return 0;
}
