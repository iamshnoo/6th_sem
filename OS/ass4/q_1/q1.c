/*
This is a simple extension of the previous assignment titled " Inter-Process Communication - 
A simple assignment on shared memory involving 2 processes and a shared integer". 
You may make a copy of the file you have created there and start working on the copy for this assignment.

Let there be 2 processes P1 and P2, where P2 is created by P1. 
That is, P1 is the parent of the child process P2. 
As shown in the following figure P1 and P2 "share" an integer variable n and a character variable c 
(which works as a flag).
P1 creates n and c, and initializes c to 'n'. 
Subsequently, P1 regularly  "wakes up" (from "sleep") after a random amount of 
time (not more than 2 seconds) checks the value of c and if c is 'y'  
then prints the value of n  and makes c to be 'n' again. 

On the other hand, P2 regularly  "wakes up" (from "sleep") after a random amount of 
time (not more than 2 seconds) checks the value of c and if c is 'n' then assigns 
some random value to n, prints that value, and makes c to be 'y'.

If the program execution is terminated by the user (by pressing  Ctrl-C), 
both P1 and P2 should terminate and the allocated shared memory should be released.
*/

#include <stdio.h>
#include <unistd.h> 
#include <sys/wait.h> 
#include <sys/types.h> 
#include <sys/ipc.h> 
#include <sys/shm.h> 
#include <signal.h> 
#include <errno.h> 
#include <stdlib.h>

int shmid; 
typedef void (*sighandler_t)(int);

void releaseSHM(int signum) {
        int status;
        status = shmctl(shmid, IPC_RMID, NULL); 
        if (status == 0) {
                fprintf(stderr, "Remove shared memory with id = %d.\n", shmid);
        } else if (status == -1) {
                fprintf(stderr, "Cannot remove shared memory with id = %d.\n", shmid);
        } else {
                fprintf(stderr, "shmctl() returned wrong value while removing shared memory with id = %d.\n", shmid);
        }

        status = kill(0, SIGKILL);
        if (status == 0) {
                fprintf(stderr, "kill susccesful.\n"); 
        } else if (status == -1) {
                perror("kill failed.\n");
                fprintf(stderr, "Cannot remove shared memory with id = %d.\n", shmid);
        } else {
                fprintf(stderr, "kill(2) returned wrong value.\n");
        }
        exit(signum);
}
                                                                                                                         
int main() {
        int status;
        pid_t pid=0;
        pid_t p1=0;
        int *n;
        char *c;
        int duration = rand() % 3;

        sighandler_t shandler;
        shmid =  shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT | 0777);
        if (shmid == -1) { 
                perror("shmget() failed: ");
                exit (1);
        }

        while(1){
            shandler =  signal(SIGINT, releaseSHM); 
            switch(pid=fork()){
                case -1 :   perror("fork() failed: ");
                            exit (1);

                case  0 :   sleep(duration);
                            if(*c=='n'){
                                *n = rand()%65536;
                                printf("Child writes %d in n.\n",*n);
                                *c = 'y';
                            }
                            break;

                default :   n = (int*)shmat(shmid, NULL,0);
                            c = (char*)shmat(shmid, NULL,0);
                            *n = -1;
                            *c = 'n';
                            if (n == (void *)-1 || c == (void *)-1) { 
                                perror("shmat() failed at parent: ");
                                exit (1);
                            }
                            sleep(duration);
                            if(*c=='y'){
                                printf("Parent reads n as %d.\n",*n);
                                *c = 'n';
                            }

            }
        }
  
}