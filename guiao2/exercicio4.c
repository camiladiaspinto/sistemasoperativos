#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(int argc, char const *argv[]) {
    int i;
    pid_t pid;
    for(i=1 ;i <11; i++){
        if (!fork()){ //valor diferente de zero, porque se não for zero o processo atual é o pai, senão é o filho
            //printf("O identificador do filho é: %d\n",getpid());
            //printf("O identificador do pai é: %d\n",getppid());
            exit(i);  
        }
        int exit_status;
        while(wait(&exit_status)!=-1){ //verificar que o wait correu bem, se retornar -1 ocorreu um erro 
        printf("Child %d\n",WEXITSTATUS(exit_status));
        }
    }
        return 0;

}
//NOTA: na concorrencia vários processos correm ao mesmo tempo, processo pai está a correr, e os filhos estão a correr ao mesmo tempo. 
//Cada vez que fork() é chamado, um novo processo filho é criado, e ambos, o processo pai e o processo filho,
//começam a executar a partir do ponto em que o fork() foi chamado.