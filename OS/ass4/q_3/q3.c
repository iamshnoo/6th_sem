/*****************************************************************
 * This assignment is exactly similar to the previous assignment titled "Inter-Process Communication -
 * An assignment on shared memory involving arbitrary number of processes."
 *
 * Let there be a process P0  and  n number other processes  P1, P2, ..., Pn,
 * These processes are independently created by independent execution of one or
 * more executable files. As shown in the following figure,
 * all these processes  "share" integer variables n and  pid, and a character variable c (which works as a flag).
 *
 * P0 creates n, pid, and c; and initializes c to 'n'.
 * Subsequently, P0 regularly  "wakes up" (from "sleep") after a random amount of
 * time (not more than 2 seconds) checks the value of c and if c is 'y'
 * then prints the value of n (along with the corresponding pid) and makes c to be 'n' again.
 *
 * On the other hand, every Pi, 1≤ i ≤n,
 * regularly  "wakes up" (from "sleep") after a random amount of time (not more than 2 seconds)
 * checks the value of c and if c is 'n' then assigns some random value to n,
 * along with its process id to pid, prints that value along with its own process id, and makes c to be 'y'.
 *
 * If the program execution is terminated by the user (by pressing  Ctrl-C),
 * P0 and Pi, 1≤ i ≤ n should terminate and the allocated shared memory should be released.
 * -------------------------------------------------------------
 * Compile : gcc q3.c -o q3
 * Run : ./q3 3 ./test1
 *****************************************************************/

/*
 * Note : I am taking the input value of n from cmdline args.
 *        Compile the program using gcc q3.c -o q3
 *        Run the program using ./q3 3 ./test1(will give n=3 and
 *                                         then will run test1 executable from children)
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
#include <time.h>

int shmid;
struct data *shmptr;

struct data {
        pid_t pid;
        int n;
        char c;
};

typedef void (*sighandler_t)(int);

/* fprintf is not async-signal-safe.  See manpage(7) signal-safety. */
void releaseSHM() {
        int status;
        shmdt((void*)shmptr);
        status = shmctl(shmid, IPC_RMID, NULL);
        status = kill(0, SIGKILL);
        exit(0);
}

int main(int argc, char* argv[]){
        int i;
        int status;
        sighandler_t shandler;
        pid_t pid;
        int duration;
        time_t t;
        key_t key;
        int num_children = atoi(argv[1]);

        srand((unsigned) time(&t));
        duration = rand()%3;
        shandler = signal(SIGINT, releaseSHM);
        key = ftok("shmq3",65);
        shmid = shmget(key, sizeof(struct data), IPC_CREAT | 0666);
        if (shmid == -1) {
                perror("shmget() failed.\n");
                exit(1);
        }
        printf("Parent has received a shared memory of (1 pid, 1 integer, 1 character). \n");
        sleep(1);
        shmptr = (struct data*) shmat (shmid, NULL, 0);
        if((int)shmptr == -1){
                perror("shmat() failed.\n");
                exit(1);
        }
        printf("Parent has attached shared memory to its address space. \n");
        sleep(1);
        shmptr->pid = getpid();
        shmptr->n = -1;
        shmptr->c = 'n';
        printf("Parent has written (Parent_PID,-1,n) initially to shared memory. \n");
        printf("Now parent will attempt to fork %d child processes. \n",num_children);
        sleep(1);

        for(i=0; i<num_children; i++){
                switch(pid = fork()){
                case -1 :       perror("fork() failed.\n");
                                exit(1);

                case 0  :       execlp(argv[2],argv[2],NULL);
                                exit(1);
                default :       break;
                }
        }

        while(1)
        {
                if (shmptr->c == 'y')
                {
                        printf("Parent's sleep-read cycle : ");
                        shmptr->pid = getpid();
                        printf("Parent[PID : %d] reads  %d.\n", shmptr->pid, shmptr->n);
                        shmptr->c = 'n';
                }
                sleep(duration);
        }

        wait(&status);
        printf("Parent has detected the completion of one child process. \n");
        exit(0);
}