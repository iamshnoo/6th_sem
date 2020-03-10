// Understanding of fork and exec - DONT DO NOW

/****************************************************************
 * We know the only way to create a process is to use the fork() system call and
 * the only way to execute an executable program is to use exec() system call.
 * Write a program to demonstrate the exec() system call does not create a new
 * process.
 * **************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  pid_t pid;
  printf("Number of processes in the system before fork: ");
  fflush(stdout);
  system("ps -C --no-headers | wc -l");

  pid = fork();
  if (pid == 0) {
    printf("Number of processes in the system after fork: ");
    fflush(stdout);
    system("ps -C --no-headers | wc -l");

  }

  else {
    wait(NULL);
  }

  return 0;
}
