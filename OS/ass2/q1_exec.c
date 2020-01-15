#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
  char* ls_args[] = {"./executable_2", "Gopal is a good boy", NULL};
  printf("Number of processes in the system before exec: ");
  fflush(stdout);
  system("ps -C --no-headers | wc -l");
  execvp(ls_args[0], ls_args);
  perror("execv");

  return 0;
}