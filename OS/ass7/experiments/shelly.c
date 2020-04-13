/**
 * @file shelly.c
 * @author Anjishnu Mukherjee
 * @brief A custom shell that makes use of the readline library.
 * http://man7.org/linux/man-pages/man3/readline.3.html for supporting history
 * of input commands provided and tab-completion of filenames.
 * @ref I have used a few sources to understand more about the readline library
 * other than the man pages. I wanted to take input in a manner similar to gets
 * and also to support history feature of terminals. The readline library allows
 * me to do both of these tasks easily. Line editing is supported by default.
 * Also tab completion of filenames is enabled by default when using readline
 * to take input. Apart from these additional features, all the core features of
 * the shell use only the standard libraries we have used for previous
 * assignments.
 * http://web.mit.edu/gnu/doc/html/rlman_2.html
 * https://eli.thegreenplace.net/2016/basics-of-using-the-readline-library/
 *
 * Compile using gcc shelly.c -o shelly -lreadline
 * Run using ./shelly
 * @date 2020-04-10
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <readline/readline.h> // might need to compile using -lreadline
#include <readline/history.h>

#define MAXCOM 1000
#define MAXLIST 100

/**
 * @ref Reference
 * https://stackoverflow.com/questions/47503734/what-does-printf-033c-mean
 * Basically it is the equivalent of doing Ctrl+L.
 */
#define clear() printf("\033[H\033[J")

/* -------------------------- Helper Functions -------------------------------*/

// Fancy styling.
void InitShell()
{
	char* username;
	clear();
	printf("\n\n\n\n******************************************");
	printf("\n\n\n\t****ANJISHNU's SHELL****");
	printf("\n\n\n\n\tEnter `help` to know more.");
	printf("\n\tEnter `exit` to quit.");
	printf("\n\n\n\n******************************************");
	username = getenv("USER");
	printf("\n\n\n\tUSER is: %s", username);
	printf("\n");
	sleep(3);
	clear();
	return;
}

// Helper function to print current working directory.
void PrintDir()
{
	char cwd[1024];
	getcwd(cwd, sizeof(cwd));
	printf("\nDir: %s\n", cwd);
	return;
}

// Helper function to display `help` menu.
void OpenHelp()
{
	puts(
		"\n1. List of Commands supported:"
		"\n>  ---------------------------\n"
		"\na. Internal commands - "
		"\n>  ---------------------"
		"\n>  hello"
		"\n>  help"
		"\n>  exit"
		"\n>  cd"
		"\n>  pwd"
		"\n>  clear"
		"\n"
		"\nb. External commands - "
		"\n>  ---------------------"
		"\n>  All commands available in UNIX shell."
		"\n>  eg. ls, ls -lt, ls | wc "
		"\n"
		"\n2. Main Features:"
		"\n>  ----------------\n"
		"\n>  Pipe handling for upto 2 commands."
		"\n>  History of commands (use ↑ and ↓ to navigate)."
		"\n>  Tab completion of filenames."
		"\n>  Line editing after having typed a command word."
		"\n>  Improper space handling."
	);

  return;
}

/* ----------------------- Execution Functions -------------------------------*/

// Function to execute commands built into this shell.
int ExecOwnCmd(char** parsed)
{
	int noOfOwnCmds = 6, i, switchOwnArg = 0;
	char* listOfOwnCmds[noOfOwnCmds];
	char* username;

	listOfOwnCmds[0] = "exit";
	listOfOwnCmds[1] = "cd";
	listOfOwnCmds[2] = "help";
	listOfOwnCmds[3] = "hello";
	listOfOwnCmds[4] = "pwd";
	listOfOwnCmds[5] = "clear";

	for (i = 0; i < noOfOwnCmds; i++)
	{
		if (strcmp(parsed[0], listOfOwnCmds[i]) == 0)
		{
			switchOwnArg = i + 1;
			break;
		}
	}

	switch (switchOwnArg)
	{
		case 1:
				printf("\nGoodbye.\n\n");
				exit(0);
		case 2:
				chdir(parsed[1]);
				return 1;
		case 3:
				OpenHelp();
				return 1;
		case 4:
				username = getenv("USER");
				printf("\nHello %s. \nType `help` to know more about this shell.\n",
						username);
				return 1;
		case 5:
				PrintDir();
				return 1;
		case 6:
				clear();
				return 1;
		default:
				break;
	}

	return 0;
}

// Function to execute system commands.
// All single commands (including those with arguments) supported in UNIX
// are supported by this function.
void ExecArgs(char** parsed)
{
	// Fork to create child.
	pid_t pid = fork();
	if (pid == -1)
	{
    fprintf(stderr, "\nForking child failed.");
    exit(EXIT_FAILURE);
	}

	// Body of child.
	else if (pid == 0)
	{
		printf("\n");
		execvp(parsed[0], parsed);
		fprintf(stderr, "\nFailed to execute command.");
    exit(EXIT_FAILURE);
	}

	// Parent of child.
	else
	{
		// Parent waits for child to terminate.
		wait(NULL);
	}
}

// Function to execute piped system commands.
// Currently only supports command1 | command2.
// Command 1 is present in "parsed".
// Command 2 is present in "parsedpipe".
// More than 2 commands are not supported yet in this function.
void ExecArgsPiped(char** parsed, char** parsedpipe)
{
	// 0 is read end, 1 is write end.
	int pipefd[2];
	pid_t p1, p2;

	// Open the pipe.
	if (pipe(pipefd) < 0)
	{
		fprintf(stderr, "\nFailed to open pipe.");
    exit(EXIT_FAILURE);
	}

	// Fork to create child 1.
	p1 = fork();
	if (p1 < 0)
	{
    fprintf(stderr, "\nForking child 1 failed.");
    exit(EXIT_FAILURE);
	}

	// Body of Child 1.
	// It only needs to write at the write end.
	if (p1 == 0)
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
		printf("\n");
		execvp(parsed[0], parsed);
		fprintf(stderr, "\nFailed to execute Command 1.");
    exit(EXIT_FAILURE);
	}

	// Parent of child 1.
	else
	{
		// Fork to create child 2.
		p2 = fork();
		if (p2 < 0)
		{
			fprintf(stderr, "\nForking child 2 failed.");
			exit(EXIT_FAILURE);
		}

		// Body of Child 2.
		// It only needs to read at the read end.
		if (p2 == 0)
		{
			close(pipefd[1]);
			dup2(pipefd[0], STDIN_FILENO);
			close(pipefd[0]);
			printf("\n");
			execvp(parsedpipe[0], parsedpipe);
			fprintf(stderr, "\nFailed to execute Command 1.");
			exit(EXIT_FAILURE);
		}

		// Parent of child 2 (same as parent of child 1).
		else
		{
			// Close all the file descriptors.
			close(pipefd[0]);
			close(pipefd[1]);

			// Wait for child 2 to terminate.
			wait(NULL);
		}

		// Wait for child 1 to terminate.
		wait(NULL);
	}
}

/* ----------------------- String Parsing Functions --------------------------*/

// Helper function for finding pipe.
// This function currently assumes input to be 2 piped commands
// of the form command 1 | command 2, where each command may have arguments.
// More than 2 commands are not supported yet in this function.
// str is the input string.
// The parsed output is stored in "strPiped".
int ParsePipe(char* str, char** strPiped)
{
	int i;
	for (i = 0; i < 2; i++)
	{
		strPiped[i] = strsep(&str, "|");
		if (strPiped[i] == NULL)
			break;
	}

	if (strPiped[1] == NULL)
		return 0; // returns zero if no pipe is found.

	else
		return 1;

}

// Helper function for parsing arguments to commands.
// str is the input string. Contains a command and its arguments (if, any).
// The parsed output is stored in the 2D array "parsed".
void ParseSpace(char* str, char** parsed)
{
	int i;

	for (i = 0; i < MAXLIST; i++)
	{
		parsed[i] = strsep(&str, " ");

		if (parsed[i] == NULL)
			break;

		if (strlen(parsed[i]) == 0)
			i--;
	}

	return;
}

// Wrapper function to call helper functions.
// str is the input string. Contains a line of input taken using TakeInput().
// Outputs are stored in "parsed" and "parsedPipe" arrays.
// Assumptions : Either single commands or single comands with arguments or
// 2 piped commands or 2 piped commands with arguments can be processed with
// this function. Commands connected with "&&" or other symbols cannot be
// processed yet using this function.
int ProcessString(char* str, char** parsed, char** parsedPipe)
{
	char* strPiped[2];
	int piped = 0;

	// This if block implicitly assumes that this shell currently supports
	// only 2 piped commands of the form command 1 | command 2.
	piped = ParsePipe(str, strPiped);
	if (piped)
	{
		ParseSpace(strPiped[0], parsed);
		ParseSpace(strPiped[1], parsedPipe);
	}

	else
		ParseSpace(str, parsed);

	if (ExecOwnCmd(parsed))
		return 0;

	else
		return 1 + piped;
}

// Function to take input from terminal, store it in a string
// and save it to a history of commands that can be scrolled
// using ↑ and ↓ to navigate.
int TakeInput(char* str)
{
	char* buf;

	// Allocates memory using malloc and hence we free() it after usage is over.
	buf = readline(">>> ");
	// Only add non-empty lines to history.
	if (strlen(buf) != 0)
	{
		add_history(buf);
		strcpy(str, buf);
		free(buf);
		return 0;
	}

	free(buf);
	return 1;
}

/* ----------------------------- Main Function -------------------------------*/

int main(int argc, char *argv[])
{
	char inputString[MAXCOM], *parsedArgs[MAXLIST];
	char* parsedArgsPiped[MAXLIST];
	int execFlag = 0;

	InitShell();
	while (1)
	{
		// Print prompt.
		PrintDir();

		// Take input.
		if (TakeInput(inputString))
			continue;

		// Process the input and set a flag to decide execution.
		// execFlag = { 0, no command or built-in command
		//						{ 1, simple system command (maybe with flags)
		//						{ 2, piped commands
		execFlag = ProcessString(inputString, parsedArgs, parsedArgsPiped);

		// Execute input commands.
		if (execFlag == 1)
			ExecArgs(parsedArgs);

		if (execFlag == 2)
			ExecArgsPiped(parsedArgs, parsedArgsPiped);
	}

	return 0;
}

/*
 *	Function: tokenizeString
 *	Splits a string according to the given delimiter
 *	Parameters:
 *		char** args (OUTPUT)	- array of tokens created
 *		int *argc (OUTPUT)		- number of tokens created
 *		char *str							- input string to tokenize
 *		const char* delim			- delimiter used to tokenize the string
 *	Returns:
 *		None

void tokenizeString(char ** args, int * argc, char * str,
    const char * delim) {
    char * token;
    int pc;
    token = strtok(str, delim);
    int cnt = -1;
    while (token) {
        args[++cnt] = (char * ) malloc((sizeof(token) + 1) * sizeof(char));
        strcpy(args[cnt], token);
        trimString(args[cnt]);
        token = strtok(NULL, delim);
    }
    args[++cnt] = NULL;
    * argc = cnt;
}
*/