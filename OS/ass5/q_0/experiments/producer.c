#include "buffer.h"
#include "producer.h"
#include <stdio.h> 
#include <stdlib.h> 
#include <sys/types.h> 
#include <sys/ipc.h> 
#include <sys/shm.h> 
#include <sys/wait.h> 
#include <unistd.h> 
#include <sys/sem.h>

#define wait(s) semop(s, &Pop, 1);   // wait operation
#define signal(s) semop(s, &Vop, 1); // signal operation

static struct sembuf Pop = {0,-1,SEM_UNDO};
static struct sembuf Vop = {0, 1,SEM_UNDO};

void producer(int producers, int mutex_id, int full_id, int empty_id, buffer* qp){
    int i;
    int p;
    while(1)
    {
        for (i = 0; i<producers; i++)
        {	
            wait(empty_id);
            wait(mutex_id);
            p = insertbuf(qp);
            printf("Producer %d : Item produced is %d, front : %d, rear : %d, count : %d\n", i+1, p, qp->front, qp->rear, qp->count);
            signal(mutex_id);
            signal(full_id);

            sleep(1);
        }
	}
}
