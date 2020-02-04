#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>   
#include <string.h>

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
      cmd[j] = NULL;
    else
      cmd[j] = argv[j + current_index];
  }
    printf("%d -> ", current_index);
    for(int i=0; i<len; i++){
        printf("%s", cmd[i]);
    }
    printf("\n");
  return cmd;
}

int main(int argc, char *argv[]){
    pid_t pids[argc];
    for (int counter = 1; counter < argc; counter++) {
        fflush(stdout);
        char **cmd = process_next_arg(argc, argv, counter);
    }
/*
    char * p = NULL;
    char * cmds[64];
    char buffer[BUFSIZ];
    int num_cmds = 0; 
    fgets(buffer, sizeof(buffer), stdin);
    if(argc == 1){
        printf("Enter commands separated by | below.\n");
    }

    // num_cmds keeps track of the next slot in cmds that's to be filled
    // it has a final value equal to the number of array elements assigned.
    for (p = strtok(buffer, " "); p; p = strtok(buffer, " "))
    {
        // maximum number of storable cmds is 64.
    //    if (num_cmds >= 64){break;}
    //    cmds[num_cmds++] = p;
        printf("Command %d is '%s'.\n", num_cmds+1, p);
    }

    
    char* str = NULL;
    int len = 0;
    printf("\n%s\n", buffer);
    char * token = strtok(buffer, "|");
    while(token != NULL){
        printf("%s\n", token);
        token = strtok(NULL, "|");
    }
    //if(buffer[strlen(buffer) - 1] == '\n'){printf("%s\n", buffer);}
    
    char **arr = (char**) malloc((argc-1)*sizeof(char*));
    for(int i = 1; i < argc; i++){arr[i]=NULL;}
    for(int i = 1; i < argc; i++){arr[i]=argv[i];}
    for(int i = 1; i < argc; i++){
        //printf("%s\n", argv[i]);
        //str = argv[i];
        //arr[i] = str; 
        printf("%s\n", arr[i]);
        // printf("%d\n",i);
        //len = len + strlen(argv[i]);
        //str = (char*) realloc(str, len);
        //strcat(str, argv[i]);
        // printf("%s\n", str);
    }
    
    //printf("\n");
    //printf("%s\n", str);
*/
    return 0;
}