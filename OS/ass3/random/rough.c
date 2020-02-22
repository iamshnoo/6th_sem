/**
* @author Kinjal Ray
* Date: 22.01.2020
* Pipe output of one command to another command
*/

#include<stdio.h>
#include <string.h>
#include <unistd.h>
#include<stdlib.h>
#include<sys/wait.h>

int main(int argc , char *argv[])
{
  int fd[2] , i;
  int n = argc - 1;
	pid_t pid[n];
  int prev;


  prev = 0;
	for(i = 0; i < n; i++)
  {
    if(i != n - 1)
    {
      pipe(fd);
    }
  	pid[i] = fork();
  	if (pid[i]==0)
    {
  		if(i != 0)
      {
        dup2(prev , 0);
      }
      close(prev);
      if(i != n - 1)
      {
        dup2(fd[1] , 1);
      }
      close(fd[1]);
      execlp(argv[i+1] , argv[i+1] , NULL);
  		exit(1);
  	}
    prev = fd[0];
  }

  close(prev);
	close(fd[0]);
	close(fd[1]);
  for(i = 0; i < n; i++)
    waitpid(pid[i] , NULL , 0);

	return 0;
}