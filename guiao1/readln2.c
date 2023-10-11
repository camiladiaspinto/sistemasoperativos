#include <sys/types.h>
#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <fcntl.h> /* O_RDONLY, O_WRONLY, O_CREAT, O_* */
#include "readln.h"

ssize_t readln2(int fd, char* line, size_t size) {
    ssize_t l = 0;
    ssize_t n;

    // Loop para ler múltiplas linhas usando readln
    while ((n = readln(fd, line, size)) > 0) {
        l += n;
        line += n;

        // Se a linha lida não termina com '\n', continua a leitura
        if (line[-1] != '\n') {
            continue;
        }

        // Se chegou aqui, encontrou uma linha completa
        break;
    }

    return l;
}
int main() {
    char buffer[256]; // Ou qualquer tamanho de buffer que você deseje usar
    int fd = open("ficheiro.txt", O_RDONLY); // Substitua "arquivo.txt" pelo nome do seu arquivo

    if (fd == -1) {
        perror("Erro ao abrir o arquivo");
        return 1;
    }

    ssize_t n = readln(fd, buffer, sizeof(buffer));
    close(fd);

    if (n == -1) {
        perror("Erro ao ler do arquivo");
        return 1;
    }

    printf("Linha lida: %s", buffer);
    printf("numero de bytes lidos %zd", n);
    
    return 0;
}