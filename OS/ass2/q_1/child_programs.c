/**
 * @author Kinjal Ray
 * Date: 15.01.2020
 * create n processes and run a program in each process
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

/*Function to create array for argument of execvp()*/
char **getcmd(char *argv[], int cnt, int id) {
  int i, n;
  for (i = id + 1; i <= cnt; i++) {
    if (argv[i][0] != '-') break;
  }
  n = i - id;
  char **cmd = (char **)malloc(sizeof(char *) * (n + 1));
  for (i = id; i < id + n; i++) {
    cmd[i - id] = argv[i];
  }
  cmd[n] = NULL;
  return cmd;
}

int main(int argc, char *argv[]) {
  const int MAX_PROCESS = argc - 1;
  int process_count = 1;

  while (process_count <= MAX_PROCESS) {
    if (fork() == 0) {
      char **tmp = getcmd(argv, MAX_PROCESS, process_count);
      execvp(tmp[0], tmp);
      break;
    }
    wait(NULL);
    process_count++;
  }

  return 0;
}
