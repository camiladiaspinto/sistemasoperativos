#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(int argc, char const *argv[]) {
    int i;
    pid_t pid;
    for(i=1 ;i <11; i++){
        if (fork()==0){ //cria processo filho a partir do pai
            printf("O identificador do filho é: %d\n",getpid());
            printf("O identificador do pai é: %d\n",getppid());
            exit(i);  
        }
        else{
        //pai espera pelo filho
        int exit_status;
        wait(&exit_status);
        printf("%d\n",WEXITSTATUS(exit_status));
        }
    }
        return 0;

}

//Notas: processo sequencial vão todos correr apenas num processo, criamos o processo filho, e o pai espera pelo processo filho para terminar e devolver o codigo da ordem

