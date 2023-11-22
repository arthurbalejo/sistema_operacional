#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define MAX_LINHAS_ESPERA 10

// Definindo estrutura para representar o call center
typedef struct {
    int linhas;
    int em_atendimento;
    int em_espera;
    sem_t mutex;
    sem_t cliente;
    sem_t atendente;
} CallCenter;

// Função para simular a ligação do cliente
void ligar(CallCenter *callCenter, int id_cliente) {
    printf("Cliente %d esta ligando! Havia %d chamadas em espera\n", id_cliente, callCenter->em_espera);
    usleep(rand() % 1000000); // Simula a duração da chamada
}

// Função para simular o atendimento do cliente
void atender(CallCenter *callCenter, int id_cliente) {
    sem_wait(&callCenter->atendente);
    callCenter->em_atendimento = id_cliente;
    printf("Cliente %d esta sendo atendido! Ha %d chamadas em espera\n", id_cliente, callCenter->em_espera);
    usleep(rand() % 1000000); // Simula a duração do atendimento
    callCenter->em_atendimento = 0;
    sem_post(&callCenter->atendente);
}

// Função principal para o cliente
void *cliente(void *arg) {
    CallCenter *callCenter = (CallCenter *)arg;
    int id_cliente = rand(); // Identificador único do cliente

    sem_wait(&callCenter->mutex);

    if (callCenter->em_espera < MAX_LINHAS_ESPERA) {
        callCenter->em_espera++;
        sem_post(&callCenter->mutex);

        sem_post(&callCenter->cliente);
        ligar(callCenter, id_cliente);

        sem_wait(&callCenter->atendente);
        callCenter->em_espera--;
        atender(callCenter, id_cliente);
        sem_post(&callCenter->atendente);
    } else {
        printf("Cliente %d não consegue realizar a chamada. Todas as linhas ocupadas\n", id_cliente);
        sem_post(&callCenter->mutex);
    }

    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Uso: %s <numero_de_linhas>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int num_linhas = atoi(argv[1]);

    if (num_linhas <= 0) {
        printf("O número de linhas deve ser um inteiro positivo.\n");
        exit(EXIT_FAILURE);
    }

    CallCenter callCenter;
    callCenter.linhas = num_linhas;
    callCenter.em_atendimento = 0;
    callCenter.em_espera = 0;

    // Inicialização dos semáforos
    sem_init(&callCenter.mutex, 0, 1);
    sem_init(&callCenter.cliente, 0, 0);
    sem_init(&callCenter.atendente, 0, 1);

    pthread_t tid;

    printf("----------------------------------------------------------------------------------\n");
    printf(" Call Center do Paulo (numero de linhas de espera: %d)\n", MAX_LINHAS_ESPERA);
    printf("----------------------------------------------------------------------------------\n");

    // Inicialização da thread do atendente
    pthread_create(&tid, NULL, cliente, &callCenter);

    // Loop para gerar clientes continuamente
    while (1) {
        usleep(rand() % 500000); // Intervalo entre a geração de clientes
        pthread_create(&tid, NULL, cliente, &callCenter);
    }

    // Aguarda a finalização da thread do atendente
    pthread_join(tid, NULL);

    // Destroi os semáforos
    sem_destroy(&callCenter.mutex);
    sem_destroy(&callCenter.cliente);
    sem_destroy(&callCenter.atendente);

    return 0;
}
