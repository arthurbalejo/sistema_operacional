#include <stdio.h>
//soma de valor absuluto
//funcao verifica se e negativo
//funcao soma valores

int main(void){
    int valorAbsoluto();
    int soma();

    int x = 4, y = -2;

    int soma = soma(x, y);

    printf("O valor da soma dos numeros absolutos e:%i", soma);

    return 0;
}

int valorAbsoluto(int n){

    if (n < 0){
        n *= -1;
    }else
    n = n;

    return n;
}

int soma(int x, int y){
    int soma;
    soma = x + y;

    return soma;
}
