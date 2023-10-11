#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h> 
#include <stdio.h>

int main(int argc, char *argv[]){
    pid_t  pid;
    
    printf("o indentificar do pai é %d e do filho é %d",getppid(),getpid());

    
}