// Understanding of fork and exec

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

int main(int argc, char* argv[]) {
  pid_t pid;
  printf("Number of processes before fork call: ");
  fflush(stdout);
  system("ps --no-headers | wc -l");

  pid = fork();
  // child process
  if (pid == 0) {
    printf("Number of processes after fork call: ");
    fflush(stdout);
    system("ps --no-headers | wc -l");

  }

  // parent process
  else {
    wait(NULL);
    // executable_2 corresponds to a program from assignment 1
    char* const cmd[] = {"./q0_param", "Gopal is a good boy", NULL};
    printf("Number of processes before execvp system call: ");
    fflush(stdout);
    system("ps --no-headers | wc -l");
    execvp(cmd[0], cmd);
    perror("execvp");
  }

  return 0;
}