#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <sys/wait.h>

int main(int argc, char const *argv[]){
    int n  = atoi(argv[1]);
    char *command[] = {"../bin/subroutineExec", NULL}; 
        
    printf("Number of process desired: %d\n", n); 
 
    for(int i = 0; i < n; i++){
        int pid = fork();
        if(pid<0){
            perror("Error during the process creation!\n");
        }    
        
        if(pid == 0) {
            // Subroutine has taken control of this child process.
            int statusCode = execvp(command[0], command);
            if (statusCode == -1) {
                printf("Terminated Incorrectly!\n");
                return 1;
            }          
        } 
    }
    
    printf("Main process finished successfully!\n");

    return 0;
}