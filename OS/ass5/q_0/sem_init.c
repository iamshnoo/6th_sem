#include "sem_init.h"
#include <stdio.h> 
#include <stdlib.h> 
#include <sys/types.h> 
#include <sys/ipc.h> 
#include <sys/shm.h> 
#include <sys/wait.h> 
#include <unistd.h> 
#include <sys/sem.h>

int mutex_init_(){
    key_t mutex_key;
    int mutex_id;
    int status;

    union semun
    {
        int              val;    /* Value for SETVAL */
        struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
        unsigned short  *array;  /* Array for GETALL, SETALL */
        struct seminfo  *__buf;  /* Buffer for IPC_INFO (Linux-specific) */
    } setvalArg;

    mutex_key = ftok("/Users/anjishnu/Documents/GitHub/6th_sem/OS/ass5/q_0/q0.c", 2);
	mutex_id = semget(mutex_key, NO_SEM, IPC_CREAT | 0777);
	setvalArg.val = 1;
    status = semctl(mutex_id, 0, SETVAL, setvalArg); // mutex = 1
    return mutex_id;
}

int full_init_(){
    int status;
    key_t full_key;
    int full_id;

    union semun
    {
        int              val;    /* Value for SETVAL */
        struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
        unsigned short  *array;  /* Array for GETALL, SETALL */
        struct seminfo  *__buf;  /* Buffer for IPC_INFO (Linux-specific) */
    } setvalArg;

    full_key = ftok("/Users/anjishnu/Documents/GitHub/6th_sem/OS/ass5/q_0/q0.c", 3);
    full_id = semget(full_key, NO_SEM, IPC_CREAT | 0777);
	setvalArg.val = 0;
    status = semctl(full_id, 0, SETVAL, setvalArg);  // full = 0
    return full_id;
}

int empty_init_(int size){
    int status;
    key_t empty_key;
    int empty_id;

    union semun
    {
        int              val;    /* Value for SETVAL */
        struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
        unsigned short  *array;  /* Array for GETALL, SETALL */
        struct seminfo  *__buf;  /* Buffer for IPC_INFO (Linux-specific) */
    } setvalArg;

    empty_key = ftok("/Users/anjishnu/Documents/GitHub/6th_sem/OS/ass5/q_0/q0.c", 4);
    empty_id = semget(empty_key, NO_SEM, IPC_CREAT | 0777);
	setvalArg.val = size;
    status = semctl(empty_id, 0, SETVAL, setvalArg); // empty = buffer_size
    return empty_id;
}