#include "buffer.h"
#include <stdio.h> 
#include <stdlib.h> 
#include <sys/types.h> 
#include <sys/ipc.h> 
#include <sys/shm.h> 
#include <sys/wait.h> 
#include <unistd.h> 
#include <sys/sem.h>

buffer* createbuf (int size){

    key_t buf_key;
    buffer *q;
    int shmID;
    buf_key = ftok("/Users/anjishnu/Documents/GitHub/6th_sem/OS/ass5/q_0/q0.c", 1);
    shmID = shmget(buf_key, sizeof(buffer), IPC_CREAT | 0777);
    q = (buffer*) shmat(shmID, 0, 777);
    int i;
    for (i=0; i<size; i++){
        q->data[i] = 999;
    }
    q->front = 0;
    q->rear = -1;
    q->count = 0;
    return q;

}

int insertbuf(buffer *q){
    int n = rand() % 1024;
    q->rear = (q->rear + 1) % MAX;
    q->data[q->rear] = n;
    q->count = q->count + 1;
    return n;
}

int deletebuf(buffer *q){
    int n = q->data[q->front];
    q->front = (q->front + 1) % MAX;
    q->count = q->count - 1;
    return n;
}
