#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

#define READ_END 0
#define WRITE_END 1

int received = 0;

// Função de tratamento de sinal
void handle_signal(int signo) {
    if (signo == SIGUSR1) {
        received = 1;
    }
}

int main() {
    int pipe_fd[2]; // Descritores do pipe
    pid_t pid;      // PID do processo filho

    // Cria o pipe anônimo
    if (pipe(pipe_fd) == -1) {
        perror("Erro ao criar o pipe");
        exit(EXIT_FAILURE);
    }

    // Registra o manipulador de sinal
    signal(SIGUSR1, handle_signal);

    // Cria um processo filho
    pid = fork();

    if (pid < 0) {
        perror("Erro ao criar o processo filho");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) { // Processo filho
        // Fecha o descritor de escrita, pois o filho só irá ler
        close(pipe_fd[1]);

        // Redireciona o standard input para o descritor de leitura do pipe
        dup2(pipe_fd[0], STDIN_FILENO);

        // Fecha o descritor de leitura, pois o filho já redirecionou o standard input
        close(pipe_fd[0]);

        // Executa o comando "wc"
        execlp("wc", "wc", (char *)NULL);

        // Em caso de falha na execução do comando "wc"
        perror("Erro ao executar o comando wc");
        exit(EXIT_FAILURE);
    } else { // Processo pai
        // Fecha o descritor de leitura, pois o pai só irá escrever
        close(pipe_fd[0]);

        // Envia sequência de linhas de texto introduzidas pelo utilizador para o filho
        printf("Introduza linhas de texto (Ctrl+D para terminar):\n");
        char buffer[1024];
        ssize_t bytesRead;

        while ((bytesRead = read(STDIN_FILENO, buffer, sizeof(buffer))) > 0) {
            write(pipe_fd[1], buffer, bytesRead);
        }

        // Fecha o descritor de escrita para indicar o fim do arquivo para o filho
        close(pipe_fd[1]);

        // Aguarda o processo filho terminar
        wait(NULL);

        // Se o filho recebeu os dados, imprime uma mensagem
        if (received) {
            printf("O filho recebeu os dados com sucesso.\n");
        } else {
            printf("O filho não recebeu os dados.\n");
        }
    }

    return 0;
}
