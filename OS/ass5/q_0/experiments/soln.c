#include "buffer.h"
#include "sem_init.h"
#include "producer.h"
#include "consumer.h"
#include <stdio.h> 
#include <stdlib.h> 
#include <sys/types.h> 
#include <sys/ipc.h> 
#include <sys/shm.h> 
#include <sys/wait.h> 
#include <unistd.h> 
#include <sys/sem.h>
#include <signal.h> 

/*
 *  gcc -c sem_init.c buffer.c producer.c consumer.c soln.c
 *  gcc sem_init.o buffer.o producer.o consumer.o soln.o -o ans
 *  ./ans 2 3 5
*/

buffer *qp = NULL;

typedef void (*sighandler_t)(int);

void cleanup() {

    int status; 
    key_t key;
    int id;
    union semun arg;

    key = ftok("/Users/anjishnu/Documents/GitHub/6th_sem/OS/ass5/q_0/q0.c", 1);
    id = shmget(key, sizeof(buffer), IPC_CREAT | 0777);
    shmdt((void*)qp);
    status = shmctl(id, IPC_RMID, NULL);

    key = ftok("/Users/anjishnu/Documents/GitHub/6th_sem/OS/ass5/q_0/q0.c", 2);
    id = semget(key, NO_SEM, IPC_CREAT | 0777);
    status = semctl(id, 0, IPC_RMID, arg);

    key = ftok("/Users/anjishnu/Documents/GitHub/6th_sem/OS/ass5/q_0/q0.c", 3);
    id = semget(key, NO_SEM, IPC_CREAT | 0777);
    status = semctl(id, 0, IPC_RMID, arg);

    key = ftok("/Users/anjishnu/Documents/GitHub/6th_sem/OS/ass5/q_0/q0.c", 4);
    id = semget(key, NO_SEM, IPC_CREAT | 0777);
    status = semctl(id, 0, IPC_RMID, arg);

    status = kill(0, SIGKILL);

    exit(0);
}

int main(int argc, char* argv[])
{
    int producers = atoi(argv[1]);
	int consumers = atoi(argv[2]);
    int size;
    int mutex_id;
    int full_id;
    int empty_id;
    pid_t pid;
    sighandler_t shandler;

    shandler = signal(SIGINT, cleanup);

    size = atoi(argv[3]);
    if(size > MAX){
        size = MAX;
    }

    qp = createbuf(size);
    mutex_id = mutex_init_();
    full_id = full_init_();
    empty_id = empty_init_(size);

    pid = fork();
    if(pid==0){
        producer(producers,mutex_id,full_id,empty_id,qp);
    }
    
    else{
        consumer(consumers,mutex_id,full_id,empty_id,qp);
    }

    return 0;
}