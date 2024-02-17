#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <sys/wait.h>

void CPUConsuming(int inicio, int fim) {
    int cont = 0;
    for (int i = inicio; i < fim; i++) {
        for (int j = 0; j < 100000; j++) {
            cont++;
        }        
    }
    printf("Finished consumirCPU\n");
}

int main(int argc, char const *argv[]){
    
    int n  = atoi(argv[1]);
    
    printf("Number of process desired: %d\n", n); 
    
    int pid;

    for(int i = 0; i < n; i++){
        pid = fork();
        if(pid<0){
            perror("Error during the process creation!\n");
        }    
        
        if(pid == 0) {
            printf("Process %d started consuming CPU...\n", getpid());
            CPUConsuming(0, 100000000);  
        } 
    }
    
    int status;
    pid_t child_pid;
    
    while ((child_pid = wait(&status)) > 0) {
        printf("Child process %d finished!\n", child_pid);
    }
    
    printf("Main process finished successfully!\n");
    
    return 0;
}