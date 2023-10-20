#include <stdio.h>
#include <stdlib.h>
#include <time.h>
/*
int verifica_numero_perfeito(int n){
        int soma = 0;
        for(int i = 1; i < n; i++ ){
        if (n % i == 0){
            soma += i;
        }
    }
    
    if (soma == n){
        return n;
    } else{
        return 0;
    }
}
*/

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

    if (soma == n) {
        return n;
    } else {
        return 0;
    }
}

int main() {

    srand(time(NULL));
    int size;
    printf("Digite o tamanho do vetor: ");
    scanf("%d", &size);

    int vet[size], counter = 0;
    
    for(int n = 0; n < size; n++){
        vet[n] = rand() %100;
        printf("%d ", vet[n]);
        if(verifica_numero_perfeito(vet[n])){
            counter += 1;
            printf("%d", vet[n]);
        }

    }

    printf("Numero de numeros perfeitos e: %d\n", counter);
    //for(int i = 0; i < size; i++){
    //    printf("%d\n", vet[i]);
    //}
   
}