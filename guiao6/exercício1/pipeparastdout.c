#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int main(int argc, char *argv[]){
    char buffer[1024];
    int n;
    puts("antes");
    int  pd=open("fifo",O_RDONLY);
    puts("depois");
    if(pd==-1){
        perror("fifo");
        return 1;
    }
    while((n=read(pd,buffer,sizeof(buffer)))>0){
        write(1,buffer,n);
    }
    close(pd);

    return 0;
}