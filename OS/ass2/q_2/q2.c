// Child Processes execute different Programs with switches

/****************************************************************
 * Write a complete, user-friendly, well-documented and nicely-indented
 * C program which when executed as "./a.out executable1 executable2 ...
 * executableN" creates N child processes where the 1st child process 1st
 * executes the 1st executable file (given by executable1). 2nd executes the 2nd
 * executable file (given by executable2) and so on. Please note that in this
 * assignment no scope was there to pass command line arguments to the
 * executables. Extend the  assignment so that this can be done now. That is the
 * program now can be called as "./a.out ls -l ps -ef" such that 1st child
 * process executes the command "ls -" and the second one executes "ps -ef".!
 * **************************************************************/

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

// This function has some implicit functions as listed below.
// Arguments can have switches starting with '-'
// Clearly, it doesn't cover all possible command line argument options.
char **process_next_arg(int argc, char *argv[], int current_index) {
  int len = 1;
  int j = 0;
  int i = current_index + 1;
  char **cmd = NULL;
  for (; i < argc; i++, len++) {
    if (argv[i][0] != '-') {
      break;
    }
  }

  cmd = (char **)malloc(sizeof(char *) * len + 1);
  for (; j <= len; j++) {
    if (j == len)
      cmd[j] = '\0';
    else
      cmd[j] = argv[j + current_index];
  }

  return cmd;
}

int main(int argc, char *argv[]) {
  pid_t pids[argc];
  for (int counter = 1; counter < argc; counter++) {
    fflush(stdout);
    char **cmd = process_next_arg(argc, argv, counter);
    if ((pids[counter] = fork()) == 0) {
      execvp(cmd[0], cmd);
      exit(0);
    } else {
      wait(NULL);
    }
  }
  return 0;
}
