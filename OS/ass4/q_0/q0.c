/*
Let there be 2 processes P1 and P2, where P2 is created by P1. 
That is, P1 is the parent of the child process P2. 
As shown in the following figure P1 and P2 "share" an integer variable n.
P1 creates n and initializes n to -1. 
Subsequently, P1 regularly  "wakes up" (from "sleep") after a 
random amount of time (not more than 2 seconds) checks the value of n and 
if n is not -1 then prints its value and makes it -1 again. 
On the other hand, P2 regularly  "wakes up" (from "sleep") after a random 
amount of time (not more than 2 seconds) checks the value of n and 
if n is -1 then assigns some random value to n and prints the value it has assigned.
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
        int *n;
        int duration;

        sighandler_t shandler;
        shmid =  shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT | 0777);
        if (shmid == -1) { 
                perror("shmget() failed: ");
                exit (1);
        }
        *n=-1;
        shandler =  signal(SIGINT, releaseSHM); 
            switch(pid=fork())
            {
                    
        while(1){
            
                case -1 :   perror("fork() failed: ");
                            exit (1);

                case  0 :   duration = rand()%3;
                            sleep(duration);
                            if(*n==-1){
                                *n = rand()%65536;
                                printf("Child writes %d.\n",*n);
                            }
                            break;

                default :   n = (int*)shmat(shmid, NULL,0);
                            
                            if (n == (void *)-1) { 
                                perror("shmat() failed at parent: ");
                                exit (1);
                            }
                            duration = rand()%3;
                            sleep(duration);
                            if(*n!=-1){
                                printf("Parent reads %d.\n",*n);
                            }
                            

            }
        }
  
}
