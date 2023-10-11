#include <sys/types.h>
#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <fcntl.h> /* O_RDONLY, O_WRONLY, O_CREAT, O_* */
#include <stdio.h>
#include <stdlib.h>
ssize_t readln(int fd, char* lines, size_t size){
    int n;
    ssize_t l = 0;
    

    while (l < size - 1 && (n = read(fd, &lines[l], 1)) > 0) {
        l++;
    }
    return n==-1 ? -1 :l;
}

// por exemplo, a função quando tem 'ola\n' devia retornar 4 bytes e retorna 3
//quando l for diferente de 0 

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