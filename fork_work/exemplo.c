#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(){
    int entrada, estado, fb0, fb1, fbn, contFib = 0, divide, primo = 0, divisor, contPrimo = 0;

    printf("Digite o numero de elementos a serem impressos: ");
    scanf("%d", &entrada);

    int pid = fork();

    if (pid < 0){
        fprintf(stderr, "fork falhou\n");
        exit(-1);
    }else if (pid != 0){
        printf("Sou o processo PAI (pid = %d , ppid = %d). Vou esperar meu filho e depois gerar os primos.\n", getpid(), getppid());
        wait(&estado);
        printf("\nSou o processo PAI (pid = %d , ppid = %d), esperei meu filho. Vou gerar os primos:\n", getpid(), getppid());
        do {
            divide = 0;
            primo++;
            for(divisor = 1;divisor < primo && divide <= 1; divisor++){
                if(primo % divisor == 0)
                    divide++;
            }
            if(divide == 1){
                printf("%d ", primo);
                contPrimo++;            
            }
        } while(contPrimo < entrada);
        printf("\nSou o processo PAI (pid = %d , ppid = %d) e terminei.\n", getpid(), getppid());
    }else if (pid == 0){
        printf("Sou o processo FILHO (pid = %d , ppid = %d). Digite o primeiro termo: ", getpid(), getppid());
        scanf("%i", &fb0);
        printf("Sou o processo FILHO (pid = %d , ppid = %d). Digite o segundo termo: ", getpid(), getppid());
        scanf("%i", &fb1);
        printf("Sou o processo FILHO (pid = %d , ppid = %d). Vou gerar a serie:\n", getpid(), getppid());
        printf("%d %d ", fb0, fb1);
        while(contFib < entrada) {
            fbn = fb0 + fb1;
            fb0 = fb1;
            fb1 = fbn;
            printf("%d ", fbn);
            contFib++;
        }
        printf("\nSou o processo FILHO (pid = %d , ppid = %d) e terminei.", getpid(), getppid());
    }
    exit(0);
}