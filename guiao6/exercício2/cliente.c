#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>


int main(int argc, char *argv[]) {
    // Abrir o pipe para escrita
    int fd = open("fifo", O_WRONLY);
    if (fd == -1) {
        perror("Erro ao abrir o pipe para escrita");
        exit(EXIT_FAILURE);
    }

    // Enviar mensagem para o servidor
    ssize_t bytesWritten = write(fd, argv[1], strlen(argv[1]));
    if (bytesWritten == -1) {
        perror("Erro ao escrever no pipe");
        exit(EXIT_FAILURE);
    }

    // Fechar o descritor de arquivo
    close(fd);

    return 0;
}
