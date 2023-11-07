#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

#define N 5
#define M 100
#define VALOR 42

void ProcuraValor(int matriz[N][M], int linhas, int colunas, int valor, int *results) {
    for (int i = 0; i < linhas; i++) {
        int ocorrencias = 0; // Corrigido de 'ocorrências' para 'ocorrencias'
        for (int j = 0; j < colunas; j++) {
            if (matriz[i][j] == valor) {
                ocorrencias++;
            }
        }
        results[i] = ocorrencias;
    }
}

int main() {
    int matriz[N][M];
    int results[N];
    int pd[2]; // Descritores do pipe

    // Preencha a matriz com o numero 42 em alguns valores da matriz
    matriz[0][23] = 42;
    matriz[2][48] = 42;
    matriz[2][29] = 42;
    matriz[3][39] = 42;

    pipe(pd);

    // Cria um processo filho
    pid_t pid = fork();

    if (pid != 0) {
        // Este é o processo pai
        close(pd[1]); // Fecha o descritor de escrita

        ProcuraValor(matriz, N, M, VALOR, results);

        // O pai lê os resultados dos filhos
        read(pd[0], results, N * sizeof(int));
        close(pd[0]); // Fecha o descritor de leitura

        for (int i = 0; i < N; i++) {
            printf("Resultados na linha %d: %d\n", i, results[i]);
        }
    } else {
        // Este é o processo filho
        close(pd[0]); // Fecha o descritor de leitura

        ProcuraValor(matriz, N, M, VALOR, results);

        // O filho escreve os resultados para o pai
        write(pd[1], results, N * sizeof(int));
        close(pd[1]); // Fecha o descritor de escrita
    }

    return 0;
}
/*
Função ProcuraValor:

    A função ProcuraValor recebe a matriz, o número de linhas e colunas, o valor a ser procurado e um array para armazenar os resultados.
    Itera sobre cada linha da matriz, contando o número de ocorrências do valor especificado naquela linha e armazena esse número no array de resultados.

Função main:

    Cria uma matriz N x M e inicializa algumas posições com o valor VALOR (42).
    Cria um pipe para comunicação entre processos pai e filho.
    Usa fork() para criar um processo filho.
    No processo pai:
        Chama ProcuraValor para contar as ocorrências do valor VALOR em cada linha da matriz.
        Lê os resultados do pipe e imprime o número de ocorrências em cada linha.
    No processo filho:
        Chama ProcuraValor para contar as ocorrências do valor VALOR em cada linha da matriz.
        Escreve os resultados no pipe para o processo pai.
*/

/* Resolução do prof: 
        struct coord *pesquisa(int matriz[M][N], int valor){
        struct coord *resultados=(struct coord)malloc(sizeof(struct coord));
        int fd[2];
        pipe(fd);
        for(int i =0;i=M;i++)
            if(fork==0)
                close(fd[0]);
                for(j=0;j=N;j++){
                    if(matriz[i][j]==valor){
                        struct coord c={i,j}
                        write(fd[1],&c,signal(c));
                    }
                    close(fd[1]);
                    _exit(0);
                }
                close(fd[1]);
                while((n=read(fd[0],&resultados),sizeof(struct coord))>0){
                    nresultados++;
                    resultados=realloc(resultados,sizeof(struct coord *nresultados+1));
                }
                close(fd[0]);
                resultados[nresultados] x=i;
                return resultados;
    }
*/