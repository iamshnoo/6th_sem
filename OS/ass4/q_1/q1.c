/******************************************************************
 * This is a simple extension of the previous assignment titled " Inter-Process Communication -
 * A simple assignment on shared memory involving 2 processes and a shared integer".
 * You may make a copy of the file you have created there and start working on the copy for this assignment.
 *
 * Let there be 2 processes P1 and P2, where P2 is created by P1.
 * That is, P1 is the parent of the child process P2.
 * As shown in the following figure P1 and P2 "share" an integer variable n and a character variable c
 * (which works as a flag).
 * P1 creates n and c, and initializes c to 'n'.
 * Subsequently, P1 regularly  "wakes up" (from "sleep") after a random amount of
 * time (not more than 2 seconds) checks the value of c and if c is 'y'
 * then prints the value of n  and makes c to be 'n' again.
 *
 * On the other hand, P2 regularly  "wakes up" (from "sleep") after a random amount of
 * time (not more than 2 seconds) checks the value of c and if c is 'n' then assigns
 * some random value to n, prints that value, and makes c to be 'y'.
 *
 * If the program execution is terminated by the user (by pressing  Ctrl-C),
 * both P1 and P2 should terminate and the allocated shared memory should be released.
 * -------------------------------------------------------------
 * Compile : gcc q1.c -o q1
 * Run : ./q1 (Hit Ctrl+C to stop execution.)
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
struct data *shmptr;

struct data {
        int n;
        char c;
};

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
        shmid = shmget(IPC_PRIVATE, sizeof(struct data), IPC_CREAT | 0666);
        if (shmid == -1) {
                perror("shmget() failed.\n");
                exit(1);
        }
        printf("Parent has received a shared memory of (1 integer, 1 character). \n");
        sleep(1);
        shmptr = (struct data*) shmat (shmid, NULL, 0);
        if((int)shmptr == -1){
                perror("shmat() failed.\n");
                exit(1);
        }
        printf("Parent has attached shared memory to its address space. \n");
        sleep(1);
        shmptr->n = -1;
        shmptr->c = 'n';
        printf("Parent has written (-1,n) initially to shared memory. \n");
        printf("Now parent will attempt to fork a child process. \n");
        sleep(1);

        switch(pid = fork()){
        case -1 :       perror("fork() failed.\n");
                        exit(1);

        case 0  :       printf("Fork was successful.\n");
                        while(1)
                        {
                                if (shmptr->c == 'n')
                                {
                                        printf("Child's sleep-write cycle : ");
                                        shmptr->n = rand()%1024;
                                        printf("Child writes %d.\n", shmptr->n);
                                        shmptr->c = 'y';
                                }
                                sleep(duration);
                        }
                        _exit(0);

        default :       while(1)
                        {
                                if (shmptr->c == 'y')
                                {
                                        printf("Parent's sleep-read cycle : ");
                                        printf("Parent reads %d.\n", shmptr->n);
                                        shmptr->c = 'n';
                                }
                                sleep(duration);
                        }

                        wait(&status);
                        printf("Parent has detected the completion of its child process. \n");
                        exit(0);
        }
}