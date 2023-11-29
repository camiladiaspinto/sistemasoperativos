#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>


int main(int argc, char *argv[]){

    if(mkfifo("fifo",0666)==-1){
        perror("Erro ao criar fifo");
        return 1;
    }
    return 0;
}