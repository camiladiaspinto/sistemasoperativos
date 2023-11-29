#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]){
    char buffer[1024];
    int n;
    puts("antes");
    int  pd=open("fifo",O_WRONLY);
    puts("depois");
    if(pd==-1){
        perror("fifo");
        return 1;
    }
    while((n=read(0,buffer,sizeof(buffer)))> 0){
        write(pd,buffer,n);
    }
    close(pd);
    return 0;
}