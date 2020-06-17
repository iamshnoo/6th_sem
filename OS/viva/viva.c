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

int main(int argc, char* argv[]){

        int n;
        printf("Please Enter the number of elements: ");
        scanf("%d",&n);
        int arr[n];
        int shmid;
        int *shmptr;
        for(int i =0;i<n;i++)
        {
            int status;
            pid_t pid;
            int duration;
            time_t t;
            srand((unsigned) time(&t));

            shmid = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT | 0666);
            if (shmid == -1) {
                    perror("shmget() failed.\n");
                    exit(1);
            }
            printf("Parent has received a shared memory of 1 integer. \n");
            sleep(1);
            shmptr = (int*) shmat (shmid, NULL, 0);

            pid = fork();
            if(pid == 0)
            {

                *shmptr = rand()%100;

                printf("Element generated is : \n");
                printf("%d\n",*shmptr);
                exit(0);
            }
            wait(NULL);
            arr[i]=*shmptr;
        }

        int sum = 0;

        printf("Summing the array now : \n");
        for(int j=0; j<n; j++)
        {
          sum+= arr[j];
          printf("%d %d\n",arr[j],j);
        }

        printf("%d\n", sum);

}