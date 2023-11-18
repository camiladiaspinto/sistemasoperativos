#include <stdlib.h>
#include <unistd.h>

int main(int argc, char const *argv[]) {
    __pid_t pid;
    pid=fork();
    if(pid==0){
            execlp("ls", "-l", NULL);

    } else{
        wait(NULL);
    }
    return 0;
}