/*****************************************************************
 * There is a fixed size buffer and there are two types of processes;
 * producer process and consumer processes. The producer processes produce
 * items and enters them into the buffer and the consumer processes remove
 * the items from the buffer and consume them.
 *
 * A producer should not produce items into the buffer when the consumer
 * is consuming an item from the buffer and vice versa.
 * So the buffer should only be accessed by the producer or consumer at a time.
 * The producer processes should also stop producing items if the buffer is
 * full and the consumer process stops consuming items if the buffer is empty.
 * Write a program to achieve the above-mentioned synchronization using semaphore.
 *
 * Your program should be well indented and documented.
 * -------------------------------------------------------------
 * Compile : gcc q0.c -o q0
 * Run : ./q0 2 3 5
 *****************************************************************/

/*
 * Instructions for running file :
 * -------------------------------
 * gcc q0.c -o q0
 * ./q0 2 3 5 will give 2 producers, 3 consumers and a buffer size of 5.
 * Max buffer size is limited to 5.
 * Hit Ctrl+C to kill all processes and remove all semaphores and shared memory.
 * Remember to change the filepath specified in ftok() calls before compiling on
 * a different system.
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/sem.h>
#include <signal.h>

#define NO_SEM	1
#define wait(s) semop(s, &Pop, 1);   // wait operation
#define sig(s) semop(s, &Vop, 1); // signal operation
#define MAX 5

static struct sembuf Pop = {0,-1,SEM_UNDO};
static struct sembuf Vop = {0, 1,SEM_UNDO};

typedef struct{
    int data[MAX];
    int front, rear, count;
} buffer;

buffer *qp;

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
	int status;
    key_t mutex_key;
    int mutex_id;
    key_t full_key;
    int full_id;
    key_t empty_key;
    int empty_id;
    pid_t pid;
    key_t buf_key;
    buffer *qp;
    int shmID;
    sighandler_t shandler;
    union semun setvalArg;

    size = atoi(argv[3]);
    if(size > MAX){
        size = MAX;
    }

    shandler = signal(SIGINT, cleanup);
    buf_key = ftok("/Users/anjishnu/Documents/GitHub/6th_sem/OS/ass5/q_0/q0.c", 1);
    shmID = shmget(buf_key, sizeof(buffer), IPC_CREAT | 0777);
    qp = (buffer*) shmat(shmID, 0, 777);
    int i;
    for (i=0; i<size; i++){
        qp->data[i] = 0x00;
    }
    qp->front = 0;
    qp->rear = -1;
    qp->count = 0;

	mutex_key = ftok("/Users/anjishnu/Documents/GitHub/6th_sem/OS/ass5/q_0/q0.c", 2);
	mutex_id = semget(mutex_key, NO_SEM, IPC_CREAT | 0777);
	setvalArg.val = 1;
    status = semctl(mutex_id, 0, SETVAL, setvalArg); // mutex = 1

    full_key = ftok("/Users/anjishnu/Documents/GitHub/6th_sem/OS/ass5/q_0/q0.c", 3);
    full_id = semget(full_key, NO_SEM, IPC_CREAT | 0777);
	setvalArg.val = 0;
    status = semctl(full_id, 0, SETVAL, setvalArg);  // full = 0

    empty_key = ftok("/Users/anjishnu/Documents/GitHub/6th_sem/OS/ass5/q_0/q0.c", 4);
    empty_id = semget(empty_key, NO_SEM, IPC_CREAT | 0777);
	setvalArg.val = size;
    status = semctl(empty_id, 0, SETVAL, setvalArg); // empty = buffer_size

	pid = fork();
	if(pid == 0)
	{
		int i;
        int p;
		while(1)
		{
			for (i = 0; i<producers; i++)
			{
				wait(empty_id);
				wait(mutex_id);
                p = rand()%1024;
                qp->rear = (qp->rear+1)%size;
                qp->data[qp->rear] = p;
                qp->count += 1;
				printf("Producer %d : Item produced is %d, front : %d, rear : %d, count : %d\n", i+1, p, qp->front, qp->rear, qp->count);
				sig(mutex_id);
				sig(full_id);

				sleep(1);
			}
		}
	}

	else
	{
		int i;
        int p;
		while(1)
		{
			for (i = 0; i<consumers; i++)
			{
				wait(full_id);
				wait(mutex_id);
                p = qp->data[qp->front];
				qp->front = (qp->front + 1)%size;
                qp->count -= 1;
				printf("Consumer %d : Item consumed is %d, front : %d, rear : %d, count : %d\n", i + 1, p, qp->front, qp->rear, qp->count);
				sig(mutex_id);
				sig(empty_id);

				sleep(2);
			}
		}
	}

	return 0;
}