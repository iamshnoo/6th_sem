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

int main()
{
    int shmid;
	key_t key;
    int duration;
    time_t t;
    sighandler_t shandler;

    srand((unsigned) time(&t));
    duration = rand()%3;

    shandler = signal(SIGINT, releaseSHM);
    key = ftok("shmq3",65);
    shmid = shmget(key, sizeof(struct data), IPC_CREAT | 0666);
    if (shmid == -1) {
            perror("shmget() failed.\n");
            exit(1);
    }

    printf("Child [test1] has received a shared memory of (1 pid, 1 integer, 1 character). \n");
    sleep(1);
    shmptr = (struct data*) shmat (shmid, NULL, 0);
    if((int)shmptr == -1){
            perror("shmat() failed.\n");
            exit(1);
    }
    printf("Child [test1] has attached shared memory to its address space. \n");
    sleep(1);

    while(1)
    {
        if (shmptr->c == 'n')
        {
                printf("Child's sleep-write cycle : ");
                shmptr->pid = getpid();
                shmptr->n = rand()%1024;
                printf("Child [PID : %d] writes %d.\n", shmptr->pid, shmptr->n);
                shmptr->c = 'y';
        }
        sleep(duration);
    }

    exit(0);
}