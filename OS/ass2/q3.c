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
 * **************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#define MAX 100
int i = 1;
int main(int argc, char *argv[]) {
  int pid = 0;
  while (i <= argc-1) {

    if ((pid = fork()) == 0) {

      int j = 0;

      for (j = i + 1; j < argc; j++) {

        if (argv[j][0] != '-') {
          break;
        }

        int length = j - i + 1;

        char **arr;
        arr = malloc(length * sizeof(char *));
        for (int k = 0; k < length; k++) {
          arr[k] = malloc(MAX * sizeof(char));
          // copy the strings to arr
          for(int l = 0; l < strlen(argv[k]); l++){
            arr[k][l] = argv[k][l];
          }
        }

        execvp(arr[0], arr);
      }

    }
    
    i++;
  
  }

  return 0;
}