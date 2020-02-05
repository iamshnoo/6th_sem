/*
This is an extension to the earlier assignment where you will support the
presence of multiple | (pipe)in the command line.
For example when the program is executed as ./a.out cmd1| cmd2 | cmd3 | .......|
cmdn, It creates n -1 pipes.cmd1 will write to write end of the first pipe cmd2
will read from the first pipe and write to write end of the 2nd pipe. In general
cmdi will write to the write end of ith pipe and cmd(i + 1) will write to the
write end of the(i + 1) st pipe and so on. Finally cmdn will print its output to
the standard output.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

/*******************************
 * Credits : For some error checking code portions, 
 * I have used stackoverflow suggestions across multiple answers.
 * *****************************/ 
int main(int argc, char *argv[]) { 

    int lpipe[2], rpipe[2];
    int i,j;
    int n=argc;
    pid_t pids[n];
    pid_t waitRetVal;
    int pipeRetVal;

    pipeRetVal = pipe(rpipe);
    if (pipeRetVal < 0) {
        printf("Failed to open pipe 0\n");
        exit(EXIT_FAILURE);
    }

    // leftmost pipe
    switch (pids[0] = fork()) {
            case -1 :   printf("Forking child 1 failed.\n");
                        exit(EXIT_FAILURE);

            
            case 0  :   close(rpipe[0]);
                        dup2(rpipe[1],STDOUT_FILENO);
                        close(rpipe[1]);
                        execlp(argv[1] , argv[1] , NULL);
                        printf("Failed to execute command %s\n", argv[1]);
                        exit(EXIT_FAILURE);

            default :   lpipe[0] = rpipe[0];  
                        lpipe[1] = rpipe[1];
    
    }
    
    // all the n-2 pipes inbetween
    for(i=2;i<n-1;i++) {

        pipeRetVal = pipe(rpipe);
        if (pipeRetVal < 0) {
            printf("Failed to open pipe %d\n", i-1);
            exit(EXIT_FAILURE);
        }

        switch (pids[i-1] = fork()) {
            case -1 :   printf("Forking child %d failed.\n",i);
                        exit(EXIT_FAILURE);

            
            case 0  :   close(lpipe[1]);
                        dup2(lpipe[0],STDIN_FILENO);
                        close(lpipe[0]);  
                        close(rpipe[0]);
                        dup2(rpipe[1],STDOUT_FILENO);
                        close(rpipe[1]);
                        execlp(argv[i] , argv[i] , NULL);
                        printf("Failed to execute command %s\n", argv[i]);
                        exit(EXIT_FAILURE);

            default :   close(lpipe[0]);
                        close(lpipe[1]);
                        lpipe[0] = rpipe[0];
                        lpipe[1] = rpipe[1];
    
        }

    }

    // rightmost pipe
    switch (pids[n-1] = fork()) {
            case -1 :   printf("Forking child n failed.\n");
                        exit(EXIT_FAILURE);

            
            case 0  :   close(lpipe[1]);
                        dup2(lpipe[0],STDIN_FILENO);
                        close(lpipe[0]);         
                        execlp(argv[n-1] , argv[n-1] , NULL);
                        printf("Failed to execute command %s\n", argv[n-1]);
                        exit(EXIT_FAILURE);

            default :   close(lpipe[0]);
                        close(lpipe[1]);
                        close(rpipe[0]);
                        close(rpipe[1]);
                        wait(0);
    
    }

    return 0;
}