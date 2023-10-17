#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char* argv[]) {

    int id = fork();
    

    if(id != 0){
        fork();
    }
    
    printf("hello worl\n");
    //printf("Hello worl form id: %d\n", id);

    /*if (id == 0){
        printf("Hello from child process\n");
    }else{
        printf("Hello from de main process\n");
    }
    */
    return 0;
}