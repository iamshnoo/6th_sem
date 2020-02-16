#include <stdio.h>
#include <sys/types.h> /* for semget(2) ftok(3) semop(2) semctl(2) */
#include <sys/ipc.h> /* for semget(2) ftok(3) semop(2) semctl(2) */
#include <sys/sem.h> /* for semget(2) semop(2) semctl(2) */
#include <unistd.h> /* for fork(2) */
#include <stdlib.h> /* for exit(3) */
#include <semaphore.h>

#define NO_SEM	1
#define wait(s) semop(s, &Pop, 1); //wait operation
#define signal(s) semop(s, &Vop, 1); //signal operation

struct sembuf Pop;
struct sembuf Vop;

int *buffer; //Defining the buffer

void createBuffer(int size)
{
	buffer = (int*)malloc(size*sizeof(int));
}

int main()
{
	key_t mykey;
	pid_t pid;
	int semid;
	int status;

	union semun
	{
		int              val;    /* Value for SETVAL */
		struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
		unsigned short  *array;  /* Array for GETALL, SETALL */
		struct seminfo  *__buf;  /* Buffer for IPC_INFO (Linux-specific) */
	} setvalArg;

	setvalArg.val = 1;

	/* struct sembuf has the following fields */
	//unsigned short sem_num;  /* semaphore number */
        //short          sem_op;   /* semaphore operation */
        //short          sem_flg;  /* operation flags */

	Pop.sem_num = 0;
	Pop.sem_op = -1;
	Pop.sem_flg = SEM_UNDO;

	Vop.sem_num = 0;
	Vop.sem_op = 1;
	Vop.sem_flg = SEM_UNDO;

	// key_t ftok(const char *pathname, int proj_id);
	mykey = ftok("./sem1.c", 1);
	
	if (mykey == -1)
	{
		perror("ftok() failed");
		exit(1);
	}

	//       int semget(key_t key, int nsems, int semflg);
	semid = semget(mykey, NO_SEM, IPC_CREAT | 0777);
	
	if(semid == -1)
	{
		perror("semget() failed");
		exit(1);
	}

	// int semctl(int semid, int semnum, int cmd, ...);
	status = semctl(semid, 0, SETVAL, setvalArg);
	
	if(status == -1)
	{
		perror("semctl() failed");
		exit(1);
	}


	int producers;
	int consumers;

	printf("Enter number of producers :");
	scanf ("%d", &producers);

	printf("Enter number of consumers :");
        scanf ("%d", &consumers);

	int size;
	printf("Enter size of buffer :");
        scanf ("%d", &size);

	createBuffer(size);

	key_t mutex_key;
	mutex_key = ftok("./sem1.c", 3);

        if (mutex_key == -1)
        {
                perror("ftok() failed");
                exit(1);
        }

        // int semget(key_t key, int nsems, int semflg);
        int mutex_id;
	mutex_id = semget(mutex_key, NO_SEM, IPC_CREAT | 0777);

        if(mutex_id == -1)
        {
                perror("semget() failed");
                exit(1);
        }

        // int semctl(int semid, int semnum, int cmd, ...);
	setvalArg.val = 1;
        status = semctl(mutex_id, 0, SETVAL, setvalArg);

        if(status == -1)
        {
                perror("semctl() failed");
                exit(1);
        }

	key_t full_key;
        full_key = ftok("./sem1.c", 2);

        if (full_key == -1)
        {
                perror("ftok() failed");
                exit(1);
        }

        // int semget(key_t key, int nsems, int semflg);
        int full_id;
        full_id = semget(full_key, NO_SEM, IPC_CREAT | 0777);

        if(full_id == -1)
        {
                perror("semget() failed");
                exit(1);
        }

        // int semctl(int semid, int semnum, int cmd, ...);
	setvalArg.val = 0;
        status = semctl(full_id, 0, SETVAL, setvalArg);

        if(status == -1)
        {
                perror("semctl() failed");
                exit(1);
        }

	key_t empty_key;
        empty_key = ftok("./sem1.c", 4);

        if (empty_key == -1)
        {
                perror("ftok() failed");
                exit(1);
        }

        // int semget(key_t key, int nsems, int semflg);
        int empty_id;
        empty_id = semget(empty_key, NO_SEM, IPC_CREAT | 0777);

        if(empty_id == -1)
        {
                perror("semget() failed");
                exit(1);
        }

        // int semctl(int semid, int semnum, int cmd, ...);
	setvalArg.val = size;
        status = semctl(empty_id, 0, SETVAL, setvalArg);

        if(status == -1)
        {
                perror("semctl() failed");
                exit(1);
        }

	//printf("Empty - %d", semctl(empty_id, 0, GETVAL, setvalArg));
	//printf("Mutex - %d", semctl(mutex_id, 0, GETVAL, setvalArg));
	//printf("Full - %d", semctl(full_id, 0, GETVAL, setvalArg));


	int in = -1;
	int out = -1;

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
