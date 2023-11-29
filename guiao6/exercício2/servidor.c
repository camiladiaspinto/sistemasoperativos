#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>



int main() {
   
    if(mkfifo("fifo",0666)==-1){
        perror("Erro ao criar fifo");
        return 1;
    }

    int fd = open("fifo", O_RDONLY);
    if (fd == -1) {
        perror("Erro ao abrir o pipe para leitura");
        exit(EXIT_FAILURE);
    }

    char buffer[100];
    ssize_t bytesRead;

    while ((bytesRead = read(fd, buffer, sizeof(buffer))) > 0) {
        int logFile = open("log.txt", O_WRONLY | O_CREAT ,0644);
        if (logFile == -1) {
            perror("Erro ao abrir o arquivo de log");
            exit(EXIT_FAILURE);
        }

        // Escrever no log
        write(logFile, buffer, bytesRead);

        close(logFile);
    }

    close(fd);
    unlink("fifo");
    return 0;
}
