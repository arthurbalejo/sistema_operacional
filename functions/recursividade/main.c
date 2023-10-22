#include <stdio.h>
//soma de valor absuluto
//funcao verifica se e negativo
//funcao soma valores
int valorAbsoluto(int n);
int soma(int x, int y);

int main(void){
    int x = 4, y = -2;

    printf("O valor da soma dos numeros absolutos e:%i\n", soma(x, y));

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
    
    x = valorAbsoluto(x);
    y = valorAbsoluto(y);
    int soma = x + y;

    return soma;
}
