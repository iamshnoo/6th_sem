/**
 * @file q0.c
 * @author Anjishnu Mukherjee
 * @brief - Implementation of a primitve shell
 * @version 0.1
 * @date 2020-03-11
 *
 * @copyright Copyright (c) 2020
 *
 */

/**
 * @brief
 *
 * A shell is an interface program between the Operating System and a User.
 * That is, a shell takes commands from the user and executes those commands
 * through invocation of appropriate system calls as depicted in the
 * following figure.
 *
 * You are familiar with Bourne Shell (/bin/sh) or Bourne Again Shell
 * (/bin/bash). You may refer to the manual (guide) on bash to have an idea
 * about the language (shell script) in which user may issue commands to it.
 * The present assignment is to construct a trivial shell (say, mysh).
 *
 * In general the commands a shell can execute are of 2 types -
 * internal commands and external commands.
 * Commands like cd, pwd, etc., are internal commands.
 * Please note that the shell does not need any external executable file
 * for the internal commands. Whereas, external commands (eg., ls, vi, ...)
 * are essentially executable files and are managed by the shell by
 * first creation of child process (fork())and then  making the child process
 * execute (execve()) the file.
 * The trivial shell should support internal commands like cd, pwd, clear, exit,
 * etc. It should support any external command with or without command line
 * arguments. For example, myshell should be able to execute both  "ls" as
 * well as "ls -lt" as external commands. Multiple commands can be can be
 * connected by ";" (semicolon, sequential execution) "&&" (logical and),
 * "||" (logical or). That is "command1 ; commnd2" or  "command1 && commnd2"
 * or "command1 || commnd2" are all valid commands for "mysh".
 * You may refer to the guides (associated herewith) for the semantics (meaning)
 * of these operators.
 * The algorithm for "mysh" should be quite straight forward.
 *
 * do
 *
 * show the shell prompt
 *
 * read a line in the string variable cmd
 *
 * parse cmd into subcommands
 * [in "command1 ; command2" command1 and command2 are subcommands]
 *
 * parse the subcommands for command line arguments
 *
 * if a subcommand is internal then do what is necessary for it.
 * Else if there is an executable for the command then fork() and
 * let the child process execute the executable while (true);
 *
 * Please note that "mysh" can be executed interactively, that is,
 * upon execution it accepts commands from the stdin.
 * "mysh" can also be executed in batch mode (for example, mysh file.sh)
 * when mysh will read the commands from the file "file.sh" and execute them.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/wait.h>

char buffer[1024];
char* args[512];
pid_t pid;
int n = 0; // number of commands run

void split(char* cmd);
char* skipwhitespace(char* s);
int execute(int input, int first, int last);

int main(){
  printf("My Shell : Type 'exit' to exit.\n");
  do{
    char *cmd = NULL;
    char *next = NULL;
    int input = 0;
    int first = 1;

    //! show the shell prompt
    printf("->");
    fflush(NULL);

    //! read a line into string cmd
    cmd = fgets(buffer, 1024, stdin);
    next = strchr(cmd, '|');

    while(next!=NULL){
      *next = '\0';
      split(cmd);
      if (args[0] != NULL) {
		    n += 1;
        execute(input, first, 0);
      }

      cmd = next + 1;
      next = strchr(cmd, '|');
      first = 0;
    }

    split(cmd);
    if (args[0] != NULL) {
      n += 1;
      execute(input, first, 1);
    }

    // kill zombies
    for (int i = 0; i < n; ++i)
		  wait(NULL);

  } while(1);
}

char* skipwhitespace(char* s)
{
	while (isspace(*s)) ++s;
	return s;
}

void split(char* cmd)
{
	cmd = skipwhitespace(cmd);
	char* next = strchr(cmd, ' ');
	int i = 0;

	while(next != NULL) {
		next[0] = '\0';
		args[i] = cmd;
		++i;
		cmd = skipwhitespace(next + 1);
		next = strchr(cmd, ' ');
	}

	if (cmd[0] != '\0') {
		args[i] = cmd;
		next = strchr(cmd, '\n');
		next[0] = '\0';
		++i;
	}

	args[i] = NULL;
}

int execute(int input, int first, int last)
{
  // BUILT-IN FUNCTIONS
	if (strcmp(args[0], "exit") == 0) {
		exit(0);
  }

  else if (strcmp(args[0], "echo") == 0) {
    if(strcmp(args[1], "pid") == 0) {
            printf("%d\n", (int)getpid());
    }

    else {
            printf("%s\n", args[1]);
    }
  }

  else if (strcmp(args[0], "cd") == 0) {
    if(args[1]==NULL) {
      printf("%s\n", getenv("HOME"));
    }
  }

  // OTHER FUNCTIONS
  else {
    int pfd[2];
    pipe(pfd);
    pid = fork();

    if (pid == 0) {

      if (first == 1 && last == 0 && input == 0) {
        dup2(pfd[1], STDOUT_FILENO);
      }

      else if (first == 0 && last == 0 && input != 0) {
        dup2(input, STDIN_FILENO);
        dup2(pfd[1], STDOUT_FILENO);
      }

      else {
        dup2(input, STDIN_FILENO);
      }

      execvp(args[0], args);
      _exit(0);
    }

    if (input != 0)
      close(input);

    close(pfd[1]);

    if (last == 1)
      close(pfd[0]);

    return pfd[0];
  }
}