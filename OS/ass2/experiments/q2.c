// Write a C program to create n processes - - DONT DO NOW

/****************************************************************
 * Write a complete C program that reads n strings as command line arguments.
 * That is, the program uses "int argc" and "char *argv[]" to read strings S1,
 * S2, ..., Sn. The strings S1, S2, ..., Sn are actually different commands with
 * optional switches prefixed with a hyphen(-). When the program is executed as
 * "./a.out S1 S2 ... Sn", the program then creates n additional child processes
 * P1, P2, ..., Pn such that Pi, 1 ≤  i ≤  n, execute the command in  Si. For
 * example, if the program is executed as "./a.out ls -l wc -l ", then, P1 will
 * execute "ls -l" and  P2 will print "wc -l" and so on.
 * ****************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  // first argument in list is the file name, hence ignore it
  int n = argc - 1;

  // to check if process is a child process
  pid_t pids[n];

  // dynamically create array of character pointers
  char **arr = (char **)malloc(n * sizeof(char *));

  // dynamically allocate memory for each row of above array
  // copy command line arguments one-by-one into each row of array
  for (int i = 0; i < n; i++) {
    arr[i] = malloc(strlen(argv[i + 1]) + 1);
    strcpy(arr[i], argv[i + 1]);
  }

  // create a child process
  // print each row of 2d array using a separate child process
  for (int i = 0; i < n; i++) {
    if ((pids[i] = fork()) == 0) {
      printf("%s ", arr[i]);
      system(arr[i]);
      // terminate child process, child becomes zombie
      exit(0);
    } else {
      // parent reaps terminated (zombie) child process
      wait(NULL);
    }
  }
  printf("\n");
  return 0;
}