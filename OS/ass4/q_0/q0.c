/******************************************************************
 * Let there be 2 processes P1 and P2, where P2 is created by P1.
 * That is, P1 is the parent of the child process P2.
 * As shown in the following figure P1 and P2 "share" an integer variable n.
 * P1 creates n and initializes n to -1.
 * Subsequently, P1 regularly  "wakes up" (from "sleep") after a
 * random amount of duration (not more than 2 seconds) checks the value of n and
 * if n is not -1 then prints its value and makes it -1 again.
 * On the other hand, P2 regularly  "wakes up" (from "sleep") after a random
 * amount of duration (not more than 2 seconds) checks the value of n and
 * if n is -1 then assigns some random value to n and prints the value it has assigned.
 * If the program execution is terminated by the user (by pressing  Ctrl-C),
 * both P1 and P2 should terminate and the allocated shared memory should be released.
 * -------------------------------------------------------------
 * Compile : gcc q0.c -o q0
 * Run : ./q0 (Hit Ctrl+C to stop execution.)
 ******************************************************************/

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <signal.h>
#include <errno.h>
#include <stdlib.h>
#include <time.h>

int shmid;
int *shmptr;
typedef void (*sighandler_t)(int);

/*fprintf is not async-signal-safe.  See manpage(7) signal-safety.*/
void releaseSHM() {
        int status;
        shmdt((void*)shmptr);
        status = shmctl(shmid, IPC_RMID, NULL);
        status = kill(0, SIGKILL);
        exit(0);
}

int main(int argc, char* argv[]){
        int status;
        sighandler_t shandler;
        pid_t pid;
        int duration;
        time_t t;

        srand((unsigned) time(&t));
        duration = rand()%3;
        shandler = signal(SIGINT, releaseSHM);
        shmid = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT | 0666);
        if (shmid == -1) {
                perror("shmget() failed.\n");
                exit(1);
        }
        printf("Parent has received a shared memory of 1 integer. \n");
        sleep(1);
        shmptr = (int*) shmat (shmid, NULL, 0);
        if((int)shmptr == -1){
                perror("shmat() failed.\n");
                exit(1);
        }
        printf("Parent has attached shared memory to its address space. \n");
        sleep(1);
        *shmptr = -1;
        printf("Parent has written -1 initially to shared memory. \n");
        printf("Now parent will attempt to fork a child process. \n");
        sleep(1);

        switch(pid = fork()){
        case -1 :       perror("fork() failed.\n");
                        exit(1);

        case 0  :       printf("Fork was successful.\n");
                        while(1)
                        {
                                if(*shmptr == -1)
                                {
                                        printf("Child's sleep-write cycle : ");
                                        *shmptr = rand()%1024;
                                        printf("Child writes %d\n",*shmptr);
                                }
                                sleep(duration);
                        }
                        _exit(0);

        default :       while(1)
                        {
                                if(*shmptr !=-1)
                                {
                                        printf("Parent's sleep-read cycle : ");
                                        printf("Parent reads %d\n", *shmptr);
                                        *shmptr = -1;
                                }
                                sleep(duration);
                        }

                        wait(&status);
                        printf("Parent has detected the completion of its child process. \n");
                        exit(0);
        }
}
