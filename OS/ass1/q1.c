// Write a C program to create 3 processes

/****************************************************************
 * A C program that creates 3 child processes P1,P2 and P3,
 * such that each process prints "Hello World! I am Pi".
 * **************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#define NUM_CHILDREN 3

int main(void) {
  pid_t pids[NUM_CHILDREN];

  for (int i = 0; i < NUM_CHILDREN; i++) {
    if ((pids[i] = fork()) == 0) {
      printf("Hello world! I am P%d\n", i + 1);
      // terminate child process, child becomes zombie
      exit(0);
    } else {
      // parent reaps terminated (zombie) child process
      wait(NULL);
    }
  }

  return 0;
}
