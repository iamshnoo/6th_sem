/*
Use of pipe system call
A pipe is a system call that is used in Linux and other Unix-like operating
systems to send the output of one command/program/process to another
command/program/process for further processing. In this assignment you have to
write a program that creates a pipe. One command will write its output in the
write end of the pipe and the other command will take its input from the read
end of the pipe and finally prints it output to the standard output. So when the
program is executed  as  ./a.out cmd1 | cmd2 (read | as pipe)  your output of
cmd1 will be written in the write end of the pipe and cm2 read from read end of
the pipe and finally prints its out put the screen.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  pid_t pid1;
  pid_t pid2;

  int pfd[2];
  int pipeRetVal;

  char *cmd1 = NULL;
  char *cmd2 = NULL;

  // open the pipe
  // Read-end = 0
  // Write-end = 1
  if ((pipeRetVal = pipe(pfd)) < 0) {
    fprintf(stderr, "Failed to open pipe\n");
    exit(EXIT_FAILURE);
  }

  // fork to create child 1
  if ((pid1 = fork()) < 0) {
    fprintf(stderr, "Forking child 1 failed.\n");
    exit(EXIT_FAILURE);
  }

  // body of child 1
  else if (pid1 == 0) {
    dup2(pfd[1], 1);
    close(pfd[0]);
    close(pfd[1]);
    cmd1 = argv[1];
    execlp(cmd1, cmd1, (char *)NULL);
    fprintf(stderr, "Failed to execute cmd 1\n");
    exit(EXIT_FAILURE);
  }

  // parent of child 1
  else {
    // fork to create child 2 from parent of child 1
    if ((pid2 = fork()) < 0) {
      fprintf(stderr, "Forking child 2 failed.\n");
      exit(EXIT_FAILURE);
    }

    // body of child 2
    if (pid2 == 0) {
      dup2(pfd[0], 0);
      close(pfd[1]);
      close(pfd[0]);
      cmd2 = argv[2];
      execlp(cmd2, cmd2, (char *)NULL);
      fprintf(stderr, "Failed to execute cmd 2\n");
      exit(EXIT_FAILURE);
    }

    // parent of child 2 (same as parent of child 1)
    else {
      // close all the pipe descriptors
      close(pfd[0]);
      close(pfd[1]);
      wait(NULL);
    }
    wait(NULL);
  }

  return EXIT_SUCCESS;
}
