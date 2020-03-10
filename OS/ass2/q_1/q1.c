// Child Processes execute different Programs

/****************************************************************
 * Write a complete, user-friendly, well-documented and nicely-indented
 * C program which when executed as "./a.out executable1 executable2 ...
 * executableN" creates N child processes where the 1st child process 1st
 * executes the 1st executable file (given by executable1). 2nd executes the 2nd
 * executable file (given by executable2) and so on. Explore what happens when
 * in place of executable files the user provides a text file for execution.
 * Write your observation and justification for this online in the given
 * text-area!
 * ---------------------------------------------------------------
 * Compile : gcc q1.c -o q1
 * Run : ./q1 ./executable1 ./executable1 ./executable1
 * Run : ./q1 ./executable1
 * Run : ./q1 ./abc.txt
 * **************************************************************/

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  pid_t pids[argc];
  for (int counter = 1; counter < argc; counter++) {
    fflush(stdout);
    char *cmd[] = {argv[counter], NULL};
    if ((pids[counter] = fork()) == 0) {
      execvp(cmd[0], cmd);
      exit(0);
    } else {
      wait(NULL);
    }
  }
  return 0;
}
