/******************************************************************
 * This is an extension to the earlier assignment where you will support the
 * presence of multiple | (pipe)in the command line.
 * For example when the program is executed as ./a.out cmd1| cmd2 | cmd3 | .......|
 * cmdn, It creates n -1 pipes.cmd1 will write to write end of the first pipe cmd2
 * will read from the first pipe and write to write end of the 2nd pipe. In general
 * cmdi will write to the write end of ith pipe and cmd(i + 1) will write to the
 * write end of the(i + 1) st pipe and so on. Finally cmdn will print its output to
 * the standard output.
 * -------------------------------------------------------------
 * Compile : gcc q1a.c -o outq1a
 * Run : ./outq1a ls wc 
 ******************************************************************/

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
int main(int argc , char *argv[])
{
    int pfd[2];
    int j = 0;
    int n = argc - 1;
    pid_t pids[n];
    pid_t waitRetVal;
    int pipeRetVal;
    int status;
    int prev = 0;
    int current_pipe = 0;


    for(; current_pipe < n; current_pipe++)
    {
        // first create a pipe -> will happen n-1 times
        if(current_pipe != n - 1){
            pipeRetVal = pipe(pfd);
            if (pipeRetVal < 0) {
                printf("Failed to open pipe %d\n", current_pipe);
                exit(EXIT_FAILURE);
            }
        }
        
        // now deal with the two ends of the pipe in a forked child process -> happens n times
        switch (pids[current_pipe] = fork()) {
            case -1 :   printf("Forking child %d failed.\n", current_pipe);
                        exit(EXIT_FAILURE);
                       
            case 0  :   if(current_pipe != 0) // not leftmost pipe
                            dup2(prev , STDIN_FILENO);
            
                        if(current_pipe != n - 1) // not rightmost pipe
                            dup2(pfd[1] , STDOUT_FILENO);      

                        // after having dealt with the two ends, now execute the command 
                        execlp(argv[current_pipe+1] , argv[current_pipe+1] , NULL);
                        printf("Failed to execute command %s\n", argv[current_pipe+1]);
                        exit(EXIT_FAILURE);

            default :   close(prev);
                        close(pfd[1]);
                        prev = pfd[0];
        }

    }

    // close all loose ends
    close(prev);
    close(pfd[0]);
    close(pfd[1]);

    // kill zombie processes
    for(; j < n; j++) {
        waitRetVal = waitpid(pids[j] , &status , 0);
        if (waitRetVal < 0) {
            printf("Failed to wait for process %d\n", j);
            exit(EXIT_FAILURE);
        }
    }
    return 0;
}