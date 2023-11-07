#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    int pd[2]; // Descritores do pipe
    int valor_enviado = 1;
    int valor_recebido;

    pipe(pd);

    // Cria um processo filho
    pid_t pid = fork();

    if (pid != 0) {
        // Este é o processo pai
        close(pd[1]); // Fecha o descritor de escrita

        while (1) {
            // O pai lê o valor do pipe
            ssize_t bytes_read = read(pd[0], &valor_recebido, sizeof(valor_recebido));
            if (bytes_read == 0) {
                // Fim de arquivo, nenhum processo tem o descritor de escrita aberto
                printf("Fim");
                break;
            }
            printf("Pai: Valor recebido = %d\n", valor_recebido);

            // Simulando um atraso
            sleep(5);
        }
        close(pd[0]); // Fecha o descritor de leitura
        _exit(0);
    }
    // Este é o processo filho
    close(pd[0]); // Fecha o descritor de leitura

    for (int i = 0; i < 2; i++) {
        // O filho escreve o valor no pipe
        write(pd[1], &valor_enviado, sizeof(valor_enviado));
        printf("Filho: Valor enviado = %d\n", valor_enviado);
    }
    close(pd[1]); // Fecha o descritor de escrita

    return 0;
}