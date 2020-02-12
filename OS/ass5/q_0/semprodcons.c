#include <stdio.h> 
#include <stdlib.h> 
#include <sys/types.h> 
#include <sys/ipc.h> 
#include <sys/shm.h> 
#include <sys/wait.h> 
#include <unistd.h> 
#include <sys/sem.h>


#define P(s) semop(s, &Pop, 1);
#define V(s) semop(s, &Vop, 1);
struct sembuf Pop;
struct sembuf Vop;

#define MAX 5

typedef struct{
    int data[MAX];
    int front, rear, count;
} buffer;


void __init__ (buffer *);
void insertbuf(buffer *, int);
void deletebuf(buffer *);
void frontbuf (buffer *, int *);
void producer(buffer*, int);
void consumer(buffer*, int);

static int Wait(int semid, int num) {
    Pop.sem_flg = 0;
    Pop.sem_num = num;
    Pop.sem_op = -1;
    P(semid);
    return 0;
}

static int Signal(int semid, int num){
    Vop.sem_flg = 0;
    Vop.sem_num = num;
    Vop.sem_op = 1;
    V(semid);
    return 0;
}

int main(){
    int chID1, chID2, chID3,status;
    struct shmid_ds buff;
    buffer *qp;
    key_t mykey;

    // Creation of semaphore and shm
    mykey = ftok("/Users/anjishnu/Documents/GitHub/6th_sem/OS/ass5/q_0/semprodcons.c", 1);
    int shmID = shmget(mykey, sizeof(buffer), IPC_CREAT | 0777);
    int semID = semget(mykey, 3, IPC_CREAT | 0777);
    semctl(semID, 0 ,SETVAL, 1);   // mutex = 1
    semctl(semID, 1, SETVAL, MAX); // empty = MAX
    semctl(semID, 2, SETVAL, 0);   // full = 0
    qp = (buffer*) shmat(shmID, 0,777);

    if((chID1 = fork()!=0)){

        if((chID2 = fork()!=0)){

            if((chID3 = fork()!=0)){
                waitpid(chID1, &status, 0);
                waitpid(chID2, &status, 0);
                waitpid(chID3, &status, 0);
                shmdt(qp);
                shmctl(shmID, IPC_RMID, &buff);
                semctl(semID, 0, IPC_RMID);
            }

            else{
                buffer *qp;
                qp = (buffer *) shmat(shmID, 0 ,0777);
                producer(qp,semID);
                shmdt(qp);
            }
        }

        else {
            buffer *qp;
            qp = (buffer *) shmat(shmID, 0, 0777);
            consumer(qp, semID);
            shmdt(qp);
        }
    }

    else{
        buffer *qp;
        qp = (buffer *) shmat(shmID, 0 ,0777);
        producer(qp,semID);
        shmdt(qp);
    }

    return 0;

}

void __init__(buffer *q){
    q->front = 0;
    q->rear = 0;
    q->count = 0;
}

void insertbuf(buffer *q, int n){
    q->rear = (q->rear + 1 ) % MAX;
    q->data[q->rear] = n;
    q->count = q->count + 1;
}

void deletebuf(buffer *q){
    q->front = (q->front + 1) % MAX;
    q->count = q->count - 1;
}

void frontbuf (buffer *q, int *n){
    *n = q->data[(q->front + 1) % MAX];
}

void producer (buffer *qp, int semID){
    int count = 1;
    srand(getpid());
    while(count <= 10){
        int data;
        data = rand();
        Wait(semID, 1);     // wait(empty)
        Wait(semID, 0);     // wait(mutex)
        insertbuf(qp,data); // critical section
        Signal(semID,0);    // signal(mutex)
        Signal(semID,2);    // signal(full)
        printf("Process [%d] produced data %d. \n", getpid(),data);
        sleep(2);
    }
}

void consumer (buffer *qp, int semID){
    int count = 1;
    while(count<=10){
        int data;
        Wait(semID, 2);      // wait(full)
        Wait(semID, 0);      // wait(mutex)
        frontbuf(qp,&data);  // critical section
        deletebuf(qp);       // critical section
        Signal(semID, 0);    // Signal(mutex)
        Signal(semID, 1);    // Signal(empty)
        printf("Process [%d] consumerd data %d. \n", getpid(),data);
    }
}
