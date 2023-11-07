#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h> 
#include <stdio.h>

int main(int argc, char *argv[]){
    int fd[2];
    int valor=1;
    int valorrecebido;

    if(pipe(fd)==-1){
        perror("erros");
        _exit(1);
    }
    pid_t pid=fork();
    if(pid == 0){

        close(fd[0]); //close pipe de leitura 
        sleep(5);
        write(fd[1],&valor,sizeof(valor));
        close(fd[1]);
        printf("valor enviado %d\n",valor);

    }
    else{
        close(fd[1]);
        read(fd[0],&valorrecebido,sizeof(valorrecebido)); 
        close(fd[0]);
        printf("valor recebido %d\n",valorrecebido);
        _exit(0);
        
    }
    return 0;
}