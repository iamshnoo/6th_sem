// Write a C program to create n processes

/****************************************************************
 * A C program that reads n strings as command line arguments,
 * creates n additional child processes Pi (i= 1 to n),
 * such that each Pi prints reverse of string Si,
 * where the program is executed as ./a.out S1 S2 ... Sn.
 * **************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

// not included in string.h
char *strrev(char *str) {
  char *p1, *p2;

  p1 = str;
  p2 = str + strlen(str) - 1;

  if (!str || !*str) return str;

  // p1 points to start of string,
  // p2 points to end of string
  // swap characters in string using p1 and p2
  while (p2 > p1) {
    *p1 ^= *p2;
    *p2 ^= *p1;
    *p1 ^= *p2;
    ++p1;
    --p2;
  }
  return str;
}

int main(int argc, char *argv[]) {
  // first argument in list is the file name, hence ignore it
  int n = argc - 1;

  // to check if process is a child process
  pid_t pids[n];

  // dynamically create array of character pointers
  char **arr = (char **)malloc(n * sizeof(char *));

  printf("Output of q0_param (passed as argument to execvp in q0) : \n");
  // dynamically allocate memory for each row of above array
  // copy command line arguments one-by-one into each row of array
  // reverse the contents of each row of array
  for (int i = 0; i < n; i++) {
    arr[i] = malloc(strlen(argv[i + 1]) + 1);
    strcpy(arr[i], argv[i + 1]);
    arr[i] = strrev(arr[i]);
  }

  // create a child process
  // print each row of 2d array using a separate child process
  for (int i = 0; i < n; i++) {
    if ((pids[i] = fork()) == 0) {
      printf("%s ", arr[i]);
      // terminate child process, child becomes zombie
      exit(0);
    } else {
      // parent reaps terminated (zombie) child process
      wait(NULL);
    }
  }
  printf("\n");
  int num_processes = 1;
  printf("Process count after exec : ");
  fflush(stdout);
  system("ps --no-headers | wc -l");
  printf("\n");
  return 0;
}