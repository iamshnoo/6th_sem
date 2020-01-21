// Synchronizing termination of processes

/******************************************************************
 * In the previous assignment you have written a C program which when executed
 * as
 * "./a.out executable1 executable2 ... executableN" creates N additional child
 * processes where the 1st child process 1st executes the 1st executable file
 * (given by executable1). 2nd executes the 2nd executable file (given by
 * executable2) and so on.
 *
 * In this assignment modify the program so that the parent process waits for
 * completion of its N child processes. The parent process reports whether a
 * child process executing a particular  executable terminated normally or
 * abnormally. Try to include as much detailed reporting as possible.
 *
 * Please upload the program file!
 *
 * Explore that when a child process terminates abnormally what can be reflected
 * to the parent process. Write your observation and justification for this in
 * the given text-area!
 *
 * ****************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

// This function has some implicit functions as listed below.
// Arguments can have switches starting with '-'
// If there is a single switch, it works as expected.
// If there are multiple switches, the switch arguments are combined and treated
// as a single argument.
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
  int status = 0;
  char **cmd = NULL;
  pid_t pid = 0;
  for (int counter = 1; counter < argc; counter++) {
    pid = fork();
    if (pid < 0) {
      perror("Forking child process failed\n");
      exit(EXIT_FAILURE);
    }

    // child process
    else if (pid == 0) {
      fflush(stdout);
      cmd = process_next_arg(argc, argv, counter);
      execvp(cmd[0], cmd);
      printf("%s: failed to execute %s\n", argv[0], argv[counter]);
      exit(EXIT_FAILURE);
    }

    // parent process
    // NOTE : I have referenced some portions of the code below from
    // https://stackoverflow.com/a/57944670/11009359
    else {
      if (waitpid(pid, &status, 0) < 0) {
        printf("Failed to wait for %s process %d\n", argv[counter], (int)pid);
        exit(EXIT_FAILURE);
      }

      else if (WIFEXITED(status)) {
        printf("Child process %s terminated normally with status %d \n",
               argv[counter], WEXITSTATUS(status));
      }

      else if (WIFSIGNALED(status)) {
        printf("Child process %s was terminated by a signal %d \n",
               argv[counter], WTERMSIG(status));
      }

      else {
        printf("Child process %s died unexpectedly \n", argv[counter]);
        exit(EXIT_FAILURE);
      }
    }
  }

  return 0;
}