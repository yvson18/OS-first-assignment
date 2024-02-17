#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <sys/wait.h>

void consumirCPU(int inicio, int fim) {
    printf("%d executando a consumirCPU\n", getpid());
    int cont = 0;
    for (int i = inicio; i < fim; i++) {
        for (int j = 0; j < 100000; j++) {
            cont++;
        }        
    }
    printf("Finalizei consumirCPU\n");
}


int main(int argc, char const *argv[])
{
    int tempoInicio = time(NULL);
    int contador = 0;
    int qntIteracoes = 100000;
    printf("1-Ola, eu sou o processo %d\n", getpid());
    int pid = fork();
    if(pid<0){
        perror("Erro ao criar o processo\n");
    }
    //Se for o processo filho
    if(pid == 0) {
        consumirCPU(0, qntIteracoes/2);       
    } 
    //Se for o processo pai
    else if (pid > 0) {
        consumirCPU(qntIteracoes/2, qntIteracoes);        
    }
    printf("2-Ola, eu sou o processo %d com contador = %d\n", getpid(), contador);
    wait(NULL);
    int tempoFim = time(NULL);
    printf("Executado em %d seg\n", tempoFim-tempoInicio);
    return 0;
}
