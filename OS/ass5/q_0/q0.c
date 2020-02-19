/*
There is a fixed size buffer and there are two types of processes;  
producer process and consumer processes. The producer processes produce 
items and enters them into the buffer and the consumer processes remove 
the items from the buffer and consume them.

A producer should not produce items into the buffer when the consumer 
is consuming an item from the buffer and vice versa. 
So the buffer should only be accessed by the producer or consumer at a time. 
The producer processes should also stop producing items if the buffer is 
full and the consumer process stops consuming items if the buffer is empty. 
Write a program to achieve the above-mentioned synchronization using semaphore.

Your program should be well indented and documented.
*/

#include <stdio.h>
#include <sys/types.h> /* for semget(2) ftok(3) semop(2) semctl(2) */
#include <sys/ipc.h>   /* for semget(2) ftok(3) semop(2) semctl(2) */
#include <sys/sem.h>   /* for semget(2) semop(2) semctl(2) */
#include <unistd.h>    /* for fork(2) */
#include <stdlib.h>    /* for exit(3) */
#include <semaphore.h>

#define NO_SEM	1
#define wait(s) semop(s, &Pop, 1);   // wait operation
#define signal(s) semop(s, &Vop, 1); // signal operation

static struct sembuf Pop = {0,-1,SEM_UNDO};
static struct sembuf Vop = {0, 1,SEM_UNDO};

int *buffer; //Defining the buffer

void createBuffer(int size)
{
	buffer = (int*)malloc(size*sizeof(int));
}


int main(int argc, char* argv[])
{
	int status;
    int producers = atoi(argv[1]);
	int consumers = atoi(argv[2]);
    int size = atoi(argv[3]);
    key_t mutex_key;
    int mutex_id;
    key_t full_key;
    int full_id;
    key_t empty_key;
    int empty_id;
    int in = -1;
	int out = -1;
    pid_t pid;

	union semun
	{
		int              val;    /* Value for SETVAL */
		struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
		unsigned short  *array;  /* Array for GETALL, SETALL */
		struct seminfo  *__buf;  /* Buffer for IPC_INFO (Linux-specific) */
	} setvalArg;

	createBuffer(size);
	mutex_key = ftok("/Users/anjishnu/Documents/GitHub/6th_sem/OS/ass5/q_0/q0.c", 3);
	mutex_id = semget(mutex_key, NO_SEM, IPC_CREAT | 0777);
	setvalArg.val = 1;
    status = semctl(mutex_id, 0, SETVAL, setvalArg); // mutex = 1
    full_key = ftok("/Users/anjishnu/Documents/GitHub/6th_sem/OS/ass5/q_0/q0.c", 2);
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
		while(1)
		{
			for (i = 0; i<producers; i++)
			{	
				wait(empty_id);
				wait(mutex_id);
				in = (in + 1)%size;
				buffer[in] = in + 1;
				printf("Producer %d : Item %d produced\n", i+1, in + 1);
				signal(mutex_id);
				signal(full_id);

				sleep(1);
			}
		}
	}

	else
	{
		int i;
		while(1)
		{
			for (i = 0; i<consumers; i++)
			{
				wait(full_id);
				wait(mutex_id);
				out = (out + 1)%size;
				printf("Consumer %d : Item %d consumed\n", i + 1, out + 1);
				signal(mutex_id);
				signal(empty_id);

				sleep(2);
			}
		}
	}

	return 0;
}